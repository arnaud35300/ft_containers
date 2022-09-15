/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swapper.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:51:31 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/14 07:49:35 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SWAPPER_HPP
# define SWAPPER_HPP

namespace ft
{

template<class T>
void swapper(T & x, T & y)
{
	T	tmp = x;

	x = y;
	y = tmp;

	return ;
}

}

#endif