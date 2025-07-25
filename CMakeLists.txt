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

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-ggdb3)  
    add_compile_options(-fno-omit-frame-pointer)  
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

set(LIBS ${GLFW_LIBRARIES} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL dl pthread freetype)
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

include_directories(${CMAKE_SOURCE_DIR}/extrenal/include)

message(${GLFW_LIBRARIES})

add_subdirectory(shaders)

add_library(GLAD "extrenal/src/gl.c")
set(LIBS ${LIBS} GLAD SHARDER)

set(1.GettingStarted
    1.HelloWindow
    2.HelloTriangle
    3.1Shaders
    3.2ShadersClass
)

set(CHAPTERS
1.GettingStarted
)


function(create_project_from_sources chapter demo)
	file(GLOB SOURCE
            "learn/${chapter}/${demo}/*.h"
            "learn/${chapter}/${demo}/*.cpp"
            "learn/${chapter}/${demo}/*.vs"
            "learn/${chapter}/${demo}/*.fs"
    )


    file(GLOB SHADERS
        "learn/${chapter}/${demo}/*.vs"
         "learn/${chapter}/${demo}/*.fs"
    )

    foreach(SHADER ${SHADERS})
        #复制文件
        file(COPY ${SHADER} DESTINATION ${CMAKE_SOURCE_DIR}/build/bin/${chapter}/${demo}/)
    endforeach(SHADER)
 
	set(NAME ${demo})
    message( ${chapter}, ${NAME})
    add_executable(${NAME} ${SOURCE})
    target_link_libraries(${NAME} ${LIBS})
    set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin/${chapter}/${demo}/")
endfunction()
foreach(CHAPTER ${CHAPTERS})
    foreach(DEMO ${${CHAPTER}})
        create_project_from_sources(${CHAPTER} ${DEMO})
    endforeach(DEMO)
endforeach(CHAPTER)

