# Accelerated C++ Playground

## cpprestsdk

### MacOS
```
brew install cmake git boost openssl libressl ninja cpprestsdk
```

include path
```json
[
    "${workspaceFolder}/include",
    "${workspaceFolder}/src/apue3e/include",
    "/opt/homebrew/include",
    "/usr/local/lib",
    "/opt/homebrew/opt/libressl/include"
]

```

## Database

### MySQL

ubuntu
```bash
sudo apt-get install libmysqlclient-dev libmysqlcppconn-dev
```

### ClickHouse

### PostgreSQL


## Redis

hiredis
redis-plus-plus

## MQ

### ZeroMQ
```bash
sudo apt -y install libzmq3-dev
```

libzmq + cppzmq

### Kafka

https://github.com/confluentinc/librdkafka

```bash
sudo apt install librdkafka-dev
```

## Libraries

### Boost


### Abseil
https://github.com/abseil/abseil-cpp

### Asio
http://think-async.com/Asio/Documentation.html

### JSON

https://github.com/Tencent/rapidjson

### YAML

```bash
sudo apt -y install libyaml-cpp-dev
```
### Web Framework
Oat++

### Google Test

- https://github.com/google/googletest

- 项目示例，配合CMake使用 https://github.com/snikulov/google-test-examples


### Catch2
https://github.com/catchorg/Catch2

### Arg Parse

https://github.com/p-ranav/argparse

### Logging
https://github.com/PlatformLab/NanoLog

### Linear Algebra

#### Eigen

#### Armadillo

```bash
sudo apt install -y libarmadillo-dev
```

https://arma.sourceforge.net/

## Low latency

### Lock-free queue

https://github.com/cameron314/concurrentqueue

https://github.com/cameron314/readerwriterqueue


### Kernel bypass

- F-Stack https://github.com/F-Stack/f-stack

### IPC

- ZeroMQ 

- Fast DSS https://www.eprosima.com/index.php/resources-all/performance/zmq-vs-eprosima-fast-rtps

- Iceoryx https://github.com/eclipse-iceoryx/iceoryx

- cppipc https://github.com/mutouyun/cpp-ipc

- Boost interprocess https://stackoverflow.com/questions/22207546/shared-memory-ipc-synchronization-lock-free

## Graphics

### Dear ImGUI

### OGRE

## Parallel Computing

### OpenMP

### MPI

### CUDA

## Meta tools

### Cling

C++ REPL

### Build Tools
#### CMAKE

- 教程

https://www.cnblogs.com/satire/p/15257789.html

- Cheatsheet

https://github.com/mortennobel/CMake-Cheatsheet

https://usercontent.one/wp/cheatsheet.czutro.ch/wp-content/uploads/2020/09/CMake_Cheatsheet.pdf

- 奇技淫巧

https://zhuanlan.zhihu.com/p/123419161


https://zhuanlan.zhihu.com/p/121079042

#### Bazel

#### SCons


### Project structure

### GDB


### Gprof


### Valgrind


### Sanitizer
https://github.com/google/sanitizers
- AddressSanitizer
- ThreadSanitizer
- ...

### Tracer

TODO

### Package manager

TODO


## Cheatsheets
- [https://github.com/mortennobel/cpp-cheatsheet](https://github.com/mortennobel/cpp-cheatsheet)

- [https://github.com/AnthonyCalandra/modern-cpp-features](https://github.com/AnthonyCalandra/modern-cpp-features)

- 把难读的指针类型声明翻译成英语[https://cdecl.org/](https://cdecl.org/)

## Tutorials

- 指针声明 http://unixwiz.net/techtips/reading-cdecl.html

- 指针声明 https://faculty.cs.niu.edu/~mcmahon/CS241/Notes/reading_declarations.html

- Cherno's C++ Tutorial

## Books

- C++ Primer
- Effective C++
- More Effective C++
- Effective Modern C++

## References

- [https://cplusplus.com/reference/](https://cplusplus.com/reference/)

- [https://devdocs.io/cpp/](https://devdocs.io/cpp/)

- [https://en.cppreference.com/w/](https://en.cppreference.com/w/)

- [MSDN](https://learn.microsoft.com/en-us/cpp/cpp/cpp-language-reference?view=msvc-170)

- [https://isocpp.org/std/the-standard](https://isocpp.org/std/the-standard)

- [https://www.boost.org/doc/](https://www.boost.org/doc/)


## Cheat Sheets

- https://hackingcpp.com/cpp/cheat_sheets.html