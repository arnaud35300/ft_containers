/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 13:27:09 by arguilla          #+#    #+#             */
/*   Updated: 2022/05/08 18:59:26 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

# include "remove_cv.hpp"

namespace ft
{

/*
 * integral_constant, true_type, false_type, and is_integral
*/

template< class T, T v >
struct integral_constant {
	public:
		typedef	T							value_type;
		typedef	integral_constant< T, v >	type;
		
		static T const	value = v;
};

typedef	integral_constant< bool, true >	true_type;
typedef	integral_constant< bool, false >	false_type;

template< class >
struct is_integral_helper : public false_type {};
template<>
struct is_integral_helper< bool > : public true_type {};
template<>
struct is_integral_helper< short > : public true_type {};
template<>
struct is_integral_helper< char > : public true_type {};
template<>
struct is_integral_helper< int > : public true_type {};
template<>
struct is_integral_helper< long > : public true_type {};
template<>
struct is_integral_helper< long long > : public true_type {};
template<>
struct is_integral_helper< unsigned short > : public true_type {};
template<>
struct is_integral_helper< unsigned char > : public true_type {};
template<>
struct is_integral_helper< unsigned int > : public true_type {};
template<>
struct is_integral_helper< unsigned long > : public true_type {};
template<>
struct is_integral_helper< unsigned long long > : public true_type {};

template<class T>
struct is_integral : public is_integral_helper< typename ft::remove_cv< T >::type >::type {};

};

#endif
