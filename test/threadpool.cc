#include "../ThreadPool/ThreadPool.h"

int main() 
{
    ThreadPool tp;
    tp.start(10);
    for (int i = 0; i < 9999999999; i++) {
        tp.add_task(i);
        std::cout<< "task:" << i << std::endl;
        std::this_thread::sleep_for (std::chrono::seconds(1));
    }
    return 0;
}