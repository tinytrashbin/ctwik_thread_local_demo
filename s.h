#pragma once

#include <iostream>

struct S {

  S(int x): x(x) {
    std::cout << "S::S(" << x << ")" << std::endl;
  }

  ~S() {
    std::cout << "~S::S(" << x << ")" << std::endl;
  }

  int x = 0;
};
