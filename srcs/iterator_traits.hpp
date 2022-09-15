/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 12:16:52 by arguilla          #+#    #+#             */
/*   Updated: 2022/05/08 19:11:45 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

#include <cstddef>

namespace ft
{

template< class Iter >
struct iterator_traits {
	typedef typename	Iter::difference_type	difference_type;
	typedef typename	Iter::value_type		value_type;
	typedef typename	Iter::pointer			pointer;
	typedef typename	Iter::reference			reference;
	typedef typename	Iter::iterator_category	iterator_category;
};

template< class T >
struct iterator_traits< T *> {
	typedef ptrdiff_t						difference_type;
	typedef	T								value_type;
	typedef	T *								pointer;
	typedef T &								reference;
	typedef	std::random_access_iterator_tag iterator_category;
};

template< class T >
struct iterator_traits< T const *> {
	typedef ptrdiff_t						difference_type;
	typedef	T const							value_type;
	typedef	T const *						pointer;
	typedef T const &						reference;
	typedef	std::random_access_iterator_tag	iterator_category;
};

}
#endif
