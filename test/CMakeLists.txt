cmake_minimum_required(VERSION 2.8)

PROJECT(Bluezpp CXX)
SET(CMAKE_CXX_FLAGS "-std=gnu++17 -pthread -lbluetooth")

include_directories(
  includes
)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/includes
)

set(CMAKE_BUILD_TYPE Debug)

set(SOURCES
  ${CMAKE_SOURCE_DIR}/srcs/main.cpp

  ${CMAKE_SOURCE_DIR}/../srcs/Adapter/Adapter.cpp
  ${CMAKE_SOURCE_DIR}/../srcs/Adapter/AdapterManager.cpp
  ${CMAKE_SOURCE_DIR}/../srcs/Adapter/BluetoothAddress.cpp

  ${CMAKE_SOURCE_DIR}/../srcs/Bluez/MGMT/BluezMGMT.cpp
  ${CMAKE_SOURCE_DIR}/../srcs/Bluez/HCI/BluezHCI.cpp
)

include_directories(${HEADERS})

add_executable(${PROJECT_NAME} ${SOURCES})

install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
)
