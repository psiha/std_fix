#pragma once

#include <iterator>

#if __cpp_lib_ranges_as_const < 202207L
namespace std
{
    template <input_iterator Iter>
    class basic_const_iterator : private Iter
    {
    public:
        using iterator_concept = Iter::iterator_concept;
        using value_type       = Iter::value_type;
        using difference_type  = Iter::difference_type;

        using Iter::Iter;
        basic_const_iterator( Iter const base ) noexcept : Iter( base ) {}

        auto const & operator* () const noexcept { return Iter::operator* (); }
        auto const * operator->() const noexcept { return Iter::operator->(); }
        auto const & operator[]( std::size_t const i ) const noexcept { return Iter::operator[]( i ); }

        // constraints not supported on using directives so...
        basic_const_iterator & operator++(   ) noexcept { Iter::operator++(); return *this; }
        basic_const_iterator   operator++(int) noexcept { auto current{ *this }; Iter::operator++(0); return current; }
        basic_const_iterator & operator--(   ) noexcept { Iter::operator--(); return *this; }
        basic_const_iterator   operator--(int) noexcept { auto current{ *this }; Iter::operator--(0); return current; }

        basic_const_iterator & operator+=( auto const x ) noexcept { static_cast<Iter &>( *this ) += x; return *this; }
        basic_const_iterator & operator-=( auto const x ) noexcept { static_cast<Iter &>( *this ) -= x; return *this; }

        basic_const_iterator   operator+ ( auto const x ) noexcept { auto res{ *this }; res += x; return res; }
        basic_const_iterator   operator- ( auto const x ) noexcept { auto res{ *this }; res -= x; return res; }

        bool operator== ( Iter                 const & other ) const noexcept { return static_cast<Iter const &>( *this ) == other; }
        bool operator== ( basic_const_iterator const & other ) const noexcept { return *this == static_cast<Iter const &>( other ); }
        auto operator<=>( basic_const_iterator const & other ) const noexcept
        requires requires( Iter a, Iter b ){ a <=> b; }
        {
            return static_cast<Iter const &>( *this ) <=> static_cast<Iter const &>( other );
        }
    }; // basic_const_iterator
} // namespace std
#endif
