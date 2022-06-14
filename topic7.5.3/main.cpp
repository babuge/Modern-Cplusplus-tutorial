#include <thread>
#include <atomic>
#include <iostream>
#include <ctime>
#include <vector>

int main() {
	
	std::atomic<int> counter{0};
	std::vector<std::thread> vt;
	std::time_t start, end;
	
	start = std::clock();
	for (int i=0;i<10000;++i) {
		vt.emplace_back([&]() {
			counter.fetch_add(1, std::memory_order_relaxed);
		});
	}
	
	for (auto& t:vt) {
		t.join();
	}
	
	end = std::clock();
	
	double during = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "during : " << during * 1000 << std::endl; 
	std::cout << "current counter: " << counter << std::endl;

	return 0;
}
