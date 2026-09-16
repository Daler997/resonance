cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for vorbis")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "D:/RESONANCE/build/_deps/vorbis-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[D:/Cmake/bin/cmake.exe]====] [====[-DVORBIS_DIR=D:/RESONANCE/build/_deps/vorbis-src]====] [====[-P]====] [====[D:/RESONANCE/build/_deps/sfml-src/tools/vorbis/PatchVorbis.cmake]====]
)

endblock()
