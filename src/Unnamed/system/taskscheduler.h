#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <atomic>
#include <unordered_set>
#include <queue>

struct Task
{
    int priority; // the bigger the priority, the sooner the task will be executed
    int entityId; // ID of the entity associated with the task
    std::function<void()> func;

    Task() = default;

    Task(int priority, int entityId, std::function<void()> func)
        : priority(priority), entityId(entityId), func(std::move(func))
    {
    }

    bool operator<(const Task& other) const
    {
        return priority < other.priority;
    }
};

class TaskScheduler
{
    static std::vector<std::thread> workers_;
    static std::atomic<int> working_threads_; // counter for working threads
    static std::atomic<int> task_priority_; // counter for task priority
    static std::condition_variable condition_;
    static bool stop_;
    static bool start_processing_; // flag to indicate whether to start processing tasks

    static std::vector<Task> tasks_;
    static std::unordered_set<int> deletedTasks_;
    static const float deletionThresholdPercentage_; // Threshold for lazy deletion as a percentage
    static std::mutex queueMutex_;
    static std::vector<Task>::iterator current_task_; // current task being executed

public:
    static void Initialize()
    {
        size_t numThreads = std::thread::hardware_concurrency();
        workers_.reserve(numThreads);
        for (size_t i = 0; i < numThreads; ++i)
        {
            workers_.emplace_back([]()
            {
                while (true)
                {
                    {
                        std::unique_lock<std::mutex> lock(queueMutex_);
                        condition_.wait(lock, []()
                        {
                            return stop_ || (start_processing_ && current_task_ != tasks_.end());
                        });

                        if (stop_)
                            return;

                        //if there are higher priority tasks, wait for them to finish
                        if (current_task_ != tasks_.end() && current_task_->priority < task_priority_ && working_threads_ > 0)
                        {
                            std::cout << "thread id: " << std::this_thread::get_id() <<
                                " waiting for task with priority: " << task_priority_ << "\n";
                            std::cout << "current task priority: " << current_task_->priority << "\n";
                            condition_.wait(lock, []()
                            {
                                return stop_ || (start_processing_ && current_task_ != tasks_.end() && (current_task_->priority >=
                                    task_priority_ || working_threads_ <= 0));
                            });
                        }
                        //if current task has higher priority than current priority, or there are no tasks running
                        else if (current_task_ != tasks_.end() && current_task_->priority >= task_priority_ || working_threads_ == 0)
                        {
                            //set current priority to the priority of the task that was just executed
                            task_priority_ = current_task_->priority;
                            ++working_threads_; // increment counter when starting a task
                            current_task_->func();
                            ++current_task_;
                            --working_threads_; // decrement counter when finishing a task
                        }
                    }

                    // Reset the start_processing_ flag if there are no more tasks
                    if (tasks_.empty())
                    {
                        std::unique_lock<std::mutex> lock(queueMutex_);
                        start_processing_ = false;
                    }
                }
            });
        }
    }

    static void Shutdown()
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
    static void AddTask(int priority, int entityId, F&& f)
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        tasks_.emplace_back(priority, entityId, std::forward<F>(f));
        condition_.notify_one();
    }

    static void RemoveTask(int entityId)
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        deletedTasks_.insert(entityId);
        size_t threshold = static_cast<size_t>(tasks_.size() * deletionThresholdPercentage_);
        if (deletedTasks_.size() >= threshold)
        {
            RebuildQueue();
        }
    }

    static void StartProcessing()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            start_processing_ = true;
            current_task_ = tasks_.begin();
        }
        condition_.notify_all();
    }

    static void StopProcessing()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex_);
            start_processing_ = false;
            current_task_ = tasks_.end();
        }
        condition_.notify_all();
    }

    static int GetTasksCount()
    {
        return static_cast<int>(tasks_.size());
    }

    static bool FrameFinished()
    {
        return current_task_ == tasks_.end();
    }

    static int GetWorkingThreads()
    {
        return working_threads_;
    }

    static void ClearTasks()
    {
        std::unique_lock<std::mutex> lock(queueMutex_);
        tasks_.clear();
    }

    static void RebuildQueue()
    {
        std::vector<Task> newQueue;
        std::vector<Task>::iterator it = tasks_.begin();
        while (it != tasks_.end())
        {
            if (deletedTasks_.find(it->entityId) == deletedTasks_.end())
            {
                newQueue.emplace_back(it->priority, it->entityId, it->func);
            }
            ++it;
        }
        tasks_ = std::move(newQueue);
        deletedTasks_.clear();
        SortQueue();
    }

private:


    static void SortQueue()
    {
        std::sort(tasks_.begin(), tasks_.end());
    }
};
