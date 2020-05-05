add_executable(${PROJECT_NAME}
	Main.cpp
)

add_subdirectory(common/common)
add_subdirectory(server)
add_subdirectory(client)

target_link_libraries(${PROJECT_NAME}
  cplat_client
  cplat_common
  cplat_server
)
