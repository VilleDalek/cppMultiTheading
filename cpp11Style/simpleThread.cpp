#include <iostream>
#include <thread>

void wait(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void thread()
{
    for(int i = 0; i < 5; ++i) {
        wait(1);
        std::cout << i << '\n';
    }
}

int main()
{
    std::thread t(thread);
    t.join();
    return 0;
}
