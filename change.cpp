#include "s.h"

thread_local S s{2};

extern "C" void G() {
	std::cout << "s.x = " << s.x << std::endl;
}
