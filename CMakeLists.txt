project(lsssl)

cmake_minimum_required(VERSION 3.10)

add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)

aux_source_directory(src/ls/ssl SRC)

aux_source_directory(sample SRC_SAMPLE)

include_directories(include)

link_directories(/usr/local/lib)

add_library(lsssl SHARED ${SRC})

add_executable(testcase ${SRC} ${SRC_SAMPLE})

target_link_libraries(testcase lsexception lsio lsnet ssl crypto lsbuffer lshttp lstime lslogger lsitem lscopyableitem lscstring lsjson)

install(TARGETS lsssl DESTINATION lib)
install(DIRECTORY include/ls/ssl DESTINATION include/ls)

