#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>

struct Task
{
    int priority; // the bigger the priority, the sooner the task will be executed
    std::function<void()> func;

    Task() = default;

    Task(int priority, std::function<void()> func) : priority(priority), func(std::move(func))
    {
    }

    bool operator<(const Task& other) const
    {
        return priority < other.priority;
    }
};

class ThreadPool
{
private:
    std::vector<std::thread> workers_;
    std::priority_queue<Task> tasks_;
    std::atomic<int> working_threads_ = 0; // counter for working threads


    std::mutex queueMutex_;
    std::condition_variable condition_;
    bool stop_ = false;
    bool start_processing_ = false; // flag to indicate whether to start processing tasks

public:
    ThreadPool() {
        size_t numThreads = std::thread::hardware_concurrency();
        workers_.reserve(numThreads);
        for (size_t i = 0; i < numThreads; ++i) {
            workers_.emplace_back([this] {
                while (true) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(this->queueMutex_);
                        this->condition_.wait(lock, [this] {
                            return this->stop_ || (this->start_processing_ && !this->tasks_.empty());
                        });

                        if (this->stop_)
                            return;

                        task = this->tasks_.top();
                        this->tasks_.pop();
                    }
                    //std::cout<<"thread id: "<<std::this_thread::get_id()<<" working on task with priority: "<<task.priority<<"\n";
                    ++working_threads_; // increment counter when starting a task
                    task.func();
                    --working_threads_; // decrement counter when finishing a task
                    //std::cout<<"thread id: "<<std::this_thread::get_id()<<" finished task with priority: "<<task.priority<<"\n";

                    // Reset the start_processing_ flag if there are no more tasks
                    if (this->tasks_.empty()) {
                        std::unique_lock<std::mutex> lock(this->queueMutex_);
                        start_processing_ = false;
                    }
                }
            });
        }
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (std::thread& worker : workers_)
            worker.join();
    }

    template <class F>
    void Enqueue(int priority, F&& f)
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex_);

            // don't allow enqueueing after stopping the pool
            if (stop_)
                throw std::runtime_error("enqueue on stopped ThreadPool");

            tasks_.emplace(priority, std::forward<F>(f));
        }
        condition_.notify_one();
    }

    void StartProcessing() {
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            start_processing_ = true;
        }
        condition_.notify_all();
    }

    void WaitForJoin()
    {
        /*{
            std::unique_lock<std::mutex> lock(queueMutex_);
            stop_ = true;
        }
        condition_.notify_all();*/
        for (std::thread& worker : workers_)
            worker.join();
    }

    int GetTasksCount() const
    {
        return tasks_.size();
    }

    int GetWorkingThreads() const {
        return working_threads_;
    }
};
