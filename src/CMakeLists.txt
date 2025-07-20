# Source files
set(SOURCES
    rwaytrie.cxx
    main.cxx
)

# Create main executable
add_executable(main ${SOURCES})

# Create test executables
add_executable(test1 rwaytrie.cxx test1.cxx)
add_executable(test2 rwaytrie.cxx test2.cxx)

# Include directories
target_include_directories(main PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(test1 PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(test2 PRIVATE ${CMAKE_SOURCE_DIR})