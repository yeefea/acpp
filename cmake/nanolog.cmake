include(FetchContent)

FetchContent_Declare(
    nanolog
    URL     https://github.com/PlatformLab/NanoLog/archive/refs/tags/0.91.zip
    SOURCE_DIR ${GLOBAL_VENDOR_DIR}/nanolog
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
)
# FetchContent_MakeAvailable(nanolog)
execute_process(
    COMMAND make
    WORKING_DIRECTORY ${GLOBAL_VENDOR_DIR}/nanolog/runtime
)

# include(ExternalProject)


# set(NANOLOG_MAJOR_VER 1)
# set(NANOLOG_MINOR_VER 10)
# set(NANOLOG_PATCH_VER 0)
# set(NANOLOG_URL_HASH  SHA256=697f91700237dbae2326b90469be32b876b2b44888302afbc7aceb68bcfe8224)

# set(NANOLOG_VER     ${NANOLOG_MAJOR_VER}.${NANOLOG_MINOR_VER}.${NANOLOG_PATCH_VER})
# set(NANOLOG_ROOT    ${GLOBAL_VENDOR_DIR}/nanolog)
# set(NANOLOG_INC_DIR ${NANOLOG_ROOT}/src/nanolog-${NANOLOG_VER}/include)
# set(NANOLOG_LIB_DIR ${NANOLOG_ROOT}/src/nanolog-${NANOLOG_VER}-build)

# set(NANOLOG_URL https://github.com/gabime/nanolog/archive/refs/tags/v${NANOLOG_VER}.tar.gz)
# set(NANOLOG_CONFIGURE cd ${NANOLOG_ROOT}/src/nanolog-${NANOLOG_VER} && mkdir -p build && cd build && cmake ..)
# set(NANOLOG_BUILD     cd ${NANOLOG_ROOT}/src/nanolog-${NANOLOG_VER} && cd build && make CXXFLAGS+='-fPIC' -j4)
# set(NANOLOG_INSTALL   echo "install nanolog")

# ExternalProject_Add(nanolog-${NANOLOG_VER}
#     URL               ${NANOLOG_URL}
#     URL_HASH          ${NANOLOG_URL_HASH} 
#     DOWNLOAD_NAME     nanolog-${NANOLOG_VER}.tar.gz
#     PREFIX            ${NANOLOG_ROOT}
#     CONFIGURE_COMMAND #{NANOLOG_CONFIGURE} 
#     BUILD_COMMAND     #{NANOLOG_BUILD} 
#     INSTALL_COMMAND   #{NANOLOG_INSTALL} 
#     )

# set(3RDPARTY_DEPENDENCIES ${3RDPARTY_DEPENDENCIES} nanolog-${NANOLOG_VER})

# if (NOT EXISTS ${NANOLOG_ROOT}/src/nanolog-${NANOLOG_VER})
#     add_custom_target(rescan-nanolog ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS nanolog-${NANOLOG_VER})
# else()
#     add_custom_target(rescan-nanolog)
# endif()