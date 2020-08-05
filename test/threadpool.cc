#include "../ThreadPool/ThreadPool.h"

int main() 
{
    ThreadPool tp;
    tp.start(10);
    for (int i = 0; i < 60; i++) {
        tp.add_task(i);
        std::cout<< "task:" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    std::this_thread::sleep_for(std::chrono::seconds(600));
    return 0;
}