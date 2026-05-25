cmake_minimum_required(VERSION 3.28)
project(ECS36BBattleShipHumansOnlyTesting) # make sure to update


# add new files to the end of this line
add_executable(${TESTING_NAME}
        test_battleship.cpp
)


find_package(Threads REQUIRED) #needed to find google test
include(FetchContent) #so we can pull in google test
FetchContent_Declare( #declare information about google test
        googletest #its variable name
        #its location on the internet
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main #what branch we want
)

set(RC_ENABLE_GTEST ON) # enable Rapid Check's integration with Google Test
FetchContent_Declare( #declare information about where to find rapid check
        rapidcheck #its variable name
        #its location on the internet
        GIT_REPOSITORY https://github.com/emil-e/rapidcheck.git
        GIT_TAG master #what branch we want
)


#download google test if we don't have it
FetchContent_MakeAvailable(googletest)

FetchContent_MakeAvailable(rapidcheck)




target_link_libraries(${TESTING_NAME}
        PRIVATE
        ${SRC_LIB_NAME} # our src code we want to test
        rapidcheck_gtest # link in rapid test with the google test integrations
        gtest #link in google test
        gmock #link in google mock
        gtest_main #add this one if you want to use google's basic main
)

target_compile_options(${TESTING_NAME} PRIVATE ${CXX_WARNINGS})
