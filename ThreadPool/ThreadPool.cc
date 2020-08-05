#include "ThreadPool.h"

ThreadPool::~ThreadPool() {

}

void ThreadPool::start(int thread_num, std::function<void> func) {
    for (int i = 0; i < thread_num; ++i) {
        thread_vec_.emplace_back(new std::thread(func));
    }
}