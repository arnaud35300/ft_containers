/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_cv.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:29:13 by arguilla          #+#    #+#             */
/*   Updated: 2022/04/22 13:30:15 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REMOVE_CV_HPP
# define REMOVE_CV_HPP

namespace ft
{

/*
 *	remove_cv
*/

template< class T > struct remove_cv                   { typedef T type; };
template< class T > struct remove_cv<const T>          { typedef T type; };
template< class T > struct remove_cv<volatile T>       { typedef T type; };
template< class T > struct remove_cv<const volatile T> { typedef T type; };

};

#endif
