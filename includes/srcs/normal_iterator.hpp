/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 09:37:29 by arguilla          #+#    #+#             */
/*   Updated: 2022/08/27 18:14:58 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NORMAL_ITERATOR_HPP
# define NORMAL_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{

template< class Iterator, class Container >
class	normal_iterator {
	protected:
		Iterator	_current;
		typedef ft::iterator_traits< Iterator >	_traits_type;
	
	public:
		typedef	Iterator	iterator_type;
		typedef typename	_traits_type::iterator_category	iterator_category;
		typedef typename	_traits_type::value_type		value_type;
		typedef typename	_traits_type::difference_type	difference_type;
		typedef typename	_traits_type::reference			reference;
		typedef typename	_traits_type::pointer			pointer;

		
		normal_iterator() : _current(Iterator()) {}
		explicit normal_iterator(Iterator const & src) : _current(src) {}
		template< class Iter >
		normal_iterator(normal_iterator<Iter, typename ft::enable_if<
				(ft::is_same<Iter, typename Container::pointer>::value),
				Container >::type> const & src)
		: _current(src.base()) {}

		Iterator const &	base(void) const { return (this->_current); }

		normal_iterator &	operator=(normal_iterator const & rhs)
		{
			if (this != &rhs)
				this->_current = rhs.base();
			return (*this);
		}
	
		reference	operator*(void) const { return (*this->_current); }
		pointer	operator->(void) const { return (this->_current); }
		normal_iterator &	operator++(void)
		{
			++_current;
			return (*this);
		}

		normal_iterator	operator++(int)
		{
			normal_iterator	tmp = *this;
			++this->_current;
			return (tmp);
			return (normal_iterator(this->_current++));
		}
	
		normal_iterator &	operator--(void)
		{
			--_current;
			return (*this);
		}
		
		normal_iterator	operator--(int)
		{
			return (normal_iterator(this->_current--));
		}

		reference	operator[](difference_type n) const
		{
			return (*(*this + n));
		}

		normal_iterator &	operator+=(difference_type n)
		{
			this->_current += n;
			return (*this);
		}

		normal_iterator	operator+(difference_type n) const
		{
			return (normal_iterator(this->_current + n));
		}

		normal_iterator &	operator-=(difference_type n)
		{
			this->_current -= n;
			return (*this);
		}
		
		normal_iterator	operator-(difference_type n) const
		{
			return (normal_iterator(this->_current - n));
		}
};

template< class IteratorL, class IteratorR, class Container >
inline bool operator==(normal_iterator< IteratorL, Container > const & lhs,
		normal_iterator< IteratorR, Container > const & rhs)
{
	return (lhs.base() == rhs.base());
}

template< class Iterator, class Container >
inline bool	operator==(normal_iterator< Iterator, Container > const & lhs,
		normal_iterator< Iterator, Container > const & rhs)
{
	return (lhs.base() == rhs.base());
}

template< class IteratorL, class IteratorR, class Container >
inline bool operator!=(normal_iterator< IteratorL, Container > const & lhs,
		normal_iterator< IteratorR, Container > const & rhs)
{
	return (lhs.base() != rhs.base());
}

template< class Iterator, class Container >
inline bool operator!=(normal_iterator< Iterator, Container > const & lhs,
		normal_iterator< Iterator, Container > const & rhs)
{
	return (lhs.base() != rhs.base());
}

template< class IteratorL, class IteratorR, class Container >
inline bool operator<(normal_iterator< IteratorL, Container > const & lhs,
		normal_iterator< IteratorR, Container > const & rhs)
{
	return (lhs.base() < rhs.base());
}

template< class Iterator, class Container >
inline bool operator<(normal_iterator< Iterator, Container >
		const & lhs,
		normal_iterator<Iterator, Container >
		const & rhs)
{
	return (lhs.base() < rhs.base());
}

template< class IteratorL, class IteratorR, class Container >
inline bool operator>(normal_iterator<IteratorL, Container >
		const & lhs,
		normal_iterator<IteratorR, Container > const & rhs)
{
	return (lhs.base() > rhs.base());
}

template< class Iterator, class Container >
inline bool operator>(normal_iterator<Iterator, Container > const & lhs,
		normal_iterator<Iterator, Container > const & rhs)
{
	return (lhs.base() > rhs.base());
}

template< class IteratorL, class IteratorR, class Container >
inline bool operator>=(normal_iterator<IteratorL, Container > const & lhs,
		normal_iterator<IteratorR, Container > const & rhs)
{
	return (lhs.base() >= rhs.base());
}

template< class Iterator, class Container >
inline bool operator>=(normal_iterator<Iterator, Container > const & lhs,
		normal_iterator<Iterator, Container > const & rhs)
{
	return (lhs.base() >= rhs.base());
}

template< class IteratorL, class IteratorR, class Container >
inline bool operator<=(normal_iterator<IteratorL, Container > const & lhs,
		normal_iterator< IteratorR, Container > const & rhs)
{
	return (lhs.base() <= rhs.base());
}

template< class Iterator, class Container >
inline bool operator<=(normal_iterator< Iterator, Container > const & lhs,
		normal_iterator< Iterator, Container > const & rhs)
{
	return (lhs.base() <= rhs.base());
}

template< class Iterator, class Container >
inline normal_iterator< Iterator, Container >	operator+(
		typename normal_iterator< Iterator, Container >::difference_type n,
		normal_iterator< Iterator, Container > const & rhs)
{
	return (normal_iterator< Iterator, Container >(rhs.base() + n));
}

template< class IteratorL, class IteratorR, class Container >
inline typename normal_iterator< IteratorL, Container >::difference_type	operator-(
		normal_iterator< IteratorL, Container> const & lhs,
		normal_iterator< IteratorR, Container> const & rhs)
{
	return (lhs.base() - rhs.base());
}


template< class Iterator, class Container >
inline typename normal_iterator< Iterator, Container >::difference_type	operator-(
		normal_iterator< Iterator, Container> const & lhs,
		normal_iterator< Iterator, Container> const & rhs)
{
	return (lhs.base() - rhs.base());
}

}

#endif
