# CMakeList.txt : CMake project for willow-bird, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.30)

project ("willow-bird")

# honnestly idk what this does but it fixes some shit with clang (lsp)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# load OpenGL
find_package(OpenGL REQUIRED)

# load freetype
find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})
include_directories(/usr/include/freetype2)

# load glew
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# load glm
find_package(glm REQUIRED)

# other includes
# include_directories(
# 	"lib/glm"
# 	"lib/glfw"
# )
# 
# link_directories(
# 	"lib/glfw"
# 	"lib/assimp"
# )

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

target_link_libraries(willow-bird glfw OpenGL::GL ${GLEW_LIBRARIES} OpenGL::GL Freetype::Freetype glm::glm)

