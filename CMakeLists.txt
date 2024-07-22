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

set(STEVE_DEBUG_AS_APPLICATION ON)
# set(STEVE_DEBUG_AS_APPLICATION OFF)

if(STEVE_DEBUG_AS_APPLICATION)
   add_compile_definitions(STEVE_DEBUG_AS_APPLICATION)
endif()

add_compile_definitions(
   DEBUG

   # STEVE_DISABLE_LOGGING
   # STEVE_DISABLE_LOGGING_OUTPUT_TO_FILE
)

# ----------------------------------------------------------------------------------------------------------------------
# ---- Project Setup ---------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

project(STEVE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pthread")
set(NO_DEFAULT_PATH true)
set(CMAKE_MAKE_PROGRAM "make -j 16")

# ----------------------------------------------------------------------------------------------------------------------
# ---- Files -----------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

FILE(GLOB_RECURSE STEVE_HEADER_FILES Source/*.hpp)
FILE(GLOB_RECURSE STEVE_SOURCE_FILES Source/*.cpp)
FILE(GLOB_RECURSE STEVE_TEMPLATE_FILES Source/*.tcc)

set(STEVE_ALL_FILES ${STEVE_HEADER_FILES} ${STEVE_SOURCE_FILES} ${STEVE_TEMPLATE_FILES})

# ----------------------------------------------------------------------------------------------------------------------
# ---- Product ---------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

include_directories(Source)

if(STEVE_DEBUG_AS_APPLICATION)
   add_executable(${PROJECT_NAME} ${STEVE_ALL_FILES})
else()
   add_library(${PROJECT_NAME} ${STEVE_ALL_FILES})
endif()

# ----------------------------------------------------------------------------------------------------------------------
# ---- Link Libraries --------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

message("[(---- Linking Libraries ----)]")

# GLFW3
add_subdirectory("Vendor/glfw")
include_directories("Vendor/glfw/include")
target_link_libraries(${CMAKE_PROJECT_NAME} glfw)
SUCCESS("Linked library: GLFW3")

# GLM
include_directories("Vendor/glm")
SUCCESS("Linked library: GLM")

# GLAD
add_subdirectory("Vendor/glad")
target_link_libraries(${CMAKE_PROJECT_NAME} glad)
SUCCESS("Linked library: GLAD")

# nanoid_cpp
add_subdirectory("Vendor/nanoid_cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} nanoid)
include_directories("Vendor/nanoid_cpp/inc")

# yaml-cpp
add_subdirectory("Vendor/yaml-cpp")
target_link_libraries(${CMAKE_PROJECT_NAME} yaml-cpp)
include_directories("Vendor/yaml-cpp/include")

message("[(---- Done Linking Libraries ----)]\n")

# ----------------------------------------------------------------------------------------------------------------------
# ---- PCHs ------------------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------

# FILE(GLOB_RECURSE STEVE_PCH_FILES Source/Steve/Core/*.hpp)
# target_precompile_headers(${PROJECT_NAME} PUBLIC ${STEVE_PCH_FILES})

# ----------------------------------------------------------------------------------------------------------------------
# ---- Installation ----------------------------------------------------------------------------------------------------
# ----------------------------------------------------------------------------------------------------------------------
set(CMAKE_INSTALL_PREFIX "/usr")
install(DIRECTORY Source/Steve
   DESTINATION include
   FILES_MATCHING
   PATTERN "*.hpp"
   PATTERN "*.tcc")
install(TARGETS ${PROJECT_NAME}
   LIBRARY DESTINATION lib)
