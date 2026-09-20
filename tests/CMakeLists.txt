# The existing compile_time_tests.cpp (previously never wired into any build) - a plain
# textual-include build. It carries no runtime component (pure static_assert, no main()), so it
# just needs to be part of the default build graph: a build failure here is the test failing.
add_library( std_fix_compile_time_tests OBJECT compile_time_tests.cpp )
target_link_libraries( std_fix_compile_time_tests PRIVATE std_fix )
