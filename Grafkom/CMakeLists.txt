# CMakeList.txt : CMake project for Grafkom, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_library (Point "Renderable/Point/Point.cpp" "Renderable/Point/Point.h")
add_library (Line "Renderable/Line/Line.cpp" "Renderable/Line/Line.h")
add_library (Shape "Renderable/Shape/Shape.cpp" "Renderable/Shape/Shape.h")
add_library (Color "Renderable/Properties/Color/Color.cpp" "Renderable/Properties/Color/Color.h")
add_library (Renderable "Renderable/Renderable.cpp" "Renderable/Renderable.h")
add_library (Buffer "Buffer/Buffer.cpp" "Buffer/Buffer.h")
add_library (Renderer "Renderer/Renderer.cpp" "Renderer/Renderer.h")
add_executable (Grafkom "Grafkom.cpp" "Grafkom.h")

target_link_libraries (Grafkom Point Line Shape Color Renderable Buffer Renderer)
# TODO: Add tests and install targets if needed.
