#include <thread>
#include <iostream>

int main()
{
      std::cout << std::this_thread::get_id() << '\n';
      std::cout << std::thread::hardware_concurrency() << '\n';
}
