cmake_minimum_required(VERSION 3.9)
project(Lab4_5)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -O2")
add_executable(Lab4_5 main.cpp ThreadSafePriorityQueue.h Writer.cpp Writer.h ThreadSafeQueue.h Factorizator.cpp Factorizator.h ThreadPool.cpp ThreadPool.h Program.cpp Program.h Exceptions/WrongArguments.h)