#-----------------------------------------------------------------------------------------------------------#
# Collect all source files
#-----------------------------------------------------------------------------------------------------------#

FILE(GLOB_RECURSE STEVE_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/steve/**/*.hpp)
FILE(GLOB_RECURSE STEVE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/steve/**/*.cpp)
FILE(GLOB_RECURSE STEVE_TEMPLATES ${CMAKE_CURRENT_SOURCE_DIR}/steve/**/*.tcc)

#-----------------------------------------------------------------------------------------------------------#
# Create a static library for steve
#-----------------------------------------------------------------------------------------------------------#

add_library(steve SHARED ${STEVE_HEADERS} ${STEVE_SOURCES} ${STEVE_TEMPLATES})

# Specify include directories
target_include_directories(steve PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Define precompiled header
target_precompile_headers(steve PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/steve/core/pch)

#-----------------------------------------------------------------------------------------------------------#
# Add compile definitions if needed
#-----------------------------------------------------------------------------------------------------------#

target_compile_definitions(steve PRIVATE DEBUG)

#-----------------------------------------------------------------------------------------------------------#
# Link libraries
#-----------------------------------------------------------------------------------------------------------#

# curl
find_package(CURL REQUIRED)
include_directories(${PROJECT_NAME} PRIVATE ${CURL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CURL_LIBRARIES})

# archive
find_package(LibArchive REQUIRED)
include_directories(${PROJECT_NAME} PRIVATE ${LibArchive_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LibArchive_LIBRARIES})

# GLAD
add_subdirectory("../vendor/glad" "${CMAKE_BINARY_DIR}/glad")
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/glad/include)

# GLFW3
add_subdirectory("../vendor/glfw" "${CMAKE_BINARY_DIR}/glfw")
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/glfw/include)

# GLM
add_subdirectory("../vendor/glm" "${CMAKE_BINARY_DIR}/glm")
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/glm)

# yaml-cpp
add_subdirectory("../vendor/yaml-cpp" "${CMAKE_BINARY_DIR}/yaml-cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/yaml-cpp/include)

# nanoid_cpp
add_subdirectory("../vendor/nanoid_cpp" "${CMAKE_BINARY_DIR}/nanoid_cpp")
target_link_libraries(${PROJECT_NAME} PRIVATE nanoid)
target_include_directories(${PROJECT_NAME} PUBLIC ../vendor/nanoid_cpp/include)

#-----------------------------------------------------------------------------------------------------------#
# Change the library type to SHARED for a dynamic library
#-----------------------------------------------------------------------------------------------------------#

set_target_properties(${PROJECT_NAME} PROPERTIES
   LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib
   RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin
)

#-----------------------------------------------------------------------------------------------------------#
