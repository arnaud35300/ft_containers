/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_same.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:33:57 by arguilla          #+#    #+#             */
/*   Updated: 2022/05/03 16:36:15 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_SAME_HPP
# define IS_SAME_HPP

# include "is_integral.hpp"

namespace ft
{

template< class T, class U>
struct is_same : ft::false_type {};

template< class T >
struct is_same<T, T> : ft::true_type {};

}

#endif
