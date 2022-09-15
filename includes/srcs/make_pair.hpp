/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pair.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:31:03 by arguilla          #+#    #+#             */
/*   Updated: 2022/04/26 15:01:31 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*                                                                            */
/* ************************************************************************** */

#ifndef MAKE_PAIR_HPP
# define MAKE_PAIR_HPP

# include "pair.hpp"

namespace ft
{

template< class T1, class T2 >
ft::pair< T1, T2 >	make_pair(T1 t, T2 u)
{
	ft::pair< T1, T2 >	obj(t, u);

	return (obj);
}

}

#endif
