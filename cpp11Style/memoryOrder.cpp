#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> a{0};
int b = 0;

void thread1()
{
	b = 1;
	a.store(1, std::memory_order_release);
}

void thread2()
{
	while (a.load(std::memory_order_acquire) != 1)
		;
	std::cout << b << '\n';
}

int main()
{
	std::thread t1(thread1);
	std::thread t2(thread2);
	t1.join();
	t2.join();
}
