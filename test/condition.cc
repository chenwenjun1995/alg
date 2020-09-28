 #include <thread>
 #include <iostream>
 #include <mutex>
 #include <condition_variable>
 #include <chrono>
 using namespace std;

 class Test {
 public:
        Test():count_(0) {}
        void tt1() {
            std::unique_lock<std::mutex> uk(mt_);
            while(true) {
                if (count_ != 0) cd_.wait(uk);
                cout << "A\n";
                count_++;
                cd_.notify_one();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    
        void tt2() {
            std::unique_lock<std::mutex> uk(mt_);
            while(true) {
                if (count_ != 1) cd_.wait(uk);
                cout << "BB\n";
                count_++;
                cd_.notify_one();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    
        void tt3() {
            std::unique_lock<std::mutex> uk(mt_);
            while(true) {
                if (count_ != 2) cd_.wait(uk);
                cout << "CCC\n";
                count_ = 0;
                cd_.notify_one();
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
  public:
        std::mutex mt_;
        int count_;
        std::condition_variable cd_;
  };
 
  int main() {
        Test test;
        std::thread t1(&Test::tt1, &test);
        std::thread t2(&Test::tt2, &test);
        std::thread t3(&Test::tt3, &test);
        std::thread t4;
        t1.join();
        t2.join();
        t3.join();
        return 0;
  }

