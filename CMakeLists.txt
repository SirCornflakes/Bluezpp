cmake_minimum_required(VERSION 2.8)

PROJECT(Bluezpp CXX)
SET(CMAKE_CXX_FLAGS "-std=gnu++17 -pthread -lbluetooth")

include_directories(
  includes
)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/includes
)

set(SOURCES
  ${CMAKE_SOURCE_DIR}/srcs/Adapter/Adapter.cpp
  ${CMAKE_SOURCE_DIR}/srcs/Adapter/AdapterManager.cpp
  ${CMAKE_SOURCE_DIR}/srcs/Adapter/BluetoothAddress.cpp

  ${CMAKE_SOURCE_DIR}/srcs/Bluez/MGMT/BluezMGMT.cpp
  ${CMAKE_SOURCE_DIR}/srcs/Bluez/HCI/BluezHCI.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)
