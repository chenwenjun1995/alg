#include <thread>
#include <vector>

class ThreadPool
{
public:
    ThreadPool(){}
    ~ThreadPool(){}

    void start(int thread_num);
    void add_task(const std::function<void>& func);
private:
    std::vector<std::thread> thread_vec_;
}