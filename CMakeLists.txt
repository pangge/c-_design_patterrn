#SET(CMAKE_C_COMPILER   /usr/bin/gcc)
#SET(CMAKE_CXX_COMPILER /usr/bin/g++)
project(UnitTest CXX)
cmake_minimum_required(VERSION 3.2)

set(UNIT_TEST_ROOT .)

include_directories(.)
include_directories(./pattern)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# recursively fetch files
function(fetch_files_with_suffix_recursively search_dir suffix outputs)
	file(GLOB_RECURSE ${outputs} ${search_dir} "*.${suffix}") 
	set(${outputs} ${${outputs}} PARENT_SCOPE)
endfunction()

#list(APPEND source main.cc;)

fetch_files_with_suffix_recursively(${UNIT_TEST_ROOT}/test_case  "cpp" source)

#message(STATUS ${source})

foreach(SRC_NAME ${source})
	#unpack the dir "/"
	string(REPLACE "/" ";" SEXY_LIST ${SRC_NAME})
	list(GET SEXY_LIST -1 TEST_CASE_NAME)
	#get the file name without suffix
	string(REPLACE "." ";" SEXY_LIST ${TEST_CASE_NAME})
	list(GET SEXY_LIST 0 TEST_CASE_NAME)
	add_executable(${TEST_CASE_NAME}  ${SRC_NAME})
	#add_executable(${TEST_CASE_NAME} $<TARGET_OBJECTS:ANAKIN_TEST_OBJS> ${ANAKIN_TEST_CUDA_OBJS})
	#target_link_libraries(${TEST_CASE_NAME} ${ANAKIN_SELF_LIBS})
	#message(STATUS "ANAKIN_SELF_LIBS : ${ANAKIN_SELF_LIBS}")
	#set_target_properties(${TEST_CASE_NAME} PROPERTIES
	#						RUNTIME_OUTPUT_DIRECTORY
	#						${PROJECT_SOURCE_DIR}/output/unit_test)
endforeach()
