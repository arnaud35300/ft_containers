/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:16:52 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/14 18:00:31 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{

template< class Iterator >
struct reverse_iterator {
	public:
		typedef Iterator														iterator_type;
		typedef typename	ft::iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename	ft::iterator_traits<Iterator>::value_type			value_type;
		typedef typename	ft::iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename	ft::iterator_traits<Iterator>::pointer				pointer;
		typedef typename	ft::iterator_traits<Iterator>::reference			reference;
	private:
		iterator_type	_base;
	public:
		/*
		 * Constructors
		 */
		reverse_iterator(void) : _base() {}
		
		explicit reverse_iterator(iterator_type it) : _base(it) {}
		
		template< class Iter>
		
		reverse_iterator(reverse_iterator<Iter> const & rev_it) : _base(rev_it.base()) {}
		
		~reverse_iterator(void) {}

		iterator_type	base(void) const
		{ return (this->_base); }

		/*
		 * Operators
		 */

		template< class U >
		reverse_iterator &	operator=(reverse_iterator<U> const & other) {
			this->_base = other.base();
			
			return (*this);
		}

		reference	operator*(void) const {
			iterator_type	copy = this->_base;

			return (*(--copy));
		}

		reverse_iterator	operator+(difference_type n) const
		{ return (reverse_iterator(this->_base - n)); }
		
		reverse_iterator	operator-(difference_type n) const
		{ return (reverse_iterator(this->base() + n)); }

		reverse_iterator &	operator++()
		{
			--this->_base;
			
			return (*this);
		}

		reverse_iterator	operator++(int)
		{
			reverse_iterator	copy = *this;
			++(*this);
			
			return (copy);
		}
		
		reverse_iterator	operator+=(difference_type n)
		{
			this->_base -= n;
			
			return (*this);
		}
		
		reverse_iterator &	operator--()
		{
			++this->_base;
			
			return (*this);
		}

		reverse_iterator	operator--(int)
		{
			reverse_iterator	copy = *this;
			--(*this);
			
			return (copy);
		}
		
		reverse_iterator	operator-=(difference_type n)
		{
			this->_base += n;
			
			return (*this);
		}

		pointer	operator->(void) const
		{ return &(this->operator*()); }

		reference	operator[](difference_type n) const
		{ return (*this->operator+(n)); }
};

template< class Iterator1, class Iterator2 >
bool	operator==(const ft::reverse_iterator<Iterator1>& lhs,
	const ft::reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() == lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator!=(const ft::reverse_iterator<Iterator1>& lhs,
	const ft::reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() != lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator<(const ft::reverse_iterator<Iterator1>& lhs,
	const ft::reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() < lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator<=(const ft::reverse_iterator<Iterator1>& lhs,
	const ft::reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() <= lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator>(const ft::reverse_iterator<Iterator1>& lhs,
	const ft::reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() > lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator>=(const ft::reverse_iterator<Iterator1>& lhs,
	const ft::reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() >= lhs.base()); }

template< class Iterator >
reverse_iterator<Iterator>	operator+(
	typename reverse_iterator<Iterator>::difference_type n,
	const reverse_iterator<Iterator> & it)
{ return  (it + n); }

template< class Iterator >
typename reverse_iterator<Iterator>::difference_type operator-(
	const reverse_iterator<Iterator> & lhs,
	const reverse_iterator<Iterator> & rhs)
{ return  (rhs.base() - lhs.base()); }

template< class IteratorL, class IteratorR >
typename reverse_iterator<IteratorL>::difference_type operator-(
	const reverse_iterator<IteratorL> & lhs,
	const reverse_iterator<IteratorR> & rhs)
{ return  (rhs.base() - lhs.base()); }

}

#endif
