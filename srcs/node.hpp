/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 12:33:38 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/18 17:38:08 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include "pair.hpp"

namespace ft
{

enum e_color {
	Black,
	Red,
};

enum e_side {
	Left,
	Right
};

enum e_position {
	Begin,
	End
};

template< typename T, class C, class Custom_less>
class node {
	public:
		typedef	T			value_type;
		typedef	T &			reference;
		typedef	T const &	const_reference;
		typedef	T *			pointer;
		typedef C			key_compare;
		value_type			val;
		node *				parent;
		node *				left;
		node *				right;
		e_color				c;
	private:
		key_compare		comp;
		Custom_less		_less;
		node *head;
		node *min;
		node *max;
	public:		
		explicit node(value_type const & val = value_type(), e_color c = Red)
			: val(val), parent(0), left(0), right(0), c(c), comp(key_compare()), _less(Custom_less(comp)) {}
		
		node(node const & x) : val(x.val), parent(x.parent), left(x.left), right(x.right), c(x.c), comp(key_compare()), _less(Custom_less(comp)) {}
		
		~node() {}

		node &	operator=(node const & x)
		{
			if (this == &x)
				return (*this);
			this->val = x.val;
			this->parent = x.parent;
			this->left = x.left;
			this->right = x.right;
			this->c = x.c;
			
			return (*this);
		}

		bool	operator==(node const & rhs)
		{ return (this->val == rhs.val); }

		bool	operator!=(node const & rhs)
		{ return (this->val != rhs.val); }

		bool	operator>(node const & rhs)
		{ return (this->val > rhs.val); }

		bool	operator<(node const & rhs)
		{ return (this->val < rhs.val); }

		bool	operator<=(node const & rhs)
		{ return (this->val <= rhs.val); }

		bool	operator>=(node const &	rhs)
		{ return (this->val >= rhs.val); }
		
		node *	get_next_node_by_right(void)
		{
			node *	it(this->right);

			while (it->left)
				it = it->left;
			return (it);
		}

		node * get_next_node_by_left(void)
		{
			node *	it(this->parent);
			node *	tmp(this);

			while (it->left != tmp)
			{
				tmp = it;
				it = it->parent;
			}
			return (it);
		}

		node *	get_next_node(void)
		{
			if (this->right)
				return (get_next_node_by_right());
			return (get_next_node_by_left());
		}

		node *	get_previous_node(void) 
		{
			node 	* it(this);
			
			this->set_usefull_nodes();
			if (this == this->min || this == this->max)
				return (this->parent);
			if (it->left)
			{
				for (it = it->left; it->right; it = it->right);
				return (it);
			}
			for (; _less(this->val, it->val) || (!_less(it->val, this->val) && !_less(this->val, it->val)); it = it->parent);

			return (it);
		}

		void	set_usefull_nodes(void)
		{
			node *	tmp(this);
	
			while (tmp->parent)
				tmp = tmp->parent;
			this->head = tmp;
			while (tmp->left)
				tmp = tmp->left;
			this->min = tmp;
			tmp = this->head;
			while (tmp->right)
				tmp = tmp->right;
			this->max = tmp;
	
			return ;
		}

		void	add_child(node *& left, node *& right)
		{
			this->left = left;
			this->right = right;
			if (left)
				left->parent = this;
			if (right)
				right->parent = this;

			return ;
		}
};

}



#endif
