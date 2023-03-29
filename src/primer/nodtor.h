#pragma once

struct NoDtor
{
  NoDtor() = default;
  ~NoDtor() = delete;
};