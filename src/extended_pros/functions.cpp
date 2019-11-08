#include "main.h"

#include "extended_pros/functions.hpp"

template <typename T> bool isInVector(std::vector<T>& vec, T elem){
  return std::find(vec.begin(), vec.end(), elem) != vec.end();
}
