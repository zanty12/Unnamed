#include "taskscheduler.h"

// Initialize static members
std::vector<std::thread> TaskScheduler::workers_;
std::atomic<int> TaskScheduler::working_threads_{0};
std::atomic<int> TaskScheduler::task_priority_{0};
std::condition_variable TaskScheduler::condition_;
bool TaskScheduler::stop_ = false;
bool TaskScheduler::start_processing_ = false;
std::vector<Task> TaskScheduler::tasks_;
std::unordered_set<int> TaskScheduler::deletedTasks_;
const float TaskScheduler::deletionThresholdPercentage_ = 0.1f;
std::mutex TaskScheduler::queueMutex_;
std::vector<Task>::iterator TaskScheduler::current_task_;