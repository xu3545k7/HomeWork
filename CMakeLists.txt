cmake_minimum_required(VERSION 3.10)
project(LogicSimulator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for source files
include_directories(${PROJECT_SOURCE_DIR}/Device)
include_directories(${PROJECT_SOURCE_DIR}/TextUI)
include_directories(${PROJECT_SOURCE_DIR}/LogicSimulator)

# Collect all source files
file(GLOB DEVICE_SOURCES ${PROJECT_SOURCE_DIR}/Device/*.h ${PROJECT_SOURCE_DIR}/Device/*.cpp)
file(GLOB TEXTUI_SOURCES ${PROJECT_SOURCE_DIR}/TextUI/*.h ${PROJECT_SOURCE_DIR}/TextUI/*.cpp)
file(GLOB SIMULATOR_SOURCES ${PROJECT_SOURCE_DIR}/LogicSimulator/*.h ${PROJECT_SOURCE_DIR}/LogicSimulator/*.cpp)

# Combine all sources for the main program
set(MAIN_SOURCES
    ${DEVICE_SOURCES}
    ${TEXTUI_SOURCES}
    ${SIMULATOR_SOURCES}
    TextUI/main.cpp   # Ensure only main.cpp is included in the main executable
)

# Create the main executable
add_executable(LogicSimulator ${MAIN_SOURCES})

# GoogleTest setup
add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)

# Enable testing
enable_testing()

# Include GoogleTest headers
include_directories(${PROJECT_SOURCE_DIR}/googletest/googletest/include)

# Create a test executable for your tests (without main.cpp)
add_executable(test_logic_simulator Test/test_main.cpp ${DEVICE_SOURCES} ${SIMULATOR_SOURCES})

# Link GoogleTest and pthread to the test executable
target_link_libraries(test_logic_simulator gtest gtest_main pthread)

# Register the testc
add_test(NAME LogicSimulatorTest COMMAND test_logic_simulator)
