/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:36:51 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/18 22:11:05 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "is_integral.hpp"
# include "enable_if.hpp"
# include "is_same.hpp"
# include "normal_iterator.hpp"
# include "lexicographical_compare.hpp"
# include "nullptr.hpp"
# include "reverse_iterator.hpp"
# include "equal.hpp"

namespace ft
{

template< class T, class Alloc = std::allocator<T> >
class vector
{
	public:
		typedef	T															value_type;
		typedef	Alloc														allocator_type;
		typedef typename	allocator_type::reference						reference;
		typedef typename	allocator_type::const_reference					const_reference;
		typedef typename	allocator_type::pointer							pointer;
		typedef typename	allocator_type::const_pointer					const_pointer;
		typedef	typename	ft::normal_iterator<pointer, vector>			iterator;
		typedef	typename	ft::normal_iterator<const_pointer, vector>		const_iterator;
		typedef	typename	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef	typename	ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef typename	std::size_t										size_type;

	private:
		allocator_type	_alloc;
		size_type		_size;
		size_type		_capacity;
		pointer			_start;

	protected:
		void	requires_less_than_max_size(size_type n) const
		{
			if (n > this->max_size())
				throw	std::length_error("vector::(x): n > vector.max_size()");
			return ;
		}

		void	resize_cut(size_type n)
		{
			for (; this->size() != n; --this->_size)
				this->_alloc.destroy(this->_start + this->size());
			return ;
		}

		void	resize_expand(size_type n, value_type val)
		{
			if (n > this->capacity())
				this->reserve(n);
			for (; this->_size < n; ++this->_size)
				this->_alloc.construct(this->_start + this->size(), val);
			return ;
		}

		size_type	find_new_capacity(size_type n)
		{
			size_type	new_capacity = this->capacity() + this->capacity();

			if (n > new_capacity)
				return (n);
			return (new_capacity);
		}

	public:

		/*
		 * Constructors
		*/
	
		explicit	vector(const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0), _start(0)
		{}

		explicit	vector(size_type n, const value_type & val = value_type(),
				const allocator_type & alloc = allocator_type())
			: _alloc(alloc), _size(0), _capacity(0)
		{
			this->assign(n, val);
			return ;
		}

		template< class InputIterator >
		vector(InputIterator first, InputIterator last,
				const allocator_type & alloc = allocator_type(),
				typename ft::enable_if< !ft::is_integral< InputIterator >::value, InputIterator>::type* = ft_nullptr)
			: _alloc(alloc), _size(0), _capacity(0)
		{
			this->assign(first, last);
			return ;
		}

		vector(const vector & x)
			: _alloc(x._alloc), _size(0), _capacity(0)
		{
			*this = x;
			return ;
		}

		/*
		 * Destructor
		*/ 

		~vector(void)
		{
			if (this->capacity() == 0)
				return ;
			for (size_type i = 0; i < this->size(); ++i)
				this->_alloc.destroy(this->_start + i);
			this->_alloc.deallocate(this->_start, this->capacity());
			return ;
		}

		/*
		 * Accessors
		 */

		value_type * data(void)
		{ return (this->_start); }
		
		value_type const * data(void) const
		{ return (this->_start); }
		
		inline allocator_type	get_allocator(void) const
		{ return (allocator_type(this->_alloc)); }
		
		inline size_type	size(void) const
		{ return (this->_size); }
		
		inline size_type	max_size(void) const
		{ return (this->_alloc.max_size()); }
		
		inline size_type	capacity(void) const
		{ return (this->_capacity); }
		
		inline bool	empty(void) const
		{ return (this->size() == 0); }

		void	reserve(size_type n)
		{
			this->requires_less_than_max_size(n);
			if (n <= this->_capacity)
				return ;
			pointer	new_start =	this->_alloc.allocate(n);
			for (size_type i = 0; i < n; ++i)
				this->_alloc.construct(new_start + i, i >= this->size() ? T() : *(this->_start + i));
			this->~vector();
			this->_start = new_start;
			this->_capacity = n;
			return ;
		}

		void	resize(size_type n, value_type val = value_type())
		{
			if (n < this->size())
				return (this->resize_cut(n));
			return (this->resize_expand(n, val));
		}

		template<class InputIterator>
		void	assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value,
				InputIterator>::type* = ft_nullptr)
		{
			size_type	n = std::distance(first, last);
			size_type	max = n > this->size() ? n : this->_size;

			if (n > this->capacity())
				this->reserve(n);
			for (size_type i = 0; i < max; ++i)
			{
				if (i < this->size())
					this->_alloc.destroy(this->_start + i);
				if (i < n)
					this->_alloc.construct(this->_start + i, *first++);
			}
			this->_size = n;
			return ;
		}

		void	assign(size_type n, value_type const & val)
		{
			size_type	max = n > this->size() ? n : this->_size;

			if (n > this->capacity())
				this->reserve(n);
			for (size_type i = 0; i < max; ++i)
			{
				if (i < this->size())
					this->_alloc.destroy(this->_start + i);
				if (i < n)
					this->_alloc.construct(this->_start + i, val);
			}
			this->_size = n;
			return ;
		}

		void	push_back(value_type const & val)
		{
			if (this->size() == this->capacity())
				this->reserve(this->capacity() == 0 ? 1 : this->capacity() + this->capacity());
			this->_alloc.construct(this->_start + this->size(), val);
			++this->_size;
			return ;
		}

		void	pop_back(void)
		{
			this->_alloc.destroy(this->_start + this->size() - 1);
			--this->_size;
			return ;
		}

		iterator	insert(iterator position, value_type const & val)
		{
			size_type	index = position - this->begin();

			this->insert(position, 1, val);
			return (iterator(this->_start + index)); 
		}

		void	insert(iterator position, size_type n, value_type const & val)
		{
			size_type	index = position - this->begin();

			if (this->size() + n > this->capacity())
				this->reserve(this->find_new_capacity(this->size() + n));
			for (size_type i = this->size(); i > index; --i)
				this->_alloc.construct(this->_start + i + n - 1, *(this->_start + i - 1));
			for (size_type i = 0; i < n; ++i)
				this->_alloc.construct(this->_start + index + i, val);
			this->_size += n;
			return ;
		}

		template<class InputIterator>
		void	insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = ft_nullptr)
		{
			size_type	n = std::distance(first, last);
			size_type	index = position - this->begin();

			if (this->size() + n > this->capacity())
				this->reserve(this->find_new_capacity(this->size() + n));
			for (size_type i = this->size(); i > index; --i)
				this->_alloc.construct(this->_start + i + n - 1, *(this->_start + i - 1));
			for (size_type i = 0; i < n; ++i)
				this->_alloc.construct(this->_start + index + i, *first++);
			this->_size += n;
			return ;
		}

		iterator	erase(iterator position)
		{ return (this->erase(position, position + 1)); }

		iterator	erase(iterator first, iterator last)
		{
			difference_type	n = std::distance(first, last);
			difference_type	start = std::distance(this->begin(), first);
			
			this->_size -= n;
			for (size_type i = start; i < this->size(); ++i)
			{
				this->_alloc.destroy(this->_start + i);
				this->_alloc.construct(this->_start + i, *(this->_start + i + n));
			}
			return (first);
		}

		void	swap(vector & x)
		{
			if (this == &x)
				return ;
			size_type		size(this->_size);
			allocator_type	alloc(this->_alloc);
			size_type		capacity(this->_capacity);
			pointer			start(this->_start);

			this->_size = x._size;
			this->_alloc = x._alloc;
			this->_capacity = x._capacity;
			this->_start = x._start;
			x._size = size;
			x._alloc = alloc;
			x._capacity = capacity;
			x._start = start;
			return ;
		}

		void	clear(void)
		{
			for (; this->size() != 0; --this->_size)
				this->_alloc.destroy(this->_start + this->size() - 1);
			return ;
		}

		/*
		 * Operators
		 */
		
		vector &	operator=(vector const & x)
		{
			if (&x != this)
				this->assign(x.begin(), x.end());
			return (*this);
		}

		/*
		 * Element access
		 */

		reference	operator[](size_type n)
		{ return	(*(this->_start + n)); }
		
		const_reference	operator[](size_type n) const
		{ return	(*(this->_start + n)); }

		reference	at(size_type n)
		{
			if (n >= this->size())
				throw std::out_of_range("vector::at: n >= this->size()");
			return ((*this)[n]);
		}
		
		const_reference	at(size_type n) const
		{
			if (n >= this->size())
				throw std::out_of_range("vector::at: n >= this->size()");
			return ((*this)[n]);
		}

		reference	front(void)
		{ return (*this->begin()); }
		
		const_reference	front(void) const
		{ return (*this->begin()); }
	
		reference	back(void)
		{ return (*(this->end() - 1)); }
		
		const_reference	back(void) const
		{ return (*(this->end() - 1)); }

		/* Iterators */

		iterator	begin(void)
		{ return (iterator(this->_start)); }

		const_iterator	begin(void) const
		{ return (const_iterator(this->_start)); }
		
		iterator	end(void)
		{ return (iterator(this->_start + this->_size)); }

		const_iterator	end(void) const
		{ return (const_iterator(this->_start + this->_size)); }

		reverse_iterator	rbegin(void)
		{ return (reverse_iterator(this->end())); }
		
		const_reverse_iterator	rbegin(void) const
		{ return (const_reverse_iterator(this->end())); }
		
		reverse_iterator	rend(void)
		{ return (reverse_iterator(this->begin())); }
		
		const_reverse_iterator	rend(void) const
		{ return (const_reverse_iterator(this->begin())); }
};

template <class T, class Alloc>
bool	operator==(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin())); }

template <class T, class Alloc>
bool	operator!=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return (!(lhs == rhs)); }

template <class T, class Alloc>
bool	operator<(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }

template <class T, class Alloc>
bool	operator<=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return (lhs < rhs || lhs == rhs); }

template <class T, class Alloc>
bool	operator>(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return (!(lhs <= rhs)); }

template <class T, class Alloc>
bool	operator>=(vector<T, Alloc> const & lhs, vector<T, Alloc> const & rhs)
{ return (lhs > rhs || lhs == rhs); }

template<class T, class Alloc>
void	swap(vector<T, Alloc> & lhs, vector<T, Alloc> & rhs)
{ return (lhs.swap(rhs)); }

}

#endif
