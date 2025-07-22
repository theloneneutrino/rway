# Source files
set(SOURCES
    rwaytrie.cxx
    main.cxx
)

# Create main executable
add_executable(Main ${SOURCES})

# Create test executables
add_executable(Test1 rwaytrie.cxx test1.cxx)
add_executable(Test2 rwaytrie.cxx test2.cxx)

# Include directories
target_include_directories(Main PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(Test1 PRIVATE ${CMAKE_SOURCE_DIR})
target_include_directories(Test2 PRIVATE ${CMAKE_SOURCE_DIR})
