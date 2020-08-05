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
        thread_vec_.push_back(new std::thread(&ThreadPool::run, this));
    }
}

void ThreadPool::run() 
{
    while (true) {
        {
            if (!data_list_.empty()) {
                int task;
                {
                    std::lock_guard<std::mutex>  lg(mutex_);
                    task = data_list_.front();
                    data_list_.pop_front();
                }
                std::cout<< "thread[" << std::this_thread::get_id() << "]:" << task << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void ThreadPool::add_task(int task) 
{
    std::lock_guard<std::mutex>  lg(mutex_);
    data_list_.push_back(task);
}
