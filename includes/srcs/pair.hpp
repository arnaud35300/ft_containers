/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:14:20 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/14 10:38:44 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PAIR_HPP
# define FT_PAIR_HPP

/*
 * pair
*/

namespace ft
{

template< class T1, class T2>
struct pair {
	public:
		typedef	T1	first_type;
		typedef	T2	second_type;
	
		T1	first;
		T2	second;
	
		pair(void) : first(), second() {}
		template< class U1, class U2 >
		pair(const pair< U1, U2 > & p) : first(p.first), second(p.second) {}
		pair(const pair & p) : first(p.first), second(p.second) {}

		pair(T1 const & x, T2 const & y) : first(x), second(y) {}
	
		pair &	operator=(pair const & other)
		{
			if (this == &other)
				return (*this);
			this->first = other.first;
			this->second = other.second;
			return (*this);
		}
};

template< class T1, class T2 >
bool	operator==(ft::pair< T1, T2 > const & lhs, ft::pair< T1, T2 > const & rhs)
{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

template< class T1, class T2 >
bool	operator<(ft::pair< T1, T2 > const & lhs, ft::pair< T1, T2 > const & rhs)
{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

template< class T1, class T2 >
bool	operator!=(ft::pair< T1, T2 > const & lhs, ft::pair< T1, T2 > const & rhs)
{ return !(lhs == rhs); }

template< class T1, class T2 >
bool	operator>(ft::pair< T1, T2 > const & lhs, ft::pair< T1, T2 > const & rhs)
{ return (rhs < lhs); }

template< class T1, class T2 >
bool	operator<=(ft::pair< T1, T2 > const & lhs, ft::pair< T1, T2 > const & rhs)
{ return !(rhs < lhs); }

template< class T1, class T2 >
bool	operator>=(ft::pair< T1, T2 > const & lhs, ft::pair< T1, T2 > const & rhs)
{ return !(lhs < rhs); }

}

#endif
