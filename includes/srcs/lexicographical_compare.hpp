/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexicographical_compare.hpp                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 17:31:54 by arguilla          #+#    #+#             */
/*   Updated: 2022/05/08 18:02:46 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEXICOGRAPHICAL_COMPARE_HPP
# define LEXICOGRAPHICAL_COMPARE_HPP

namespace ft
{

template<class InputIterator1, class InputIterator2>
bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
{
	while (first1 != last1)
	{
		if (first2 == last2 || *first2 < *first1)
			return false;
		else if (*first1 < *first2)
			return true;
		++first1; ++first2;
	}
	return (first2 != last2);
}

template<class InputIterator1, class InputIterator2, class Compare>
bool	lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2,
		Compare comp)
{
	while (first1 != last1)
	{
		if (first2 == last2 || comp(*first2, *first1))
			return false;
		else if (comp(*first1, *first2))
			return true;
		++first1; ++first2;
	}
	return (first2 != last2);
}

}

#endif
