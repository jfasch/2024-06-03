ADD_EXECUTABLE(read-random-sensor read-random-sensor.cpp)
TARGET_LINK_LIBRARIES(read-random-sensor toolcase)

ADD_EXECUTABLE(message-queue-demo message-queue-demo.cpp)
TARGET_LINK_LIBRARIES(message-queue-demo toolcase)

ADD_EXECUTABLE(latch-demo latch-demo.cpp)
TARGET_LINK_LIBRARIES(latch-demo toolcase)
