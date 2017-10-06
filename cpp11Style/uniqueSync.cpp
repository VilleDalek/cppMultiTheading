#include <thread>
#include <mutex>
#include <iostream>

void wait(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

std::timed_mutex mutex;

void thread1()
{
    using std::this_thread::get_id;
    for(int i = 0; i < 5; ++i) {
        wait(1);
        std::unique_lock<std::timed_mutex> lock(mutex);
        std::cout << "Thread " << get_id() << ": " << i << '\n';
        std::timed_mutex *m = lock.release();
        m->unlock();
    }
}

void thread2()
{
    using std::this_thread::get_id;
    for(int i = 0; i < 5; ++i) {
        wait(1);
        std::unique_lock<std::timed_mutex> lock(mutex, std::try_to_lock);
        if(lock.owns_lock() || lock.try_lock_for(std::chrono::seconds(1))) {
            std::cout << "Thread " << get_id() << ": " << i << '\n';
        }
    }
}

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);
    t1.join();
    t2.join();
}
