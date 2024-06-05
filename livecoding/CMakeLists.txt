ADD_EXECUTABLE(hello-world hello-world.cpp)

ADD_EXECUTABLE(new-cpp new-cpp.cpp)
ADD_EXECUTABLE(thread-easy thread-easy.cpp)

ADD_EXECUTABLE(auto-ptr auto-ptr.cpp)
ADD_EXECUTABLE(ptr-decay ptr-decay.cpp)
ADD_EXECUTABLE(lambda lambda.cpp)
ADD_EXECUTABLE(map map.cpp)

ADD_SUBDIRECTORY(smart-pointers)

ADD_SUBDIRECTORY(threads)

ADD_EXECUTABLE(timestamps timestamps.cpp)
