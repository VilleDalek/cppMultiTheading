#include <thread>
#include <mutex>
#include <iostream>

void wait(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

std::mutex mutex;

void thread ()
{
    using std::this_thread::get_id;
    for(int i = 0; i < 5; ++i) {
        wait(1);
    //    mutex.lock();
        std::lock_guard<std::mutex> lock(mutex);
        std::cout << "Thread " << get_id() << ": " << i << '\n';
    //    mutex.unlock();
    }
}

int main()
{
    std::thread t1(thread);
    std::thread t2(thread);
    t1.join();
    t2.join();
}
