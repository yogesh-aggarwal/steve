# Add executable for `run`
add_executable(run main.cpp)

# Link the steve library (from the `source` folder)
target_link_libraries(run PRIVATE steve)
