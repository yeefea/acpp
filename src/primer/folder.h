#pragma once

#include "message.h"

class Folder
{

public:
  void add_msg(Message *);
  void rem_msg(Message *);
};