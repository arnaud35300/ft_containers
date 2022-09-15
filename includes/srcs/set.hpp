/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 08:45:47 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/14 19:15:04 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include "rb_tree.hpp"
# include "make_pair.hpp"

namespace ft
{

template<class Key, class Compare = std::less<Key>,
	class Alloc = std::allocator< Key > >
class set : public ft::rb_tree<Key const, Key const, Key const, Compare, Alloc, ft::my_less2<Key, Key, Compare> >
{
	private:
	public:
		typedef	ft::rb_tree<const Key, Key const, Key const, Compare, Alloc, ft::my_less2<Key, Key, Compare> >	_base;
		typedef	typename	_base::key_type					key_type;
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

		explicit set(key_compare const & comp = key_compare(), allocator_type const & alloc = allocator_type())
			: _base(comp, alloc) {}

		template<class InputIterator>
		set(InputIterator first, InputIterator last, key_compare const & comp = key_compare(),
			allocator_type const & alloc = allocator_type(),
			typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator>::type* = ft_nullptr)
			: _base(comp, alloc)
		{
			this->insert(first, last);

			return ;
		}

		set(set const & x)
			: _base()
		{
			this->insert(x.begin(), x.end());

			return ;
		}

		/*
		* Destructor
		*/

		virtual ~set() {}

		/*
		* Operators
		*/

		set & operator=(set const & x)
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
		* Modifiers
		*/

		ft::pair< iterator, iterator >	equal_range(key_type const & x ) const
		{
				iterator left = this->lower_bound( x );
				iterator right = left;
				
				if (right != this->end() && this->iseq(*right, x))
					right++;
				
				return ft::make_pair(left, right);
		}

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
				if (key_compare()(val, it->val))
				{
					if (it->left && it->left != this->_first)
						it = it->left;
					else
						return (ft::make_pair(iterator(this->insert_node(it, Left, val)), true));
				}
				else if (key_compare()(it->val, val))
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

template< class Key, class Compare, class Allocator >
bool	operator==(set< Key, Compare, Allocator > const & x, set< Key, Compare, Allocator> const & y)
{
	if (x.size() != y.size())
		return false;

	return ft::equal(x.begin(), x.end(), y.begin());
}

template< class Key, class Compare, class Allocator >
bool	operator<(set< Key, Compare, Allocator > const & x, set< Key, Compare, Allocator> const & y)
{ return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()); }

template< class Key, class Compare, class Allocator >
bool	operator!=(set< Key, Compare, Allocator > const & x, set< Key, Compare, Allocator> const & y)
{ return !(x == y); }

template< class Key, class Compare, class Allocator >
bool	operator>(set< Key, Compare, Allocator > const & x, set< Key, Compare, Allocator> const & y)
{ return !(x <= y); }

template< class Key, class Compare, class Allocator >
bool	operator>=(set< Key, Compare, Allocator > const & x, set< Key, Compare, Allocator> const & y)
{ return !(x < y); }

template< class Key, class Compare, class Allocator >
bool	operator<=(set< Key, Compare, Allocator > const & x, set< Key, Compare, Allocator> const & y)
{ return !(y < x); }

}

#endif