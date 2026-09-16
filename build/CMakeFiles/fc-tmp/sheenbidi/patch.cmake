cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for sheenbidi")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "D:/RESONANCE/build/_deps/sheenbidi-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[D:/Cmake/bin/cmake.exe]====] [====[-DSHEENBIDI_DIR=D:/RESONANCE/build/_deps/sheenbidi-src]====] [====[-P]====] [====[D:/RESONANCE/build/_deps/sfml-src/tools/sheenbidi/PatchSheenBidi.cmake]====]
)

endblock()
