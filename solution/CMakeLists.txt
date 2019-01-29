set(SOLUTION_INCLUDES_DIR include)
set(SOLUTION_SOURCES_DIR src)

include_directories (
  ${SOLUTION_INCLUDES_DIR}
)

file(GLOB SOLUTION_SOURCES
  "${SOLUTION_INCLUDES_DIR}/*.h"
  "${SOLUTION_SOURCES_DIR}/*.cpp"
)

set(MAIN_LIB_NAME mars-rover)

add_library (${MAIN_LIB_NAME} STATIC ${SOLUTION_SOURCES})

add_subdirectory(utest)
