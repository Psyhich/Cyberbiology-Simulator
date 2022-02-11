cmake_minimum_required(VERSION 3.15)

project(cyberbiology)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDES 
	include/map.h 
	include/energy_acceptor.h
	include/entity.h 
	include/entity_extensions.h 
	include/base_entity.h
	include/map_tile.h
)

set(SOURCES 
	src/main.cpp
	src/map.cpp
	src/energy_acceptor.cpp
	src/entity.cpp
	src/entity_extensions.cpp
	src/base_entity.cpp
)

add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC "include/")

if(CMAKE_BUILD_TYPE MATCHES Debug)
	set_target_properties(${PROJECT_NAME} 
		PROPERTIES EXPORT_COMPILE_COMMANDS true)

	execute_process(
		COMMAND ${CMAKE_COMMAND} -E create_symlink
			${CMAKE_BINARY_DIR}/compile_commands.json
			${CMAKE_SOURCE_DIR}/compile_commands.json
	)
endif()
