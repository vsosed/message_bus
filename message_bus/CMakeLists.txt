file(GLOB_RECURSE MB_SOURCES "src/*.cpp")
file(GLOB_RECURSE MB_HEADERS "include/*.h")

add_library(message_bus STATIC EXCLUDE_FROM_ALL ${MB_SOURCES} ${MB_HEADERS})
#target_include_directories(test PRIVATE ${YOUR_DIRECTORY})
target_include_directories(message_bus PUBLIC include)
