ADD_EXECUTABLE(
  all-tests

#  demo-suite.cpp

  sensor-const-suite.cpp
  sensor-random-suite.cpp

  sensor-config-suite.cpp

  mt-queue-suite.cpp
)
TARGET_LINK_LIBRARIES(
  all-tests

  toolcase
  gtest_main 
)

ADD_EXECUTABLE(sensor-config-maybe-mt-safe sensor-config-maybe-mt-safe.cpp)
TARGET_LINK_LIBRARIES(sensor-config-maybe-mt-safe toolcase)

ADD_TEST(
  NAME the-only-test-suite
  COMMAND all-tests
)
