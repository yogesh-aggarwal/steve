cmake_minimum_required(VERSION 3.20)

# ----------------------------------------------------------------------------------------------------------------------
# ---- Helper Functions ------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

function(SUCCESS message)
   message("[SUCCESS] ${message}")
endfunction()

function(LINK_LIBRARY libVendorPath libName)
   add_subdirectory("Vendor/${libVendorPath}")
   target_link_libraries(${PROJECT_NAME} PRIVATE ${libName})
   include_directories("Vendor/${libVendorPath}/include")
   SUCCESS("Linked library: ${libName}")
endfunction()

# ----------------------------------------------------------------------------------------------------------------------
# ---- Compile-Time Defines --------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

set(LEARNOPENGL_DEBUG_AS_APPLICATION ON)
# set(LEARNOPENGL_DEBUG_AS_APPLICATION OFF)

if(LEARNOPENGL_DEBUG_AS_APPLICATION)
   add_compile_definitions(LEARNOPENGL_DEBUG_AS_APPLICATION)
endif()

add_compile_definitions(
   DEBUG

   # LEARNOPENGL_DISABLE_LOGGING
   # LEARNOPENGL_DISABLE_LOGGING_OUTPUT_TO_FILE
)

# ----------------------------------------------------------------------------------------------------------------------
# ---- Project Setup ---------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

project(LEARNOPENGL)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pthread")
set(NO_DEFAULT_PATH true)
set(CMAKE_MAKE_PROGRAM "make -j 16")

# ----------------------------------------------------------------------------------------------------------------------
# ---- Files -----------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

FILE(GLOB_RECURSE LEARNOPENGL_HEADER_FILES Source/*.hpp)
FILE(GLOB_RECURSE LEARNOPENGL_SOURCE_FILES Source/*.cpp)
FILE(GLOB_RECURSE LEARNOPENGL_TEMPLATE_FILES Source/*.tcc)

set(LEARNOPENGL_ALL_FILES ${LEARNOPENGL_HEADER_FILES} ${LEARNOPENGL_SOURCE_FILES} ${LEARNOPENGL_TEMPLATE_FILES})

# ----------------------------------------------------------------------------------------------------------------------
# ---- Product ---------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

include_directories(Source)

if(LEARNOPENGL_DEBUG_AS_APPLICATION)
   add_executable(${PROJECT_NAME} ${LEARNOPENGL_ALL_FILES})
else()
   add_library(${PROJECT_NAME} ${LEARNOPENGL_ALL_FILES})
endif()

# ----------------------------------------------------------------------------------------------------------------------
# ---- Link Libraries --------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

message("[(---- Linking Libraries ----)]")

# GLFW3
add_subdirectory("Vendor/glfw")
include_directories("Vendor/glfw/include")
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)
SUCCESS("Linked library: glfw")

# GLM
include_directories("Vendor/glm")
SUCCESS("Linked library: GLM")

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} ${OPENGL_LIBRARIES})
include_directories(${OPENGL_INCLUDE_DIRS})
SUCCESS("Linked library: OpenGL")

message("[(---- Done Linking Libraries ----)]\n")

# ----------------------------------------------------------------------------------------------------------------------
# ---- PCHs ------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

FILE(GLOB_RECURSE LEARNOPENGL_PCH_FILES Source/Core/*)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${LEARNOPENGL_PCH_FILES})

# ----------------------------------------------------------------------------------------------------------------------
# ---- Installation ----------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
set(CMAKE_INSTALL_PREFIX "/usr")
install(DIRECTORY Source/LearnOpenGL
   DESTINATION include
   FILES_MATCHING
   PATTERN "*.hpp"
   PATTERN "*.tcc")
install(TARGETS ${PROJECT_NAME}
   LIBRARY DESTINATION lib)
