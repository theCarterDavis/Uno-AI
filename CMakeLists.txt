cmake_minimum_required(VERSION 3.26)
project(HarnessedAI)

set(CMAKE_CXX_STANDARD 17)

add_executable(HarnessedAI main.cpp
        AI.cpp
        AI.h
        Card.cpp
        Card.h
        cobos3.cpp
        cobos3.h
        jennyGoodAI.cpp
        jennyGoodAI.h
        Player.cpp
        Player.h
        TestAI.cpp
        TestAI.h
        v001.cpp
        v001.h
        v002.cpp
        v002.h
        v003.cpp
        v003.h
        v004.cpp
        v004.h
        v005.cpp
        v005.h
        v006.cpp
        v006.h
        v007.cpp
        v007.h
        v008.cpp
        v008.h
)
