add_library (tcpserver_lsrk utserver.c)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (tcpserver_lsrk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})