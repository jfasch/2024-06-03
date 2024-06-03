ADD_LIBRARY(
  sensors

  sensor.h
  sensor-const.h
  sensor-const.cpp
  sensor-random.h
  sensor-random.cpp
)  

ADD_EXECUTABLE(sensor-unique-ptr sensor-unique-ptr.cpp)
TARGET_LINK_LIBRARIES(sensor-unique-ptr sensors)

ADD_EXECUTABLE(unique-ptr unique-ptr.cpp)
TARGET_LINK_LIBRARIES(unique-ptr sensors)

ADD_EXECUTABLE(weak-ptr weak-ptr.cpp)
TARGET_LINK_LIBRARIES(weak-ptr sensors)
