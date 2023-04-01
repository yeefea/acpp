#include "message.h"

Message::Message(const Message &m) : contents(m.contents), folders(m.folders)
{
  add_to_folders(m);
}

Message::~Message()
{
  remove_from_folders();
}

Message &Message::operator=(const Message &rhs)
{
  remove_from_folders();
  contents = rhs.contents;
  folders = rhs.folders;
  add_to_folders(rhs);
  return *this;
}

void Message::save(Folder &f)
{
  folders.insert(&f);
  f.add_msg(this);
}

void Message::remove(Folder &f)
{
  folders.erase(&f);
  f.rem_msg(this);
}

void Message::add_to_folders(const Message &m)
{
  for (auto f : m.folders)
  {
    f->add_msg(this);
  }
}
void Message::remove_from_folders()
{
  for (auto f : folders)
  {
    f->rem_msg(this);
  }
}

void swap(Message &lhs, Message &rhs)
{
  using std::swap;
  for (auto f : lhs.folders)
  {
    f->rem_msg(&lhs); // 从folders里删除msg
  }
  for (auto f : rhs.folders)
  {
    f->rem_msg(&rhs); // 从folders里删除msg
  }
  swap(lhs.folders, rhs.folders);   // swap set
  swap(lhs.contents, rhs.contents); // swap string

  for (auto f : lhs.folders)
  {
    f->add_msg(&lhs);
  }
  for (auto f : rhs.folders)
  {
    f->add_msg(&rhs);
  }
}

void Message::move_folders(Message *m)
{
  folders = std::move(m->folders);
  for (auto f : folders)
  {
    f->rem_msg(m);
    f->add_msg(this);
  }
  m->folders.clear();
}