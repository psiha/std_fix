cmake_minimum_required( VERSION 3.28 )
project( std_fix LANGUAGES CXX )

add_library( std_fix INTERFACE )
add_library( Psi::StdFix ALIAS std_fix )
target_include_directories( std_fix INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include" )
target_compile_features( std_fix INTERFACE cxx_std_23 )

include( module.cmake )

if ( PROJECT_IS_TOP_LEVEL )
    enable_testing()
    add_subdirectory( tests )
endif()
