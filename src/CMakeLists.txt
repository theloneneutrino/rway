# Add source to this project's executable.
add_library(rwaytrie SHARED "rwaytrie.cxx")

add_executable(Test1 "test1.cxx")
add_executable(Test2 "test2.cxx")

target_link_libraries(Test1 PUBLIC rwaytrie)
target_link_libraries(Test2 PUBLIC rwaytrie)
