mincmake_minimum_required(VERSION 3.15)

project(cyberbiology)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(INCLUDES )
set(SOURCES )

add_executable(${PROJECT_NAME} ${INCLUDES} ${SOURCES})

target_include_directories(${PROJECT_NAME include/})

if(CMAKE_BUILD_TYPE MATCHES Debug)
	set_target_properties(${PROJECT_NAME} 
		PROPERTIES EXPORT_COMPILE_COMMANDS true)

	execute_process(
		COMMAND ${CMAKE_COMMAND} -E create_symlink
			${CMAKE_BINARY_DIR}/compile_commands.json
			${CMAKE_SOURCE_DIR}/compile_commands.json
	)
endif()
