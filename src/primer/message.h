#pragma once

#include "folder.h"
#include <string>
#include <set>

void swap(Message &lhs, Message &rhs);

class Message
{
  friend class Folder;
  friend void swap(Message &lhs, Message &rhs);

public:
  explicit Message(const std::string &str = "") : contents(str) {}
  Message(const Message &);
  Message &operator=(const Message &);
  ~Message();
  void save(Folder &);
  void remove(Folder &);
  

private:
  std::string contents;       // 消息内容
  std::set<Folder *> folders; // 文件夹

  void add_to_folders(const Message &);
  void remove_from_folders();
  void move_folders(Message* m);
};

