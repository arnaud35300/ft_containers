/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 19:20:20 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/14 19:14:57 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include "pair.hpp"
# include "make_pair.hpp"
# include "rb_tree.hpp"
# include "node.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"	
# include "nullptr.hpp"

namespace ft
{

template<class Key, class Value, class Compare = std::less< Key >,
	class Alloc = std::allocator<ft::pair<const Key, Value> > >
class map : public ft::rb_tree<const Key, Value, ft::pair<Key const, Value>, Compare, Alloc, ft::my_less<Key, Value, Compare> >
{
	private:
	public:
		typedef	ft::rb_tree<Key const, Value, ft::pair<Key const, Value>, Compare, Alloc, ft::my_less<Key, Value, Compare> >	_base;
		typedef	typename	_base::key_type					key_type;
		typedef	typename	_base::mapped_type				mapped_type;
		typedef typename	_base::value_type				value_type;
		typedef typename	_base::key_compare				key_compare;
		typedef typename	_base::allocator_type			allocator_type;
		typedef typename	_base::reference				reference;
		typedef typename	_base::const_reference			const_reference;
		typedef typename	_base::pointer					pointer;
		typedef typename	_base::const_pointer			const_pointer;
		typedef typename	_base::difference_type			difference_type;
		typedef typename	_base::size_type				size_type;
		typedef typename	_base::map_node					map_node;
		typedef typename	_base::iterator					iterator;
		typedef typename	_base::const_iterator			const_iterator;
		typedef typename	_base::reverse_iterator			reverse_iterator;
		typedef typename	_base::const_reverse_iterator	const_reverse_iterator;
		
		/*
		* Constructors
		*/

		explicit map(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type())
			: _base(comp, alloc) {}

		template<class InputIterator>
		map(InputIterator first, InputIterator last, key_compare const & comp = key_compare(),
			allocator_type const & alloc = allocator_type(),
			typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator>::type* = ft_nullptr)
			: _base(comp, alloc)
		{
			this->insert(first, last);

			return ;
		}

		map(map const & x)
			: _base()
		{
			this->insert(x.begin(), x.end());

			return ;
		}

		/*
		* Destructor
		*/

		virtual ~map() {}

		/*
		* Operators
		*/

		map & operator=(map const & x)
		{
			if (this == &x)
				return (*this);
			this->clear();
			this->_alloc = x._alloc;
			this->_comp = x._comp;
			this->insert(x.begin(), x.end());

			return (*this);
		}

		/*
		* Element access
		*/

		mapped_type &	operator[](key_type const & key)
		{ return (this->insert(value_type(key, mapped_type())).first->second); }

		mapped_type &	at(key_type const & key)
		{
			iterator it = this->find(key);
			
			if (it == this->end())
				throw std::out_of_range("ft::map::at");
			
			return (it->second);
		}

		mapped_type const &	at(key_type const & key) const
		{
			const_iterator it = this->find(key);
			
			if (it == this->end())
				throw std::out_of_range("ft::map::at");
			
			return (it->second);
		}
		
		/*
		* Modifiers
		*/

		ft::pair<iterator, bool>	insert(value_type const & val)
		{
			if (this->_size == 0)
				return (this->insert_root(val));
			return (this->explore_tree(val));
		}

		iterator	insert(iterator position, value_type const & val)
		{
			position = iterator(this->_root);
			return (this->insert(val).first);			
		}

		template< class InputIterator >
		void	insert(InputIterator first, InputIterator last, 
			typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator>::type* = ft_nullptr)
		{
			for (; first != last; ++first)
				this->insert(*first);

			return ;
		}

	private:
		ft::pair<iterator, bool>	explore_tree(value_type const & val)
		{
			map_node *					it(this->_root);

			while (it)
			{
				if (key_compare()(val.first, it->val.first))
				{
					if (it->left && it->left != this->_first)
						it = it->left;
					else
						return (ft::make_pair(iterator(this->insert_node(it, Left, val)), true));
				}
				else if (key_compare()(it->val.first, val.first))
				{
					if (it->right && it->right != this->_last)
						it = it->right;
					else
						return (ft::make_pair(iterator(this->insert_node(it, Right, val)), true));
				}
				else
					break;
			}
			return (ft::make_pair(iterator(it), false));
		}
};

template< class Key, class T, class Compare, class Allocator >
bool	operator==(map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y)
{
	if (x.size() != y.size())
		return false;
	
	return ft::equal(x.begin(), x.end(), y.begin());
}

template< class Key, class T, class Compare, class Allocator >
bool	operator<(map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template< class Key, class T, class Compare, class Allocator >
bool	operator!=(map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y)
{ return !(x == y); }

template< class Key, class T, class Compare, class Allocator >
bool	operator>(map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y)
{ return !(x <= y); }

template< class Key, class T, class Compare, class Allocator >
bool	operator>=(map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y)
{ return !(x < y); }

template< class Key, class T, class Compare, class Allocator >
bool	operator<=(map< Key, T, Compare, Allocator > const & x, map< Key, T, Compare, Allocator> const & y)
{ return !(y < x); }

}


#endif
