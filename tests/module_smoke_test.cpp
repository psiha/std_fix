// Smoke test for the optional std_fix module (STD_FIX_MODULE).
//
// On a modern STL every one of std_fix's feature-test-macro gates is already closed (verified
// empirically against this toolchain's STL before writing this file), so the module purview
// carries none of std_fix's own conditional bodies - it degrades to a transparent pass-through
// of the real standard-library declarations. What this test actually exercises is the thing
// unique to modularizing this particular header set: std_fix reopens `namespace std` itself, so
// a TU that both `import`s the module AND textually #includes the same std_fix headers (exactly
// as tests/compile_time_tests.cpp does, unmodularized) must not conflict or redeclare anything.
import std_fix;

#include <std_fix/bit>
#include <std_fix/concepts>
#include <std_fix/memory>

//------------------------------------------------------------------------------

static_assert( std::bit_cast< int >( 0.f ) == 0 );
static_assert( std::bit_width( 127U ) == 7U );

static_assert
(
     std::convertible_to<          int, float > &&
    !std::convertible_to< char const *, float >
);

struct Base    {                    };
struct Derived : Base { explicit Derived( int ) {} };
static_assert( std::derived_from< Derived, Base > );
static_assert( std::destructible< Derived > );
static_assert( std::constructible_from< Derived, int > );

static_assert( std::integral< int > && !std::integral< float > );

int main()
{
    alignas( int ) unsigned char storage[ sizeof( int ) ];
    int * const p{ std::construct_at< int >( reinterpret_cast< int * >( storage ), 42 ) };
    bool const ok{ ( *p == 42 ) && ( std::bit_cast< int >( 0.f ) == 0 ) };
    return ok ? 0 : 1;
}
