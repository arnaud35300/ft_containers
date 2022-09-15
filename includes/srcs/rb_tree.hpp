/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 08:03:09 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/14 19:02:00 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <memory>
# include <cstddef>
# include <iostream>
# include <functional>
# include <string>
# include "node.hpp"
# include "rb_tree_iterator.hpp"
# include "lexicographical_compare.hpp"
# include "equal.hpp"
# include "pair.hpp"
# include "swapper.hpp"
# include "is_same.hpp"
# include "iterator_traits.hpp"
# include "nullptr.hpp"
# include "enable_if.hpp"
# include "rb_tree_reverse_iterator.hpp"
# include "make_pair.hpp"
# include <limits>
# include <vector>

namespace ft
{

template< class Key, class Value, class Compare >
struct my_less : public std::binary_function<Key, Key, bool>
{
	typedef	Key													key_type;
	Compare														comp;

	my_less(Compare c) : comp(c) {}

	bool operator()(ft::pair<Key, Value> const & x, ft::pair<Key, Value> const & y) const
	{ return (comp(x.first, y.first)); }

	bool operator()(ft::pair<Key, Value> const & pair, key_type const & key) const
	{ return (comp(pair.first, key)); }

	bool operator()(key_type const & key, ft::pair<Key, Value> const & pair) const
	{ return (comp(key, pair.first)); }

	bool operator()(key_type const & x, key_type const & y) const
	{ return (comp(x, y)); }
};

template< class Key, class Value, class Compare >
struct my_less2 : public std::binary_function<Key, Key, bool>
{
	typedef	Key													key_type;
	Compare														comp;

	my_less2(Compare c) : comp(c) {}

	template<class T>
	bool operator()(T const & x, T const & y) const
	{
		return (comp(x, y));
	}
};

template< class Key, class Value, class Node_pair, class Compare = std::less<Key>,
	class Alloc = std::allocator<ft::pair<Key const, Value> >,
	class Custom_less = ft::my_less<Key, Value, Compare> >
class rb_tree
{
	public:
		typedef	Key													key_type;
		typedef	Value												mapped_type;
		typedef Node_pair											value_type;
		typedef	Compare												key_compare;
		typedef	Alloc												allocator_type;
		typedef	value_type &										reference;
		typedef	value_type const &									const_reference;
		typedef value_type *										pointer;
		typedef value_type const *									const_pointer;
		typedef ptrdiff_t											difference_type;
		typedef size_t												size_type;
		typedef ft::node<value_type, key_compare, Custom_less>					map_node;
		typedef ft::rb_tree_iterator<value_type, pointer,
			reference, key_compare, Custom_less>									iterator;
		typedef ft::rb_tree_iterator<value_type, const_pointer,
			const_reference, key_compare, Custom_less>							const_iterator;
		typedef ft::rb_tree_reverse_iterator<iterator>						reverse_iterator;
		typedef ft::rb_tree_reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef	std::allocator< map_node >							node_allocator_type;

		map_node *													_root;
	protected:
		node_allocator_type											_node_allocator;
		map_node *													_first;
		map_node *													_last;
		allocator_type												_alloc;
		key_compare													_comp;
		Custom_less													_less;
		size_type													_size;

	public:

		class value_compare
		{
			friend class	rb_tree;
			public:
				explicit value_compare(key_compare const & comp = key_compare()) : comp(comp), less(Custom_less(comp)) {}
				bool operator()(value_type const & x, value_type const & y) const
				{ return (less(x, y)); }
			private:
				key_compare comp;
				Custom_less less;
		};

		/*
		* Constructors
		*/

		explicit rb_tree(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type())
			: _node_allocator(node_allocator_type()), _alloc(alloc), _comp(comp), _less(Custom_less(comp)),  _size(0)
 
		{
			this->init();
			return ;
		}

		rb_tree(rb_tree const & x) : _alloc(x._alloc), _node_allocator(x._node_allocator), _comp(x._comp), _less(x._less), _size(0)
		{
			this->init();
			return ;
		}

		/*
		* Destructor
		*/

		virtual ~rb_tree()
		{
			this->clear();

			_node_allocator.destroy(this->_first);
			_node_allocator.deallocate(this->_first, 1);
			_node_allocator.destroy(this->_last);
			_node_allocator.deallocate(this->_last, 1);
			
			return ;
		}

		/*
		* Operators
		*/

		rb_tree & operator=(rb_tree const & x)
		{
			if (this == &x)
				return (*this);
			this->clear();
			this->_alloc = x._alloc;
			this->_comp = x._comp;
			this->insert(x.begin(), x.end());

			return (*this);
		}

		template<class T>
		bool	iseq(T const & lhs, T const & rhs) const
		{ return _less(lhs, rhs) == _less(rhs, lhs); }

		template<class T, class U>
		bool	iseq(T const & lhs, U const & rhs) const
		{ return _less( lhs, rhs ) == _less( rhs, lhs ); }

		/*
		* Iterators
		*/

		iterator	begin(void)
		{ return (iterator(this->_first->parent));}

		const_iterator	begin(void) const
		{ return (const_iterator(this->_first->parent));}

		iterator	end(void)
		{ return (iterator(this->_last)); }

		const_iterator	end(void) const
		{ return (const_iterator(this->_last)); }

		reverse_iterator	rbegin(void)
		{ return (reverse_iterator(this->_last)); }

		const_reverse_iterator	rbegin(void) const
		{ return (const_reverse_iterator(this->_last)); }

		reverse_iterator	rend(void)
		{ return (reverse_iterator(this->_first->parent)); }

		const_reverse_iterator	rend(void) const
		{ return (const_reverse_iterator(this->_first->parent)); }

		/*
		* Capacity
		*/

		bool	empty(void) const
		{ return (this->_size == 0); }

		size_type	size(void) const
		{ return (this->_size); }

		virtual size_type	max_size(void) const
		{ return (this->_alloc.max_size()); }

		/*
		* Observers
		*/

		key_compare	key_comp(void) const
		{ return (this->_comp); }

		value_compare	value_comp(void) const
		{ return (value_compare(this->_comp)); }

		/*
		* Modifiers
		*/

		void	clear(map_node *pos) {
			if (!pos)
				return ;
			clear(pos->left);
			clear(pos->right);
			if (pos != _first && pos != _last) {
			_node_allocator.destroy(pos);
			_node_allocator.deallocate(pos, 1);
			--this->_size;
			}

			return ;
		}

		void		clear(void)
		{
			if (this->empty())
				return ;
	
			this->clear(this->_root);
			this->link_nodes();

			return ;
		}

		virtual void	erase(iterator position)
		{
			map_node *	node = this->find_by_type(position);
			if (node == this->_last)
				return ;
			this->delete_node(node);
	
			--this->_size;
			delete node;

			return ;
		}
	
		virtual size_type	erase(key_type const & key)
		{
			map_node * node = this->find_by_type(key);

			if (node == this->_last)
				return (0);
			this->delete_node(node);
			--this->_size;
			delete node;
			
			return (1);
		}

		virtual void	erase(iterator first, iterator last)
		{
			while (first != last)
				this->erase(first++);
			
			return ;
		}
		
		void	swap(rb_tree & x)
		{
			ft::swapper(this->_root, x._root);
			ft::swapper(this->_first, x._first);
			ft::swapper(this->_last, x._last);
			ft::swapper(this->_alloc, x._alloc);
			ft::swapper(this->_comp, x._comp);
			ft::swapper(this->_size, x._size);
			
			return ;
		}

		/*
		* Operations
		*/

		virtual	iterator	lower_bound(key_type const & key)
		{	
			iterator	it = this->begin();
		
			if (this->_size == 0)
				return (it);
			for (iterator ite = this->end(); it != ite && this->_less(*it, key); ++it);

			return (it);
		}

		virtual const_iterator	lower_bound(key_type const & key) const
		{
			const_iterator	it = this->begin();
		
			if (this->_size == 0)
				return (it);
			for (const_iterator ite = this->end(); it != ite && this->_less(*it, key); ++it);

			return (it);
		}

		virtual iterator	upper_bound(key_type const & key)
		{
			iterator	it = this->begin();
		
			if (this->_size == 0)
				return (it);
			else if (!this->_less(key, *(--this->end())))
				return (this->end());
			else if (this->_less(key, *(this->begin())))
				return (this->begin());
			for (iterator ite = this->end(); it != ite && !this->_less(key, *it); ++it);
			return (it);
		}

		virtual const_iterator	upper_bound(key_type const & key) const
		{
			const_iterator	it = this->begin();
		
			if (this->_size == 0)
				return (it);
			
			else if (!this->_less(key, *(--this->end())))
				return (this->end());
			else if (this->_less(key, *(this->begin())))
				return (this->begin());
			for (const_iterator ite = this->end(); it != ite && !this->_less(key, *it); ++it);
			return (it);
		}

		virtual	ft::pair< const_iterator, const_iterator >	equal_range (key_type const & key) const
		{ return (ft::make_pair(const_iterator(this->lower_bound(key)), const_iterator(this->upper_bound(key)))); }

		virtual	ft::pair< iterator, iterator >	equal_range(key_type const & key)
		{ return (ft::make_pair(iterator(this->lower_bound(key)), iterator(this->upper_bound(key)))); }
		
		virtual size_type	count(key_type const & key) const
		{
			const_iterator	it = this->begin();

			for (const_iterator ite = this->end(); it != ite; ++it)
				if (!this->_less(*it, key) && !this->_less(key, *it))
					return (1);
			return (0);
		}

		virtual iterator	find(key_type const & key)
		{ return (iterator(this->find_by_type<>(key))); }
		
		virtual const_iterator	find(key_type const & key) const
		{ return (const_iterator(this->find_by_type<>(key))); }

		/*
		* Allocator
		*/

		allocator_type get_allocator() const
		{ return (this->_alloc); }

		template< class T >
		map_node *	find_by_type(T position,
			typename ft::enable_if<
			ft::is_same<iterator, T>::value || ft::is_same<const_iterator, T>::value,
			T>::type * = 0)
		{ return (this->find_by_type<>(*position)); }

		template< class T >				
		map_node *	find_by_type(T position) const
		{
			for (map_node * node = this->_root;
				node && node != this->_first && node != this->_last;) {
				if (this->_less(position, node->val))
					node = node->left;
				else if (this->_less(node->val, position))
					node = node->right;
				else
					return (node);
			}
			
			return (this->_last);
		}

		map_node *	new_map_node(value_type const & val, e_color color)
		{
			map_node * node = this->_node_allocator.allocate(1);
			this->_node_allocator.construct(node, map_node(val, color));

			return (node);
		}
		
		map_node *	new_map_node(value_type const & val)
		{ return (this->new_map_node(val, Red)); }

		map_node *	new_map_node(void)
		{
			map_node * node = this->_node_allocator.allocate(1);
			this->_node_allocator.construct(node, map_node());
			
			return (node);
		}

		void	init(void)
		{
			this->_first = new_map_node();
			this->_last = new_map_node();
			this->link_nodes();
			this->_size = 0;

			return ;
		}

		void	link_nodes(void)
		{
			this->_first->parent = this->_last;
			this->_last->parent = this->_first;
			
			return ;
		}
		/*
		* Insertion
		*/

		ft::pair<iterator, bool>	insert_root(value_type const & val)
		{
			++this->_size;				
			this->_root = new_map_node(val, Black);
			_root->add_child(this->_first, this->_last);

			return (ft::make_pair(rb_tree::iterator(this->_root), true));
		}

		map_node *	insert_node(map_node * it, e_side side, value_type const & val = value_type())
		{
			map_node *	new_node = new_map_node(val);
			map_node *& side_node = (side == Left) ? it->left : it->right;
			
			new_node->parent = it;
			if (side == Right)
				new_node->right = side_node;
			else
				new_node->left = side_node;
			if (side_node)
				side_node->parent = new_node;
			side_node = new_node;
			++this->_size;
			this->create_rb_tree_relations(new_node);
			
			return (new_node);
		}

		/*
		* Deletion
		*/

		void	delete_node_without_two_children(map_node * node, map_node *& side, map_node *& child)
		{
			child = side;
			return (this->delete_node_without_two_children(node, side));
		}


		void	delete_node_without_two_children(map_node * node, map_node *& side)
		{
			if (node && node == this->_root)
				this->_root = side;
			else if (node == node->parent->left)
				node->parent->left = side;
			else
				node->parent->right = side;
			if (side)
				side->parent = node->parent;			

			return ;
		}

		void	delete_node_with_two_children(map_node * node, map_node *& child, e_color & color)
		{
			map_node *	nearest = node->right;

			for (; nearest->left; nearest = nearest->left);

			color = nearest->c;
			child = nearest->right;
			if (nearest->parent == node)
			{
				if (child)
					child->parent = nearest;
			}
			else
			{
				this->delete_node_without_two_children(nearest, nearest->right);
				nearest->right = node->right;
				nearest->right->parent = nearest;
			}
			this->delete_node_without_two_children(node, nearest);
			nearest->left = node->left;
			nearest->left->parent = nearest;
			nearest->c = node->c;
		
			return ;
		}

		void	resolve_first_delete_violation(map_node * node, map_node *& uncle, e_side side)
		{
			uncle->c = Black;
			node->parent->c = Red;
			this->rotate(node->parent, side);
			if (side == Left)
				uncle = node->parent != NULL ? node->parent->right : NULL;
			else
				uncle = node->parent != NULL ? node->parent->left : NULL;

			return ;
		}

		void	resolve_second_delete_violation(map_node *& node, map_node * uncle)
		{
			if (uncle != NULL)
				uncle->c = Red;
			node = node->parent;

			return ;
		}
		
		void	resolve_third_delete_violation(map_node * node, map_node *& uncle, e_side side)
		{
			uncle->c = Red;
			if (side == Left)
			{
				uncle->left->c = Black;
				this->right_rotation(uncle);
				uncle = node->parent != NULL ? node->parent->right : NULL;
			}
			else
			{
				uncle->right->c = Black;
				this->left_rotation(uncle);
				uncle = node->parent != NULL ? node->parent->left : NULL;
			}

			return ;
		}

		void	resolve_fourth_delete_violation(map_node *& node, map_node *& uncle, e_side side)
		{
			if (uncle != NULL)
				uncle->c = node->parent == NULL ? Black : node->parent->c;
			node->parent->c = Black;
			if (side == Left)
			{
				if (uncle != NULL && uncle->right != NULL)
					uncle->right->c = Black;
				this->left_rotation(node->parent);
			}
			else
			{
				if (uncle != NULL && uncle->left != NULL)
					uncle->left->c = Black;
				this->right_rotation(node->parent);
			}
			node = this->_root;
			node->parent = NULL;

			return ;
		}
		
		void	fix_rb_tree_relations(map_node * node)
		{
			while (node != this->_root && node->c == Black)
			{
				if (node == node->parent->left)
				{
					map_node *	uncle = node->parent->right;

					if (uncle && uncle->c == Red)
						this->resolve_first_delete_violation(node, uncle, Left);
					if (uncle == NULL || ((uncle->left == NULL || uncle->left->c == Black) && (uncle->right == NULL || uncle->right->c == Black)))
						this->resolve_second_delete_violation(node, uncle);
					else {
						if (uncle->right == NULL || uncle->right->c == Black)
							this->resolve_third_delete_violation(node, uncle, Left);
						this->resolve_fourth_delete_violation(node, uncle, Left);
					}
				}
				else
				{
					map_node *	uncle = node->parent->left;

					if (uncle && uncle->c == Red)
						this->resolve_first_delete_violation(node, uncle, Right);
					if (uncle == NULL || ((uncle->left == NULL || uncle->left->c == Black) && (uncle->right == NULL || uncle->right->c == Black)))
						this->resolve_second_delete_violation(node, uncle);
					else 
					{
						if (uncle->left == NULL || uncle->left->c == Black)
							this->resolve_third_delete_violation(node, uncle, Right);
						this->resolve_fourth_delete_violation(node, uncle, Right);
					}
				}
			}
			node->c = Black;

			return ;
		}
			
		void	delete_node(map_node *& node)
		{
			map_node *	child;
			e_color		color = node->c;
			
			if (node->left == 0 || node->right == 0)
				this->delete_node_without_two_children(node, node->left ? node->left : node->right, child);
			else
				this->delete_node_with_two_children(node, child, color);			
			if (child != 0 && color == Black)
				this->fix_rb_tree_relations(child);
			return ;
		}

		/*
		* Rb tree relations
		*/
	
		void	create_rb_tree_relations(map_node * node)
		{
			while (node != this->_root && node->parent->c == Red && node->c == Red)
			{
				map_node *	parent = node->parent;
				map_node *	gr_parent = parent->parent;

				if (parent == gr_parent->left)
				{
					map_node *	uncle = gr_parent->right;

					if (uncle && uncle->c == Red && uncle != this->_last && uncle != this->_first)
						this->recolor_node_family(node, gr_parent, parent, uncle);
					else if (node == parent->right)
						this->resolve_first_violation(&rb_tree::left_rotation, node, parent);
					else
						this->resolve_second_violation(&rb_tree::right_rotation, parent, gr_parent);
				}
				else
				{
					map_node *	uncle = gr_parent->left;

					if (uncle && uncle->c == Red && uncle != this->_last && uncle != this->_first)
						this->recolor_node_family(node, gr_parent, parent, uncle);
					else if (node == parent->left)
						this->resolve_first_violation(&rb_tree::right_rotation, node, parent);
					else
						this->resolve_second_violation(&rb_tree::left_rotation, parent, gr_parent);
				}
			}
			this->_root->c = Black;
			return ;
		}

		void	resolve_first_violation(void (rb_tree::*rotation)(map_node *&), map_node *& node, map_node *& parent)
		{
			(this->*rotation)(parent);
			node = parent;

			return ;
		}

		void	resolve_second_violation(void (rb_tree::*rotation)(map_node *&), map_node *& parent, map_node *& gr_parent)
		{
			e_color	tmp = parent->c;

			(this->*rotation)(gr_parent);
			parent->c = gr_parent->c;
			gr_parent->c = tmp;
			
			return ;
		}

		/*
		* Rotations
		*/

		void	set_new_parent_relation(map_node *& node_to_move, map_node *& parent)
		{
			node_to_move->parent = parent->parent;
			if (node_to_move->parent == 0) 
				this->_root = node_to_move;
			else if (parent == node_to_move->parent->left)
				node_to_move->parent->left = node_to_move;
			else
				node_to_move->parent->right = node_to_move;
			parent->parent = node_to_move;
			
			return ;
		}

		void	rotate(map_node *& node, e_side side)
		{
			if (side == Left)
				return (this->left_rotation(node));
			return (this->right_rotation(node));
		}

		/*
		* Rotate node to the right side of his parent.
		*
		* Explanation (open it with diagrams.net):
		* @see https://drive.google.com/file/d/1peWknShL14TcO4caNdts5pNt4tA7i5Zj/view?usp=sharing
		*/
		void	right_rotation(map_node *& parent)
		{
			map_node *node_to_move = parent->left;

			parent->left = node_to_move->right;
			if (parent->left)
				parent->left->parent = parent;
			this->set_new_parent_relation(node_to_move, parent);
			node_to_move->right = parent;

			return ;
		}

		/*
		* Rotate node to the left side of his parent.
		*
		* Explanation (open it with diagrams.net):
		* @see https://drive.google.com/file/d/1peWknShL14TcO4caNdts5pNt4tA7i5Zj/view?usp=sharing
		*/ 
		void	left_rotation(map_node *& parent)
		{
			map_node *node_to_move = parent->right;

			parent->right = node_to_move->left;
			if (parent->right)
				parent->right->parent = parent;
			this->set_new_parent_relation(node_to_move, parent);
			node_to_move->left = parent;

			return ;
		}

		/*
		* Node operations
		*/

		/*
		*	Case when uncle is red:
		*	I colorize uncle and parent in Black, and grandparent in Red.
		*	Grandparent become the new node.
		*/
		void	recolor_node_family(map_node *& node, map_node *& gr_parent, map_node * parent, map_node * uncle)
		{
			gr_parent->c = Red;
			parent->c = Black;
			uncle->c = Black;
			node = gr_parent;

			return ;
		}

#ifndef MAP_DISPLAY_HPP
# define MAP_DISPLAY_HPP 1

// You can change those define

# define __NODE		map_node	 // name of your strucure/class which contain your node
# define __VALUE	val	 // name of your value variable in your structure/class
# define __SIZE		5		 // size between nodes (only for display)
# define __ROOT		_root	 // name of your tree's root variable
# define __IS_BLACK	c // name of the bool variable for the color of nodes
# define __NIL		0		 // name of your NULL pointer
# define __RIGHT	right	 // name of the right child of your nodes
# define __LEFT		left	 // name of the left child of your nodes


# define __BLACK "\033[40m"
# define __RED   "\e[1;41m"
# define __STOP  "\033[0m"

protected:

int count_from_node(__NODE *ptr, int count = 0) {
	if (ptr != __NIL) {
		if (ptr->__RIGHT != __NIL)
			count += count_from_node(ptr->__RIGHT);
		if (ptr->__LEFT != __NIL)
			count += count_from_node(ptr->__LEFT);
		return (++count);
	}
	return count;
}

int count_btw_p(__NODE *ptr, bool is_right) {
	if (is_right) {
		return count_from_node(ptr->__LEFT);
	}
	else {
		return count_from_node(ptr->__RIGHT);
	}
}

std::vector<std::vector <int> > aff;

bool search_v(int level) {
	for (size_t i = 0; i < aff.size(); i++) {
		if (aff[i][0] == level) {
			aff[i][1]--;
			if (aff[i][1] <= 0)
				aff.erase(aff.begin() + i);
			return (true);
		}
	}
	return (false);
}

void aff_chars(std::string a, std::string b, int size = -1) {
	size = (size == -1) ? a.size() : size;
	std::cout << a;
	for (int i = __SIZE; i - size > 0; i--)
				std::cout << b;
}

public:

void print_tree(__NODE *ptr, int level = 0, bool is_right = 0)
{
	int i;
	if (ptr != __NIL)
	{
		print_tree(ptr->__RIGHT, level + 1, 1);
		std::cout << std::endl;
		for (i = 1; i < level && ptr != __ROOT; i++) {
			if (search_v(i))
				aff_chars("│", " ", 1);
			else
				aff_chars(" ", " ");
		}
		if (ptr != __ROOT) {
			if (is_right && count_btw_p(ptr, is_right) > 0) {
				std::vector<int> tmp;
				tmp.push_back(level);
				tmp.push_back(count_btw_p(ptr, is_right));
				aff.push_back(tmp);
			}
			if (is_right)
					aff_chars("╭", "─", 1);
			else
					aff_chars("╰", "─", 1);
		}
		if (ptr->__LEFT != __NIL && count_btw_p(ptr->__LEFT, 0) > 0) {
			std::vector<int> tmp;
			tmp.push_back(level + 1);
			tmp.push_back(count_btw_p(ptr->__LEFT, 0));
			aff.push_back(tmp);
		}
		if (ptr->c == Black)
			std::cout << __BLACK << ptr->val.first << __STOP;
		else
			std::cout  << __RED << ptr->val.first << __STOP;
		print_tree(ptr->__LEFT, level + 1, 0);
	}
}

#endif
};

}

#endif
