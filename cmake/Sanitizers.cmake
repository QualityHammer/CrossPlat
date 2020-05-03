function(enable_sanitizers target)
  if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES
      ".*Clang")
    option(ENABLE_COVERAGE "Enable coverage reporting for gcc/clang" FALSE)

    if (ENABLE_COVERAGE)
      target_compile_options(project_options INTERFACE --coverage -O0 -g)
      target_link_libraries(project_options INTERFACE --coverage)
    endif()

    set(SANITIZERS "")

    option(ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" FALSE)
    if (ENABLE_SANITIZER_ADDRESS)
      list(APPEND SANIZIZERS "memory")
    endif()

    option(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR
      "Enable undefined behabior sanitizer" FALSE)
    if (ENABLE_SANITIZER_UNDEFINED_BEHAVIOR)
      list(APPEND SANITIZERS "undefined")
    endif()

    option(ENABLE_SANITIZER_THREAD "Enable thread sanitizer" FALSE)
    if (ENABLE_SANITIZER_THREAD)
      list(APPEND SANITIZERS "thread")
    endif()

    list (JOIN SANITIZERS "," LIST_OF_SANITIZERS)
  endif()

  if (LIST_OF_SANITIZERS)
    if (NOT "${LIST_OF_SANITIZERS}" STREQUAL "")
      target_compile_options(${target}
        INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
      target_link_libraries(${target}
        INTERFACE -fsanitize=${LIST_OF_SANITIZERS})
    endif()
  endif()

endfunction(enable_sanitizers)
