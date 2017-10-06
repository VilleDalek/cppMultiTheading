#include <thread>
#include <future>
#include <functional>
#include <iostream>

int accumulate()
{
	int sum = 0;
	for (int i = 0; i < 5; ++i)
		sum += i;
	return sum;
}

int main()
{
	//std::packaged_task<int()> task(accumulate);
	//std::future<int> f = task.get_future();
	//std::thread t(std::move(task));
    std::future<int> f = std::async(accumulate);
	std::cout << f.get() << '\n';
    //t.join();
}
