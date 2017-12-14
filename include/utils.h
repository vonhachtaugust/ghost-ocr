#pragma once

#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace ghost {

  template <typename T>
  void print(T t) {
    std::cout << t << std::endl;
  }

  template <typename T>
  void printl(T t) {
    std::cout << t << " ";
  }

  template <typename Container>
  void printc(Container cont) {
    for (auto iter = std::begin(cont); iter != std::end(cont); ++iter) {
      printl(*iter);
    }
  }

  template <typename first, typename second>
  void printumap(std::unordered_map<first, second> map) {
    for (auto it = map.begin(); it != map.end(); ++it) {
      std::cout << it->first << " : " << it->second;
    }
    std::cout << std::endl;
  }
}  // namespace ghost
