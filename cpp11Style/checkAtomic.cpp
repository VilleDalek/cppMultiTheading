#include <atomic>
#include <iostream>

int main()
{
	std::cout.setf(std::ios::boolalpha);

	std::atomic<short> s;
	std::cout << s.is_lock_free() << '\n';

	std::atomic<int> i;
	std::cout << i.is_lock_free() << '\n';

	std::atomic<long> l;
	std::cout << l.is_lock_free() << '\n';
}
