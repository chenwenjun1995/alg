#include <thread>
#include <vector>
#include <list>
#include <mutex>
#include <iostream>
#include <chrono>

class ThreadPool
{
public:
    ThreadPool();
    ~ThreadPool();

    void start(int thread_num);
    void run();
    void add_task(int task);
private:
    std::mutex mutex_;
    std::list<int> data_list_;
    std::vector<std::thread*> thread_vec_;
};
