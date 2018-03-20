cmake_minimum_required(VERSION 2.8)

#setto il nome del progetto
project(glxDisplay)
message("Nome Progetto : ${PROJECT_NAME}")

#metto il flag per il c++ 11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


###########################################
#creazione della libraria dinamica
###########################################
add_library(${PROJECT_NAME} SHARED 
	src/glxDisplay.cpp
)

target_include_directories(${PROJECT_NAME}
	PUBLIC
		${PROJECT_SOURCE_DIR/include}	
)

###########################################
#creazione dell'eseguibile
###########################################
set(SOURCES 
	src/main.cpp
)

include_directories(${PROJECT_SOURCE_DIR/include})
include_directories(/usr/include/glib-2.0 /usr/include/libxml2 /usr/lib/aarch64-linux-gnu/glib-2.0/include/)

set(HEADERS
        include/glxDisplay.h
)

add_executable(glxDisplayBin ${SOURCES} ${HEADERS})

#all'eseguibile link la lib
target_include_directories(glxDisplayBin 
	PRIVATE
		${PROJECT_NAME} 
		GL
		GLEW
)
