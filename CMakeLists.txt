cmake_minimum_required(VERSION 3.28)
project(ECS36BBattleShipWithAI) # make sure to update

set(CMAKE_CXX_STANDARD 23)
set(CXX_WARNINGS -Wall -Werror -Wextra)

# make sure to update
set(SRC_LIB_NAME ECS36BBattleShipWithAILib)
set(EXE_NAME ECS36BBattleShipWithAIExe)
set(TESTING_NAME ECS36BBattleShipWithAITests)

add_subdirectory(src)
add_subdirectory(testing)
