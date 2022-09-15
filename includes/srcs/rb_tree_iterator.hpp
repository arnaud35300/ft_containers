/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:19:21 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/14 16:03:10 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

namespace ft
{

template< class T, class Ptr, class Ref, class C, class Custom_less>
class rb_tree_iterator
{
	public:
		typedef	rb_tree_iterator<T, Ptr, Ref, C, Custom_less>	iterator_type;
		typedef	rb_tree_iterator<T, T *, T &, C, Custom_less>	iterator;
		typedef	rb_tree_iterator<T, T const *, T const &, C, Custom_less>	const_iterator;
		typedef size_t	size_type;
		typedef ptrdiff_t	difference_type;
		typedef T	value_type;
		typedef Ptr	pointer;
		typedef Ref	reference;
		typedef node<T, C, Custom_less>*	node_ptr;
		typedef std::bidirectional_iterator_tag	iterator_category;
		node_ptr	ptr;

		rb_tree_iterator(void) : ptr(NULL) {}
		
		rb_tree_iterator(node_ptr const ptr) : ptr(ptr) {}
		
		rb_tree_iterator(iterator const & x) : ptr(const_cast<node_ptr>(x.ptr)) {}
		
		virtual ~rb_tree_iterator(void) {}

		iterator_type &	operator=(iterator_type const & x)
		{
			this->ptr = x.ptr;
		
			return (*this);
		}

		rb_tree_iterator	operator++(int)
		{
			rb_tree_iterator	tmp(*this);
			this->ptr = ptr->get_next_node();
		
			return (tmp);
		}

		rb_tree_iterator &	operator++(void)
		{
			this->ptr = ptr->get_next_node();
		
			return (*this);
		}

		rb_tree_iterator	operator--(int)
		{
			rb_tree_iterator	tmp(*this);
			this->ptr = ptr->get_previous_node();
			
			return (tmp);
		}

		rb_tree_iterator &	operator--()
		{
			this->ptr = ptr->get_previous_node();
			
			return (*this);
		}

		reference	operator*()
		{ return this->ptr->val; }
		
		reference	operator*() const
		{ return this->ptr->val; }
		pointer		operator->()
		{ return (&(this->ptr->val)); }

		pointer		operator->() const
		{ return (&(this->ptr->val)); }

		template<class T2, class Ptr2, class Ref2, class C2, class Custom_less2>
		friend inline bool	operator==(iterator_type const & lhs, rb_tree_iterator<T2, Ptr2, Ref2, C2, Custom_less2> const & rhs)
		{ return (lhs.ptr == rhs.ptr); }

		template<class T2, class Ptr2, class Ref2, class C2, class Custom_less2>
		friend inline bool	operator!=(iterator_type const & lhs, rb_tree_iterator<T2, Ptr2, Ref2, C2, Custom_less2> const & rhs)
		{ return (!(lhs == rhs));  }
};

}

#endif
