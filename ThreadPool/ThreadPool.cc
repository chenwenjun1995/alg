#include "ThreadPool.h"

ThreadPool::ThreadPool()
{

}

ThreadPool::~ThreadPool() 
{
    
}

void ThreadPool::start(int thread_num) 
{
    for (int i = 0; i < thread_num; ++i) {
        thread_vec_.push_back(new std::thread(std::bind(&ThreadPool::run, this)));
    }
}

void ThreadPool::run() 
{
    int task;
    {
        std::lock_guard<std::mutex>  lg(mutex_);
        if (!data_list_.empty()) {
            int task = data_list_.front();
            data_list_.pop_front();
            std::cout<< std::this_thread::get_id() << ":" <<task << std::endl;
        }
        else {
            std::this_thread::sleep_for (std::chrono::seconds(1));
        }
    }
    std::this_thread::sleep_for (std::chrono::seconds(30));
}

void ThreadPool::add_task(int task) 
{
    std::lock_guard<std::mutex>  lg(mutex_);
    data_list_.push_back(task);
}