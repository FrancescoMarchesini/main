cmake_minimum_required(VERSION 2.8)

#setto il nome del progetto
project(glxDisplay)
message("Nome Progetto : ${PROJECT_NAME}")

#metto il flag per il c++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#aggiungo cartellaper lib esterne
add_subdirectory (external)

include_directories(/usr/include/gstreamer-1.0 /usr/lib/aarch64-linux-gnu/gstreamer-1.0/include /usr/include/glib-2.0 /usr/include/libxml2 /usr/lib/aarch64-linux-gnu/glib-2.0/include/)
include_directories(external/glfw-3.2.1/include/ external/glm-0.9.8/ data/shader/ common/)

add_executable(${PROJECT_NAME} 
	App/main.cpp
        App/App.h
        App/App.cpp
        common/glfwDisplay/glxDisplay.cpp
        common/glfwDisplay/glxDisplay.h
        common/openGL/Quad.h
        common/openGL/Quad.cpp
        common/openGL/loadImageOnTexture.h
        common/openGL/loadImageOnTexture.cpp
        common/openGL/shader.h
        common/openGL/shader.cpp
        common/openGL/openGLText2D.cpp
        common/openGL/openGLText2D.h
        common/Gstreamer/gstreamer.h
        common/Gstreamer/gstreamer.cpp
        common/stb_image.h
        data/shader/text2d.vertexshader
        data/shader/text2d.fragmentshader
        data/shader/quad.vertexshader
        data/shader/quad.fragmentshader

)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
		GL
		GLEW
                glfw
                gstreamer-1.0
                gstapp-1.0
)

