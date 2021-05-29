#	 Upanix - An x86 based Operating System
#	 Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
#																			 
#	 This program is free software: you can redistribute it and/or modify
#	 it under the terms of the GNU General Public License as published by
#	 the Free Software Foundation, either version 3 of the License, or
#	 (at your option) any later version.
#																			 
#	 This program is distributed in the hope that it will be useful,
#	 but WITHOUT ANY WARRANTY; without even the implied warranty of
#	 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	 GNU General Public License for more details.
#																			 
#	 You should have received a copy of the GNU General Public License
#	 along with this program.  If not, see <http://www.gnu.org/licenses/
cmake_minimum_required(VERSION 3.15)
project(UpanixTests)

set(OUTPUT_DIR ${PROJECT_SOURCE_DIR}/out)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_FLAGS "-fpermissive")

set(UPANLIB_SOURCE_DIR ${PROJECT_SOURCE_DIR}/../upanlibs)
include_directories(${PROJECT_SOURCE_DIR}/libutest)

include_directories(${PROJECT_SOURCE_DIR}/upanlibstests/mocks)

include_directories(${UPANLIB_SOURCE_DIR}/libustd/infra)
include_directories(${UPANLIB_SOURCE_DIR}/libustd/algo)
include_directories(${UPANLIB_SOURCE_DIR}/libustd/ds)
include_directories(${UPANLIB_SOURCE_DIR}/libustd/mem)
include_directories(${UPANLIB_SOURCE_DIR}/libustd/mthread)

#LIBUTEST
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./libutest -name '*.cpp' | grep -v CMakeFile" OUTPUT_VARIABLE LIB_UTEST_CPP_SRC)
string(REPLACE "\n" ";" LIB_UTEST_CPP_SRC ${LIB_UTEST_CPP_SRC})
add_library(utest STATIC ${LIB_UTEST_CPP_SRC})

#LIBUPANLIBSTESTS
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find ./upanlibstests -name '*.cpp' | grep -v CMakeFile" OUTPUT_VARIABLE LIB_UPANLIBSTESTS_CPP_SRC)
string(REPLACE "\n" ";" LIB_UPANLIBSTESTS_CPP_SRC ${LIB_UPANLIBSTESTS_CPP_SRC})
add_library(upanlibstests STATIC ${LIB_UPANLIBSTESTS_CPP_SRC})

#upantests
execute_process(COMMAND bash -c "cd ${PROJECT_SOURCE_DIR}; find . -name 'main.cpp' | grep -v CMakeFile" OUTPUT_VARIABLE TEST_SRC)
string(REPLACE "\n" ";" TEST_SRC ${TEST_SRC})
add_executable(upantests "${TEST_SRC}")
add_dependencies(upantests utest)
add_dependencies(upantests upanlibstests)
target_link_libraries(upantests utest)
target_link_libraries(upantests -Wl,--whole-archive ${PROJECT_SOURCE_DIR}/out/libupanlibstests.a -Wl,--no-whole-archive)

link_directories(${OUTPUT_DIR})
