cmake_minimum_required(VERSION 3.1.0)

project(CFG)
function(p_cut input num output)
    if(${num} EQUAL 2)
        string(REGEX REPLACE "(.*)/(.*)/(.*)" "\\1" op  ${input})
        set(${output} ${op} PARENT_SCOPE)
    elseif(${num} EQUAL 1)
        string(REGEX REPLACE "(.*)/(.*)" "\\1" op  ${input})
        set(${output} ${op} PARENT_SCOPE)
    else()
        message(STATUS "error param")
    endif()
endfunction()

p_cut(${CMAKE_CURRENT_SOURCE_DIR} 1 OUTPUT_PREFIX)

message(STATUS "> ${OUTPUT_PREFIX}")

# config your library
set(TableMsg_INCLUDE_DIRS ${OUTPUT_PREFIX}/include)
set(TableMsg_LIB_DIRS ${OUTPUT_PREFIX}/lib)
set(TableMsg_VERSION 1.0)
LINK_DIRECTORIES(${TableMsg_LIB_DIRS})
set(TableMsg_LIB TableMsg)
configure_file(TableMsgConfig.cmake.in ${OUTPUT_PREFIX}/lib/TableMsgConfig.cmake)
