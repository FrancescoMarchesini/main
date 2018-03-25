cmake_minimum_required(VERSION 2.8)

#setto il nome del progetto
project(glxDisplay)
message("Nome Progetto : ${PROJECT_NAME}")

#metto il flag per il c++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#aggiungo cartellaper lib esterne
add_subdirectory (external)

include_directories(/usr/include/glib-2.0 /usr/include/libxml2 /usr/lib/aarch64-linux-gnu/glib-2.0/include/)
include_directories(external/glfw-3.2.1/include/ external/glm-0.9.8/ data/shader/ common/)

add_executable(${PROJECT_NAME} 
	App/main.cpp
	App/glxDisplay.cpp
	App/glxDisplay.h
	App/loadImage.h
	App/loadImage.cpp
	data/shader/text2d.vertexshader
	data/shader/text2d.fragmentshader
        common/shader.h
        common/shader.cpp
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
		GL
		GLEW
                glfw
)

