option(USE_IMGUI "Enable compilation of ImGui" OFF)
option(USE_SDL "Enable compilation of SDL" OFF)

if (USE_IMGUI)
  message("Using ImGui")
  add_subdirectory(imgui)
endif()

if (USE_SDL)
  message("Using SDL")
  add_subdirectory(sdl)
endif()

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
