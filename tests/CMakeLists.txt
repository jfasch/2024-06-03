ADD_EXECUTABLE(
  all-tests

  demo-suite.cpp

  sensor-const-suite.cpp
  sensor-random-suite.cpp

#  sensor-config-suite.cpp
)

TARGET_LINK_LIBRARIES(
  all-tests

  toolcase
  gtest_main 
)
