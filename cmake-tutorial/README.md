# CMake学习笔记
```
 ██████╗███╗   ███╗ █████╗ ██╗  ██╗███████╗
██╔════╝████╗ ████║██╔══██╗██║ ██╔╝██╔════╝
██║     ██╔████╔██║███████║█████╔╝ █████╗  
██║     ██║╚██╔╝██║██╔══██║██╔═██╗ ██╔══╝  
╚██████╗██║ ╚═╝ ██║██║  ██║██║  ██╗███████╗
 ╚═════╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝
```

## `CMakeLists.txt`基本结构

```cmake
cmake_minimum_required(VERSION 3.11)

project(Tutorial VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(GLOBAL_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

configure_file(TutorialConfig.h.in ${GLOBAL_INCLUDE_DIR}/TutorialConfig.h)

# 可执行文件
add_executable(Tutorial tutorial.cxx)

target_include_directories(Tutorial PUBLIC ${GLOBAL_INCLUDE_DIR})
```

## Library

```
.
├── CMakeLists.txt              // main cmake
├── MathFunctions
│   ├── CMakeLists.txt          // sub cmake
│   ├── MathFunctions.h
│   └── mysqrt.cxx
├── TutorialConfig.h.in
└── tutorial.cxx
```

`sub cmake`比较简单，只有一行
```cmake
add_library(MathFunctions mysqrt.cxx)
```

`main cmake`需要包括
```cmake
add_subdirectory(MathFunctions)  # 添加目录

target_link_libraries(Tutorial PUBLIC MathFunctions)  # 添加link库

target_include_directories(Tutorial PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/MathFunctions"
                          )  # 添加include dir
```