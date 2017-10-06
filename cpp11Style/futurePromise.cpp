#include <thread>
#include <future>
#include <functional>
#include <iostream>

void accumulate(std::promise<int> &p)
{
	int sum = 0;
	for (int i = 0; i < 5; ++i)
		sum += i;
	p.set_value(sum);
}

int main()
{
	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::thread t{accumulate, std::ref(p)};
	std::cout << f.get() << '\n';
    t.join();
}
