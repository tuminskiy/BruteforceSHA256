cmake_minimum_required(VERSION 3.5.0)
project(BruteforceSHA256)

add_executable(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON

  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/debug/bin"
  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/release/bin"
)

set(HEADERS
  include/rangenumber.hpp
  include/detail/rangenumber_impl.hpp
  include/ns26.hpp
  include/bruteforcetask.hpp
  include/threadpool.hpp
  include/detail/threadpool_impl.hpp
  include/sha256.hpp
)

set(SOURCES src/main.cpp
  src/ns26.cpp
  src/bruteforcetask.cpp
  src/threadpool.cpp
  src/sha256.cpp
)


target_include_directories(${PROJECT_NAME} PRIVATE include)

target_sources(${PROJECT_NAME} PRIVATE ${HEADERS} ${SOURCES})
