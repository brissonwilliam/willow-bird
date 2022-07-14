# CMakeList.txt : CMake project for willow-bird, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("willow-bird")

# glfw instructions 
find_package(OpenGL REQUIRED)

include_directories("src/glfw")
include_directories("src/controls")
include_directories("src/ui")
include_directories("src/engine")
include_directories("src/config")
link_directories("src/glfw")
link_directories("src/controls")
link_directories("src/ui")
link_directories("src/engine")
link_directories("src/config")

# Add source to this project's executable.
add_executable (willow-bird 
	"src/main.cpp"	
	"src/main.h"
	"src/game.cpp"
	"src/game.h"
	"src/config/options.h"	
	"src/controls/keys.cpp"
	"src/controls/keys.h"
	"src/ui/window.h"
	"src/ui/window.cpp"
	"src/engine/renderer.cpp"
	"src/engine/renderer.h")

target_link_libraries(willow-bird "glfw3.lib")
target_link_libraries(willow-bird OpenGL::GL)

# TODO: Add tests and install targets if needed.
