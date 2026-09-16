cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for mbedtls")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "D:/RESONANCE/build/_deps/mbedtls-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[D:/Cmake/bin/cmake.exe]====] [====[-DMBEDTLS_DIR=D:/RESONANCE/build/_deps/mbedtls-src]====] [====[-P]====] [====[D:/RESONANCE/build/_deps/sfml-src/tools/mbedtls/PatchMbedTLS.cmake]====]
)

endblock()
