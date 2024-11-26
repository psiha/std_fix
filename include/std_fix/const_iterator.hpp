#pragma once

#include <iterator>

#if __cpp_lib_ranges_as_const < 202207L
namespace std
{
    template <input_iterator Iter>
    class basic_const_iterator : private Iter
    {
    public:
        using iterator_concept  = Iter::iterator_concept;
        using iterator_category = Iter::iterator_concept;
        using value_type        = Iter::value_type const;
        using difference_type   = Iter::difference_type;
        using reference         = value_type &;
        using pointer           = value_type *;

        using Iter::Iter;
        basic_const_iterator( Iter const base ) noexcept : Iter( base ) {}

        reference operator* () const noexcept { return Iter::operator* (); }
        pointer   operator->() const noexcept { return Iter::operator->(); }
        reference operator[]( std::size_t const i ) const noexcept { return Iter::operator[]( i ); }

        basic_const_iterator & operator++(   ) noexcept { Iter::operator++(); return *this; }
        basic_const_iterator   operator++(int) noexcept { auto current{ *this }; Iter::operator++(0); return current; }
        basic_const_iterator & operator--(   ) noexcept { Iter::operator--(); return *this; }
        basic_const_iterator   operator--(int) noexcept { auto current{ *this }; Iter::operator--(0); return current; }

        basic_const_iterator & operator+=( difference_type const x ) noexcept { static_cast<Iter &>( *this ) += x; return *this; }
        basic_const_iterator & operator-=( difference_type const x ) noexcept { static_cast<Iter &>( *this ) -= x; return *this; }

        basic_const_iterator   operator+ ( difference_type const x ) const noexcept { auto res{ *this }; res += x; return res; }
        basic_const_iterator   operator- ( difference_type const x ) const noexcept { auto res{ *this }; res -= x; return res; }

        difference_type operator-( basic_const_iterator const & other ) const noexcept
        requires requires{ this->base() - other.base(); }
        {
            return this->base() - other.base();
        }

        friend auto operator+( difference_type const diff, basic_const_iterator const & it ) noexcept { return it + diff; }

        reference operator[]( std::integral auto const x ) const noexcept { return Iter::operator[]( x ); }

        bool operator== ( Iter                 const & other ) const noexcept { return static_cast<Iter const &>( *this ) == other; }
        bool operator== ( basic_const_iterator const & other ) const noexcept { return *this == static_cast<Iter const &>( other ); }
        auto operator<=>( basic_const_iterator const & other ) const noexcept
        requires requires( Iter a, Iter b ){ a <=> b; }
        {
            return static_cast<Iter const &>( *this ) <=> static_cast<Iter const &>( other );
        }

        constexpr Iter const & base() const &  noexcept { return *this; }
        constexpr Iter         base()       && noexcept { return std::move( static_cast<Iter &>( *this ) ); }
    }; // basic_const_iterator
} // namespace std
#endif
