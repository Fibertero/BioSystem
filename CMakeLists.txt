cmake_minimum_required(VERSION 3.16)
project(BioSystem CXX)

find_package(raylib 4.0 REQUIRED)

include(cmake/base.cmake) # Set compilation base
include(cmake/warnings.cmake) # Set warnings

add_executable(${PROJECT_NAME})

target_sources(
	${PROJECT_NAME}
	PRIVATE
	# Sources
		src/main.cpp
		src/Cards.cpp
	# Headers
		src/Cards.hpp
		src/Deck.hpp
)

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
	cxx_std_20
)

set_default_warnings(${PROJECT_NAME})

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
		raylib
		m
)
