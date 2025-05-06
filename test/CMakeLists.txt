include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(test_clocktime test_clocktime.cpp ../src/ClockTime.cpp)
target_include_directories(test_clocktime PRIVATE ../include)
target_link_libraries(test_clocktime gtest gtest_main)

add_executable(test_clubmanager test_clubmanager.cpp ../src/ClockTime.cpp ../src/ClubManager.cpp)
target_include_directories(test_clubmanager PRIVATE ../include)
target_link_libraries(test_clubmanager gtest gtest_main)