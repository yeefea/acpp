# Accelerated C++ Playground

## Books

- C++ Primer
- Effective C++
- More Effective C++
- Effective Modern C++
- ...

## Cheatsheets
- [https://github.com/mortennobel/cpp-cheatsheet](https://github.com/mortennobel/cpp-cheatsheet)

- [https://github.com/AnthonyCalandra/modern-cpp-features](https://github.com/AnthonyCalandra/modern-cpp-features)

- 把难读的指针类型声明翻译成人话 [https://cdecl.org/](https://cdecl.org/)

## Tutorials

- 指针声明 http://unixwiz.net/techtips/reading-cdecl.html

- 指针声明 https://faculty.cs.niu.edu/~mcmahon/CS241/Notes/reading_declarations.html

- Cherno's C++ Tutorial https://www.bilibili.com/video/BV1VJ411M7WR/?spm_id_from=333.337.search-card.all.click&vd_source=ac5b43cd098d981ddf36ad289c0ad346


## Cheat Sheets

- https://hackingcpp.com/cpp/cheat_sheets.html

## Interview

- https://csguide.cn/cpp/

- https://github.com/huihut/interview#database

## Essential Libraries
### CPPRESTSDK


### Libevent


### MySQL

ubuntu
```bash
sudo apt-get install libmysqlclient-dev libmysqlcppconn-dev
```

### ClickHouse

### PostgreSQL


### Redis

hiredis

redis-plus-plus


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

### Boost


### Abseil
https://github.com/abseil/abseil-cpp

### Asio
http://think-async.com/Asio/Documentation.html


### Serialization
#### JSON

https://github.com/Tencent/rapidjson

#### YAML

```bash
sudo apt -y install libyaml-cpp-dev
```

#### Protobuf

https://protobuf.dev/getting-started/cpptutorial/

#### Cap'n Proto

https://github.com/capnproto/capnproto


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

### Cryptography

https://github.com/openssl/openssl

- libssl
- libcrypto
- libsodium
- cryptopp https://github.com/weidai11/cryptopp

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

Boost lockfree

### NUMA

- libnuma-dev

### Kernel bypass

- F-Stack https://github.com/F-Stack/f-stack

### IPC

- ZeroMQ 

- Fast DSS https://www.eprosima.com/index.php/resources-all/performance/zmq-vs-eprosima-fast-rtps

- Iceoryx https://github.com/eclipse-iceoryx/iceoryx

- cppipc https://github.com/mutouyun/cpp-ipc

- Boost interprocess https://stackoverflow.com/questions/22207546/shared-memory-ipc-synchronization-lock-free

- https://mikewei.github.io/doc/shm_container/

## Graphics

### Dear ImGUI

### OGRE

## Parallel Computing

### OpenMP

### MPI

### CUDA

## Meta tools

编译过程：预处理(cpp) -> 编译(gcc/g++) -> 汇编(as) -> 链接(ld) -> 可执行文件

### G++

cheat sheet: https://bytes.usc.edu/cs104/wiki/gcc/

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

- Builtin modules

https://cmake.org/cmake/help/git-stage/manual/cmake-modules.7.html

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

## References

- [https://cplusplus.com/reference/](https://cplusplus.com/reference/)

- [https://devdocs.io/cpp/](https://devdocs.io/cpp/)

- [https://en.cppreference.com/w/](https://en.cppreference.com/w/)

- [MSDN](https://learn.microsoft.com/en-us/cpp/cpp/cpp-language-reference?view=msvc-170)

- [https://isocpp.org/std/the-standard](https://isocpp.org/std/the-standard)

- [https://www.boost.org/doc/](https://www.boost.org/doc/)

- [C++17 Standard](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/n4659.pdf)
