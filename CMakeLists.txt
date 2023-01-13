cmake_minimum_required(VERSION 3.16)
project(pexeso)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fsanitize=address -fsanitize=leak -g")

file(GLOB src
        src/*/*.hpp
        src/*/*.cpp
        )

add_executable(pexeso ${src} main.cpp src/board.h src/board.cpp src/game.cpp src/window.cpp)


# Enable threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(pexeso Threads::Threads)

#file(GLOB tests-src
#        ${src}
#        test/*.cpp
#        )
#
#add_executable(tests ${tests-src})
#
#enable_testing()
#add_test(NAME tests COMMAND tests)


# Load src files AND tests files
file(GLOB tests-src
        ${src}
        test/*.cpp
        )

# All tests executable
add_executable(tests ${tests-src}  src/board.h src/board.cpp src/game.cpp src/window.cpp)

# Enable threads in tests
target_link_libraries(tests Threads::Threads)

enable_testing()
add_test(NAME tests COMMAND tests)



