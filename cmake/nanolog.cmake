include(ExternalProject)

set(NANOLOG_ROOT    ${GLOBAL_VENDOR_DIR}/nanolog)
set(NANOLOG_TMP_DIR    ${GLOBAL_VENDOR_DIR}/nanolog-tmp)
set(NANOLOG_STAMP_DIR    ${GLOBAL_VENDOR_DIR}/nanolog-stamp)

set(NANOLOG_GIT_REPO git@github.com:PlatformLab/NanoLog.git)
set(NANOLOG_GIT_TAG 2a94d70f9d1db4da416053b1b926387fa068a59b)
set(NANOLOG_CONFIGURE echo "config nanolog")
set(NANOLOG_BUILD     cd runtime && ${MAKE_EXE} -j4 && mkdir -p ${GLOBAL_INCLUDE_DIR}/nanolog ${GLOBAL_LIB_DIR} ${GLOBAL_TOOLS_DIR} && cp *.h ${GLOBAL_INCLUDE_DIR}/nanolog && cp *.a ${GLOBAL_LIB_DIR})
set(NANOLOG_INSTALL   echo "install nanolog")

find_program(MAKE_EXE NAMES make)

ExternalProject_Add(nanolog
    GIT_REPOSITORY      ${NANOLOG_GIT_REPO}
    GIT_TAG             ${NANOLOG_GIT_TAG}
    GIT_SHALLOW         ON
    GIT_PROGRESS        ON
    GIT_SUBMODULES      ""

    DOWNLOAD_DIR        ${NANOLOG_ROOT}
    SOURCE_DIR          ${NANOLOG_ROOT}
    BINARY_DIR          ${NANOLOG_ROOT}
    TMP_DIR             ${NANOLOG_TMP_DIR}
    STAMP_DIR           ${NANOLOG_STAMP_DIR}
    
    CONFIGURE_COMMAND   ${NANOLOG_CONFIGURE}
    BUILD_COMMAND       ${NANOLOG_BUILD}
    INSTALL_COMMAND     ${NANOLOG_INSTALL} 
    )
