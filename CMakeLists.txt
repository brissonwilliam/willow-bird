# CMakeList.txt : CMake project for willow-bird, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("willow-bird")

# glfw instructions 
find_package(OpenGL REQUIRED)

include_directories(
	"lib/glm"
	"lib/glfw"
)

include_directories(BEFORE SYSTEM "lib/assimp/include")

link_directories(
	"lib/glfw"
	"lib/assimp"
)

# Add source to this project's executable.
file(GLOB src_assets CONFIGURE_DEPENDS "src/assets/*.h" "src/assets/*.cpp")
file(GLOB src_config CONFIGURE_DEPENDS "src/config/*.h" "src/config/*.cpp")
file(GLOB src_engine CONFIGURE_DEPENDS "src/engine/*.h" "src/engine/*.cpp")
file(GLOB src_ui CONFIGURE_DEPENDS "src/ui/*.h" "src/ui/*.cpp")

add_executable (willow-bird 
	"src/main.cpp"	
	"src/main.h"
	"src/game.cpp"
	"src/game.h"
	${src_assets}
	${src_config}
	${src_engine}
	${src_ui}
)

target_link_libraries(willow-bird "glfw3.lib")
target_link_libraries(willow-bird "assimp-vc142-mtd.lib")
target_link_libraries(willow-bird OpenGL::GL)

# TODO: Add tests and install targets if needed.
