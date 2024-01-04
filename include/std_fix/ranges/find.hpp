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

#if __cpp_lib_ranges_fold >= 202207L
#   include <algorithm>
#else
#	include <range/v3/algorithm/find.hpp>
#   include <range/v3/algorithm/find_if.hpp>
#	include <range/v3/algorithm/fold.hpp>
	namespace std { namespace ranges { using namespace ::ranges; } }
#endif
