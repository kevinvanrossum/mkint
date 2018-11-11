# Author: Jeroen de Haas <jah.dehaas@avans.nl>
cmake_policy(SET CMP0048 NEW)
cmake_minimum_required(VERSION 3.1.3)
project(libkmint
        VERSION 0.0.1
        DESCRIPTION "A simple library for use within the AI course at Avans University"
        LANGUAGES CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(MSVC)
  add_compile_options(/W3)

  if(NOT DEFINED SDL2_DIR)
    set(SDL2_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2")
  endif()
  if(NOT DEFINED SDL2_IMAGE_DIR)
    set(SDL2_IMAGE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../SDL2_image")
  endif(NOT DEFINED SDL2_IMAGE_DIR)




  find_package(SDL2 REQUIRED)
  find_package(SDL2_IMAGE REQUIRED)
else() # Assume GCC/Clang on a Unix os
  include(FindPkgConfig)
  find_package(SDL2 REQUIRED)
  pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
  add_compile_options(-Wall -Wpedantic -Werror)
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
endif()

add_library(kmint SHARED 
    src/kmint/map/map.cpp
    src/kmint/random.cpp
    src/kmint/play/stage.cpp
    src/kmint/play/actor.cpp
    src/kmint/play/image_drawable.cpp
    src/kmint/ui/app.cpp
    src/kmint/ui/window.cpp
    src/kmint/ui/renderer.cpp
    src/kmint/ui/events/event.cpp
    src/kmint/ui/sdl/texture.cpp
    src/kmint/graph/graph.cpp
    #src/kmint/math/vector2d.cpp
    src/kmint/math/angle.cpp)

target_compile_features(kmint PUBLIC cxx_std_17)
if (MSVC)
  set_target_properties(kmint PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS true)
endif()
set_target_properties(kmint PROPERTIES
                            VERSION ${PROJECT_VERSION}
                            SOVERSION 1)
target_link_libraries(kmint PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_include_directories(kmint PUBLIC include)
target_include_directories(kmint PRIVATE 
    src
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS})


find_package(GTest)
if(GTest_FOUND)
    enable_testing()
    add_executable(kmint_tests
                   test/util/wrapped_iterator.cpp
                   test/graph/graph.cpp
                   test/math/size.cpp
                   test/map/map.cpp
                   test/play/stage.cpp
                   test/ui/events/modifier.cpp
    )
    target_compile_features(kmint_tests PUBLIC cxx_std_17)
    target_include_directories(kmint_tests PUBLIC include)
    target_link_libraries(kmint_tests kmint GTest::GTest GTest::Main)
    add_test(AllTests kmint_tests)
endif()

install(DIRECTORY include/kmint
  DESTINATION include/kmint
  FILES_MATCHING PATTERN "*.hpp")
install(TARGETS kmint
  DESTINATION lib)
