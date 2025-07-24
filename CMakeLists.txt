cmake_minimum_required(VERSION 3.10)

project(LearOpenGL)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LearnOpenGL)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)
# pkg_check_modules(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set(LIBS ${GLFW_LIBRARIES} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype)
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

message(${GLFW_LIBRARIES})

add_library(GLAD "extrenal/src/gl.c")
set(LIBS ${LIBS} GLAD)

set(CHAPTERS
HelloWindow
HelloTriangle
)


function(create_project_from_sources chapter)
	file(GLOB SOURCE
            "learn/${chapter}/*.h"
            "learn/${chapter}/*.cpp"
    )
   message( ${SOURCE}, ${chapter})
	set(NAME ${chapter})
    add_executable(${NAME} ${SOURCE})
    target_link_libraries(${NAME} ${LIBS})
    set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin/${chapter}")
endfunction()
foreach(CHAPTER ${CHAPTERS})
    create_project_from_sources(${CHAPTER} )
endforeach(CHAPTER)

include_directories(${CMAKE_SOURCE_DIR}/extrenal/include)