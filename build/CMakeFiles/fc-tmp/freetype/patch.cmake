cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for freetype")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "D:/RESONANCE/build/_deps/freetype-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[D:/Cmake/bin/cmake.exe]====] [====[-DFREETYPE_DIR=D:/RESONANCE/build/_deps/freetype-src]====] [====[-P]====] [====[D:/RESONANCE/build/_deps/sfml-src/tools/freetype/PatchFreetype.cmake]====]
)

endblock()
