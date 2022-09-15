/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:16:43 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/15 11:19:58 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

template<class T, class Container = ft::vector<T> >
class stack
{
	public:
		typedef	T			value_type;
		typedef	Container	container_type;
		typedef std::size_t	size_type;

	protected:
		container_type	c;

		friend bool	operator==(stack const & lhs, stack const & rhs)
		{ return lhs.c == rhs.c; }

		friend bool	operator<(stack const & lhs, stack const & rhs)
		{ return lhs.c < rhs.c; }

	public:
		explicit	stack(container_type const & ctnr = container_type())
			: c(ctnr) {}

		~stack(void) {}

		bool empty(void) const
		{ return (this->c.empty()); }
		
		size_type	size(void) const
		{ return (this->c.size()); }

		value_type &	top(void)
		{ return (this->c.back()); } 

		value_type const &	top(void) const
		{ return (this->c.back()); } 

		void	push(value_type const & val)
		{
			this->c.push_back(val);
			return ;
		}

		void	pop(void)
		{
			this->c.pop_back();
			return ;
		}
};

template <class T, class Container>
inline bool	operator==(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs)
{ return (lhs.c == rhs.c); }

template <class T, class Container>
inline bool	operator!=(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs)
{ return (!(lhs == rhs)); }

template <class T, class Container>
inline bool	operator<(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs)
{ return (lhs.c < rhs.c); }

template <class T, class Container>
inline bool	operator<=(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs)
{ return (!(lhs > rhs)); }

template <class T, class Container>
inline bool	operator>(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs)
{ return (rhs < lhs); }

template <class T, class Container>
inline bool	operator>=(ft::stack<T, Container> const & lhs, ft::stack<T, Container> const & rhs)
{ return (!(lhs < rhs)); }

}

#endif
