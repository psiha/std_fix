#pragma once

#include <iterator>

#if __cpp_lib_ranges_as_const < 202207L
#include <cstdint>
#include <concepts>
namespace std
{
//{
    template <input_iterator Iter>
    class [[ clang::trivial_abi ]] basic_const_iterator
    {
    public:
        using iterator_concept  = Iter::iterator_concept;
        using iterator_category = Iter::iterator_concept;
        using value_type        = Iter::value_type const;
        using difference_type   = Iter::difference_type;
        using reference         = value_type &;
        using pointer           = value_type *;

        constexpr basic_const_iterator() noexcept = default;
        constexpr basic_const_iterator( Iter const base ) noexcept : base_( base ) {}

        constexpr reference operator* () const noexcept { return *base_; }
        constexpr pointer   operator->() const noexcept { return std::to_address( base_ ); }
        constexpr reference operator[]( std::integral auto const i ) const noexcept { return base_[ i ]; }

        constexpr basic_const_iterator & operator++(   ) noexcept { ++base_; return *this; }
        constexpr basic_const_iterator   operator++(int) noexcept { return { base_++ }; }
        constexpr basic_const_iterator & operator--(   ) noexcept { --base_; return *this; }
        constexpr basic_const_iterator   operator--(int) noexcept { return { --base_ }; }

        constexpr basic_const_iterator & operator+=( difference_type const x ) noexcept { base_ += x; return *this; }
        constexpr basic_const_iterator & operator-=( difference_type const x ) noexcept { base_ -= x; return *this; }

        constexpr basic_const_iterator   operator+ ( difference_type const x ) const noexcept { return { base_ + x }; }
        constexpr basic_const_iterator   operator- ( difference_type const x ) const noexcept { return { base_ - x }; }

        constexpr difference_type operator-( basic_const_iterator const & other ) const noexcept
        requires requires{ this->base() - other.base(); }
        {
            return this->base() - other.base();
        }

        friend auto operator+( difference_type const diff, basic_const_iterator const & it ) noexcept { return it + diff; }

        constexpr bool operator== ( Iter                 const & other ) const noexcept { return this->base_ == other; }
        constexpr bool operator== ( basic_const_iterator const & other ) const noexcept { return this->base_ == other.base_; }
        constexpr bool operator!= ( basic_const_iterator const & other ) const noexcept { return this->base_ != other.base_; }
        constexpr bool operator<= ( basic_const_iterator const & other ) const noexcept { return this->base_ <= other.base_; }
        constexpr bool operator>= ( basic_const_iterator const & other ) const noexcept { return this->base_ >= other.base_; }
        constexpr bool operator<  ( basic_const_iterator const & other ) const noexcept { return this->base_ <  other.base_; }
        constexpr bool operator>  ( basic_const_iterator const & other ) const noexcept { return this->base_ >  other.base_; }

        constexpr Iter const & base() const &  noexcept { return base_; }
        constexpr Iter         base()       && noexcept { return std::move( base_ ); }

    private:
        Iter base_;
    }; // basic_const_iterator

    template <class Iter> [[ nodiscard ]] constexpr auto *   to_address( basic_const_iterator<Iter> const & const_iter ) noexcept { return   to_address( const_iter.base() ); }
    template <class Iter> [[ nodiscard ]] constexpr auto * __to_address( basic_const_iterator<Iter> const & const_iter ) noexcept { return __to_address( const_iter.base() ); }
} // namespace std
#endif
