
CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(gb28181gateway)


#Add the source in project root directory
AUX_SOURCE_DIRECTORY(. DIRSRCS)


#Add header file include directories
INCLUDE_DIRECTORIES(/src )


SET(CMAKE_CXX_STANDARD 17)


# Target
ADD_EXECUTABLE(gb28181gateway main.cpp SipUA.cpp SipHeader.cpp)


TARGET_LINK_LIBRARIES(gb28181gateway osipparser2 eXosip2 pthread boost)