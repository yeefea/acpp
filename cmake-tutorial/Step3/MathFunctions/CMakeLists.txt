add_library(MathFunctions mysqrt.cxx)

# TODO 1: State that anybody linking to MathFunctions needs to include the
# current source directory, while MathFunctions itself doesn't.
# Hint: Use target_include_directories with the INTERFACE keyword

# 加了这个target_include_directories，上层就不用include了
target_include_directories(MathFunctions INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
