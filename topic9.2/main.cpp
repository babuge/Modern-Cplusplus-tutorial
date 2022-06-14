#include <iostream>

void no_throw_pre() noexcept {
	std::cout << "noexcept";
	throw true;
}

void may_throw() {
 	throw true;
}

auto non_block_throw = []{
	may_throw();
};

void no_throw() noexcept {
	return;
}

auto block_throw = []() noexcept {
	no_throw();
};

int main() {
	std::cout << "throw true" << std::endl;
	no_throw_pre();
	std::cout << std::boolalpha << "may_throw() noexcept? "
		<< noexcept(may_throw()) << std::endl
	<< "no_throw() noexcept? " << noexcept(no_throw()) << std::endl
	<< "lmay_throw() noexcept? " << noexcept(non_block_throw())<< std::endl
	<< "lno_throw() noexcept? " << noexcept(block_throw()) << std::endl;


	try {
		may_throw();
	} catch (...) {
		std::cout << "捕获异常，来自my_throw()" << std::endl;
	}

	try {
		non_block_throw();
	} catch(...) {
		std::cout << "捕获异常，来自 non_block_throw()" << std::endl;
	}

	try {
		block_throw();
	} catch(...) {
		std::cout << "捕获异常，来自block_throw()" << std::endl;
	}

	return 0;
}
