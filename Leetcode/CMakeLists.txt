cmake_minimum_required(VERSION 3.3)
project(Leetcode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES
        notes.h
        leetcode.h
        546_bottomup.h
        546_topdown.h
        664.h
        664_sol.h
        818_dp.h
        818_queue.h
        862.h
        876.h
        877.h
        878.h
        879.h
        880.h
        881.h
        882_bfs.h
        882_dijkstra.h
        883.h
        884.h
        885.h
        886_dfs.h
        886_union_find.h
        887.h
        888.h
        889.h
        890.h
        891.h
        891_sol.h
        892.h
        893.h
        894.h
        895.h
        896.h
        897.h
        898.h
        899.h
        84.h
        685.h
        900.h
        901.h
        902.h
        903.h
        904.h
        905.h
        906.h
        907.h
        908.h
        910.h
        911.h
        913.h
        914.h
        915.h
        916.h
        921.h
        922.h
        923.h
        924.h
        1252.h
        1253.h
        1254.h
        1255.h
        1263.h
        main.cpp)

add_executable(Leetcode ${SOURCE_FILES})