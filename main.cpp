#include "s.h"

#include <dlfcn.h>

#include <thread>
#include <iostream>
#include <cassert>

thread_local S s{1};

using namespace std::chrono_literals;

using GFuncType = void(*)();
GFuncType g_func_ptr = nullptr;

void func(int id) {
  for (int i = 0; i < 100; i++) {
    std::cout << "Thread-" << id << ", [i = " << i << "]: ";
    if ( i < 4 ) {
      std::cout << "s.x = " << s.x << std::endl;
    } else {
      g_func_ptr();
    }
    std::this_thread::sleep_for(1000ms);
  }
}


int main() {
  std::thread t1(func, 1);
  std::this_thread::sleep_for(300ms);
  std::thread t2(func, 2);
  std::this_thread::sleep_for(300ms);
  std::thread t3(func, 3);
  auto handle = dlopen("./change.so", RTLD_NOW);
  assert(handle);
  g_func_ptr = reinterpret_cast<GFuncType>(dlsym(handle, "G"));
  assert(g_func_ptr);

  g_func_ptr();

  t1.join();
  t2.join();
  t3.join();
}
