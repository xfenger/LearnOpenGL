cmake_minimum_required(VERSION 3.10)

project(LearOpenGL)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
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
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/extrenal/include)

message(${GLFW_LIBRARIES})

add_subdirectory(shaders)

add_library(GLAD "extrenal/src/gl.c")
set(LIBS ${LIBS} GLAD SHARDER)

set(CHAPTERS "")

file(GLOB children RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/learn" "${CMAKE_CURRENT_SOURCE_DIR}/learn/*")

foreach(child IN LISTS children)
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/learn/${child}")
        list(APPEND CHAPTERS ${child})
    endif()
endforeach()

foreach(CHAPTER ${CHAPTERS})
    file(GLOB children RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/learn/${CHAPTER}" "${CMAKE_CURRENT_SOURCE_DIR}/learn/${CHAPTER}/*")
    set(${CHAPTER} "")
    foreach(child IN LISTS children)
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/learn/${CHAPTER}/${child}")
        list(APPEND ${CHAPTER} ${child})
    endif()
    endforeach()
endforeach(CHAPTER)


function(copy_shader_from_sourcess chapter demo)
    file(GLOB SHADERS
            "learn/${chapter}/${demo}/*.vs"
            "learn/${chapter}/${demo}/*.fs"
        )

    foreach(SHADER ${SHADERS})
        get_filename_component(FILE_NAME  ${SHADER} NAME)
        set(SRC_FILE "${SHADER}")
        set(DST_FILE "${CMAKE_SOURCE_DIR}/build/bin/${chapter}/${demo}/${FILE_NAME}")
        message("copy_shader_from_sourcess " ${SRC_FILE} " " ${DST_FILE})
        add_custom_command(
        OUTPUT ${DST_FILE}  
        DEPENDS ${SRC_FILE}
        COMMAND ${CMAKE_COMMAND} -E copy ${SRC_FILE} ${DST_FILE}
        COMMENT "Copying ${SRC_FILE} to ${DST_FILE}"
        )

        add_custom_target(CopyFile_${FILE_NAME} ALL DEPENDS ${DST_FILE})
    endforeach(SHADER)
endfunction(copy_shader_from_sourcess)

function(create_project_from_sources chapter demo)
	file(GLOB SOURCE
            "learn/${chapter}/${demo}/*.h"
            "learn/${chapter}/${demo}/*.cpp"
            "learn/${chapter}/${demo}/*.vs"
            "learn/${chapter}/${demo}/*.fs"
    )

	set(NAME ${demo})
    message( ${chapter}, ${NAME})
    add_executable(${NAME} ${SOURCE})
    target_link_libraries(${NAME} PRIVATE ${LIBS})

    set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin/${chapter}/${demo}/")
endfunction()
foreach(CHAPTER ${CHAPTERS})
    foreach(DEMO ${${CHAPTER}})
        create_project_from_sources(${CHAPTER} ${DEMO})
        copy_shader_from_sourcess(${CHAPTER} ${DEMO})
    endforeach(DEMO)
endforeach(CHAPTER)

