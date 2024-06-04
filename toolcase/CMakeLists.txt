ADD_LIBRARY(
  toolcase

  sensor.h
  sensor-const.h
  sensor-const.cpp
  sensor-random.h
  sensor-random.cpp

  sensor-config.h
  sensor-config.cpp
)

TARGET_INCLUDE_DIRECTORIES(
  toolcase
  PUBLIC
  .
)
