include(ExternalProject)

set(NANOLOG_MAJOR_VER 0)
set(NANOLOG_MINOR_VER 91)

set(NANOLOG_VER     ${NANOLOG_MAJOR_VER}.${NANOLOG_MINOR_VER})
set(NANOLOG_ROOT    ${GLOBAL_VENDOR_DIR}/nanolog)
set(NANOLOG_TMP_DIR    ${GLOBAL_VENDOR_DIR}/nanolog-tmp)
set(NANOLOG_STAMP_DIR    ${GLOBAL_VENDOR_DIR}/nanolog-stamp)
# set(NANOLOG_INC_DIR ${NANOLOG_ROOT}/src/nanolog-${NANOLOG_VER}/include)
# set(NANOLOG_LIB_DIR ${NANOLOG_ROOT}/src/nanolog-${NANOLOG_VER}-build)

set(NANOLOG_URL https://github.com/PlatformLab/NanoLog/archive/refs/tags/${NANOLOG_MAJOR_VER}.${NANOLOG_MINOR_VER}.zip)
set(NANOLOG_CONFIGURE echo "config nanolog")
set(NANOLOG_BUILD     cd runtime && ${MAKE_EXE} -j4)
set(NANOLOG_INSTALL   echo "install nanolog")
find_program(MAKE_EXE NAMES make)
ExternalProject_Add(nanolog
    URL                 ${NANOLOG_URL}
    DOWNLOAD_DIR        ${NANOLOG_ROOT}
    SOURCE_DIR          ${NANOLOG_ROOT}
    BINARY_DIR          ${NANOLOG_ROOT}
    TMP_DIR             ${NANOLOG_TMP_DIR}
    STAMP_DIR           ${NANOLOG_STAMP_DIR}

    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    
    CONFIGURE_COMMAND   ${NANOLOG_CONFIGURE}
    BUILD_COMMAND       ${NANOLOG_BUILD}
    INSTALL_COMMAND     ${NANOLOG_INSTALL} 
    )

# set(3RDPARTY_DEPENDENCIES ${3RDPARTY_DEPENDENCIES} nanolog-${NANOLOG_VER})

# if (NOT EXISTS ${NANOLOG_ROOT}/src/nanolog-${NANOLOG_VER})
#     add_custom_target(rescan-nanolog ${CMAKE_COMMAND} ${CMAKE_SOURCE_DIR} DEPENDS nanolog-${NANOLOG_VER})
# else()
#     add_custom_target(rescan-nanolog)
# endif()