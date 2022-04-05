add_executable (tcpserverapp utserver.c)
add_executable (tcpclientapp tclient.c)
add_executable (udpclientapp uclient.c)

install(TARGETS tcpserverapp DESTINATION bin)
install(TARGETS tcpclientapp DESTINATION bin)
install(TARGETS udpclientapp DESTINATION bin)