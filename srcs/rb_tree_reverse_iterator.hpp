/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_reverse_iterator.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:20:25 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/14 15:52:24 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_REVERSE_ITERATOR_HPP
# define RB_TREE_REVERSE_ITERATOR_HPP

# include "iterator_traits.hpp"

namespace ft
{

template< class Iterator >
struct rb_tree_reverse_iterator {
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
		rb_tree_reverse_iterator(void) : _base() {}
	
		explicit rb_tree_reverse_iterator(iterator_type it) : _base(it) {}
	
		template< class Iter>
	
		rb_tree_reverse_iterator(rb_tree_reverse_iterator<Iter> const & rev_it) : _base(rev_it.base()) {}
	
		~rb_tree_reverse_iterator(void) {}

		iterator_type	base(void) const
		{ return (this->_base); }

		/*
		 * Operators
		 */
		template< class U >
		rb_tree_reverse_iterator &	operator=(rb_tree_reverse_iterator<U> const & other)
		{
			this->_base = other.base();
			
			return (*this);
		}

		reference	operator*() const
		{ 
			iterator_type	tmp = this->_base;
		
			return *--tmp;
		}

		rb_tree_reverse_iterator	operator+(difference_type n) const
		{ return (rb_tree_reverse_iterator(this->_base - n)); }
		
		rb_tree_reverse_iterator	operator-(difference_type n) const
		{ return (rb_tree_reverse_iterator(this->base() + n)); }

		rb_tree_reverse_iterator &	operator++()
		{
			--this->_base;
			
			return (*this);
		}

		rb_tree_reverse_iterator	operator++(int)
		{
			rb_tree_reverse_iterator	copy = *this;
			++(*this);
			
			return (copy);
		}
		
		rb_tree_reverse_iterator	operator+=(difference_type n)
		{
			this->_base -= n;
			
			return (*this);
		}
		
		rb_tree_reverse_iterator &	operator--()
		{
			++this->_base;
			
			return (*this);
		}

		rb_tree_reverse_iterator	operator--(int)
		{
			rb_tree_reverse_iterator	copy = *this;
			--(*this);
			
			return (copy);
		}
		
		rb_tree_reverse_iterator	operator-=(difference_type n)
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
bool	operator==(const ft::rb_tree_reverse_iterator<Iterator1>& lhs,
	const ft::rb_tree_reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() == lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator!=(const ft::rb_tree_reverse_iterator<Iterator1>& lhs,
	const ft::rb_tree_reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() != lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator<(const ft::rb_tree_reverse_iterator<Iterator1>& lhs,
	const ft::rb_tree_reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() < lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator<=(const ft::rb_tree_reverse_iterator<Iterator1>& lhs,
	const ft::rb_tree_reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() <= lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator>(const ft::rb_tree_reverse_iterator<Iterator1>& lhs,
	const ft::rb_tree_reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() > lhs.base()); }

template< class Iterator1, class Iterator2 >
bool	operator>=(const ft::rb_tree_reverse_iterator<Iterator1>& lhs,
	const ft::rb_tree_reverse_iterator<Iterator2> & rhs)
{ return  (rhs.base() >= lhs.base()); }

template< class Iterator >
rb_tree_reverse_iterator<Iterator>	operator+(
	typename rb_tree_reverse_iterator<Iterator>::difference_type n,
	const rb_tree_reverse_iterator<Iterator> & it)
{ return  (it + n); }

template< class Iterator >
typename rb_tree_reverse_iterator<Iterator>::difference_type operator-(
	const rb_tree_reverse_iterator<Iterator> & lhs,
	const rb_tree_reverse_iterator<Iterator> & rhs)
{ return  (rhs.base() - lhs.base()); }

template< class IteratorL, class IteratorR >
typename rb_tree_reverse_iterator<IteratorL>::difference_type operator-(
	const rb_tree_reverse_iterator<IteratorL> & lhs,
	const rb_tree_reverse_iterator<IteratorR> & rhs)
{ return  (rhs.base() - lhs.base()); }

}

#endif