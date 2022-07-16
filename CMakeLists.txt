# CMakeList.txt : CMake project for willow-bird, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("willow-bird")

# glfw instructions 
find_package(OpenGL REQUIRED)

include_directories(
	"src/glfw"
	"src/ui"
	"src/engine"
	"src/config"
)
link_directories(
	"src/glfw"
	"src/ui"
	"src/engine"
	"src/config"
)

# Add source to this project's executable.
add_executable (willow-bird 
	"src/main.cpp"	
	"src/main.h"
	"src/engine/fps.cpp"
	"src/engine/fps.h"
	"src/engine/inputs.cpp"
	"src/engine/inputs.h"
	"src/engine/state.cpp"
	"src/engine/state.h"
	"src/engine/renderer.cpp"
	"src/engine/renderer.h"
	"src/game.cpp"
	"src/game.h"
	"src/ui/window.h"
	"src/ui/window.cpp"
	"src/config/options.h"	
)

target_link_libraries(willow-bird "glfw3.lib")
target_link_libraries(willow-bird OpenGL::GL)

# TODO: Add tests and install targets if needed.
