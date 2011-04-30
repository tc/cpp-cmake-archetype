PROJECT(calc)

cmake_minimum_required(VERSION 2.8)

ENABLE_TESTING()

set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Find the Boost package graph (Boost Graph Library)
# Obviously this isn't required to build the example and so it is commented.
# Uncomment if you truly need to use Boost libraries.
# find_package(Boost COMPONENTS graph REQUIRED)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(CppUnit REQUIRED)


# Main executable
SET(SOURCES src/main/cpp/Calculator.cpp)

ADD_LIBRARY(calc SHARED ${SOURCES})		

ADD_EXECUTABLE(calcexe src/main/cpp/main.cpp)

target_link_libraries(calcexe calc)

install(TARGETS calcexe calc
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
)


# Unit testing driver
include_directories("${PROJECT_SOURCE_DIR}/src/main/cpp/include")
set(UnitTests_SRCS src/test/cpp/main.cpp
		   src/test/cpp/CalculatorTest.cpp)

add_executable(UnitTester ${UnitTests_SRCS})
TARGET_LINK_LIBRARIES(UnitTester ${CPPUNIT_LIBRARY}
				 calc
				 dl)

# Add coverage options for CI
if(COVERAGE)
	set_target_properties(calc calcexe UnitTester PROPERTIES
						  COMPILE_FLAGS "-fprofile-arcs -ftest-coverage"
						  LINK_FLAGS "-coverage")
endif(COVERAGE)


# Choose the packaging
# include("cmake/CPackConfigRPM.cmake")
# include("cmake/CPackConfigDEB.cmake")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")

# Use default variables when not specified
include(CPack)

# Include resources available
#install(FILES src/main/resources/Calculator.properties DESTINATION share)
