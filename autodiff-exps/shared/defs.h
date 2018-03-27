#pragma once

#include "defs_core.h"

template<typename T>
T dot(int n, const T* const x, const T* const y)
{
  T res = 0;
  for (int i = 0; i < n; i++)
    res = res + x[i] * y[i];
  return res;
}

