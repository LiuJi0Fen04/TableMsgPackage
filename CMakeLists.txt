cmake_minimum_required(VERSION 3.1.0)

project(table_msg VERSION 1.0)

FILE(GLOB_RECURSE CLASS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
foreach(item ${CLASS})
    message("cpp: ${item}")
endforeach()
add_library(TableMsg SHARED ${CLASS})

target_include_directories(TableMsg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# config your library
set(TableMsg_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(TableMsg_LIB_DIRS ${PROJECT_SOURCE_DIR}/lib)
set(TableMsg_VERSION 1.0)
LINK_DIRECTORIES(${TableMsg_LIB_DIRS})
set(TableMsg_LIB TableMsg)
configure_file(TableMsgConfig.cmake.in ${PROJECT_SOURCE_DIR}/lib/TableMsgConfig.cmake)

FILE(GLOB_RECURSE CFG ${CMAKE_CURRENT_SOURCE_DIR}/config/*.*)
install(FILES ${CFG} DESTINATION config)
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/class.h DESTINATION include)
install(FILES ${PROJECT_SOURCE_DIR}/lib/TableMsgConfig.cmake DESTINATION lib)
install(TARGETS ${TableMsg_LIB} DESTINATION lib)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGING_VERSION_MAJOR "${table_msg_VERSION_MAJOR}")
set(CPACK_PACKAGING_VERSION_MINOR "${table_msg_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)