# The existing compile_time_tests.cpp (previously never wired into any build) - a plain
# textual-include build. It carries no runtime component (pure static_assert, no main()), so it
# just needs to be part of the default build graph: a build failure here is the test failing.
add_library( std_fix_compile_time_tests OBJECT compile_time_tests.cpp )
target_link_libraries( std_fix_compile_time_tests PRIVATE std_fix )

# Module smoke test, only built when STD_FIX_MODULE is turned on (see module.cmake).
if ( STD_FIX_MODULE AND TARGET std_fix_module )
    add_executable( std_fix_module_smoke_test EXCLUDE_FROM_ALL "${CMAKE_CURRENT_SOURCE_DIR}/module_smoke_test.cpp" )
    target_link_libraries( std_fix_module_smoke_test PRIVATE Psi::StdFixModule )
    set_target_properties( std_fix_module_smoke_test PROPERTIES CXX_SCAN_FOR_MODULES ON DISABLE_PRECOMPILE_HEADERS ON )
    add_test( NAME std_fix_module_smoke_test COMMAND std_fix_module_smoke_test )
endif()
