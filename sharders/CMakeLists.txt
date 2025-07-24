file(GLOB_RECURSE  SOURCE
"*.h"
"*.hpp"
"*.cpp"
)
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${CMAKE_CXX_FLAGS_DEBUG})
add_library(SHARDER STATIC  ${SOURCE} )

target_include_directories(SHARDER PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR},
    ${CMAKE_CURRENT_SOURCE_DIR}/include # 使包含路径对使用者可见
)
