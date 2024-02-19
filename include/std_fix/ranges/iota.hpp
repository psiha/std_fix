////////////////////////////////////////////////////////////////////////////////
///
/// Workaround for missing ranges functionality
/// (granular include version)
/// (uses ranges-v3 as a fallback and assumes it to be in the include path)
///
/// (c) Copyright Domagoj Saric.
///
///  Use, modification and distribution are subject to the
///  Boost Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
///
///  See http://www.boost.org for most recent version.
///
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include <version>

#if __cpp_lib_ranges >= 201911L
#   include <ranges>
#else
#   include <range/v3/view/iota.hpp>
    namespace std { using namespace ::ranges::cpp20; }
#endif
