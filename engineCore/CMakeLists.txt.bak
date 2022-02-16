cmake_minimum_required(VERSION 2.22.1 FATAL_ERROR)

set(CORE_PROJECT_NAME EngineCORE)

set(CORE_PUBLIC_INCLUDES
	includes/CORE/Application.hpp
	includes/CORE/log.hpp
)

set(CORE_PUBLIC_SOURCES
	src/CORE/Application.cpp
)

add_library(${CORE_PROJECT_NAME} STATIC
	${CORE_PUBLIC_INCLUDES}
	${CORE_PUBLIC_SOURCES}
	)

target_include_directories(${CORE_PROJECT_NAME} PUBLIC includes)
target_compile_features(${CORE_PROJECT_NAME} PUBLIC cxx_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${CORE_PROJECT_NAME} PRIVATE spdlog)