/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nullptr.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 18:34:52 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/14 07:57:29 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	NULLPTR_HPP
# define NULLPTR_HPP

namespace ft
{

const class nullptr_t
{
	public:
		template<class T>
		operator T*(void) const
		{ return (0); }

		template<class C, class T>
		operator T C::*(void) const
		{ return (0); }

	private:
		void	operator&(void) const;
} ft_nullptr = {};

}

#endif
