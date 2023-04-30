include_directories(${GLOBAL_INCLUDE_DIR})

file(GLOB EFF_FILES ch*.cpp)

foreach(_eff_file ${EFF_FILES})
  get_filename_component(_file_prefix ${_eff_file} NAME_WE)
  set(_exe_name "eff_${_file_prefix}")
  add_executable(${_exe_name} ${_eff_file} utils.cpp)
endforeach()


