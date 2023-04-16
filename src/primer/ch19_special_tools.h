#pragma once
#include <cstdlib>
#include <stdexcept>

void* operator new(size_t size) {
  if (void* mem = malloc(size)) {
    return mem;
  }
  throw std::runtime_error("bad_alloc");
}