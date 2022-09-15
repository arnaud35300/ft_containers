/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arguilla <arguilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 14:56:35 by arguilla          #+#    #+#             */
/*   Updated: 2022/09/15 11:19:08 by arguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>

# ifndef USE_STL
#  define USE_STL 1
# endif

#if USE_STL //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	#include <set>
	namespace ft = std;
#else
	#include <main.hpp>
#endif

#include <stdlib.h>

#define MAX_RAM 429496729//6
#define BUFFER_SIZE 4096

struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};

#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

/************************/


template<typename T>
void	print_content(ft::vector<T> & ctn)
{
	typename ft::vector<T>::iterator it = ctn.begin();
	typename ft::vector<T>::iterator ite = ctn.end();
	typename ft::vector<T>::reverse_iterator rit = ctn.rbegin();

	std::cout << "-*-*-*- VECTOR -*-*-*-" << std::endl;
	std::cout << "size: " << ctn.size() << std::endl;
	std::cout << "capacity: " << ctn.capacity() << std::endl;

	ctn.push_back(999999);

	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	it = ctn.begin();
	std::cout << *it << std::endl;
	++it;
	std::cout << *it << std::endl;
	--it;
	std::cout << *it << std::endl;
	++it;
	++it;
	std::cout << *it << std::endl;
	std::cout << *rit << std::endl;
	++rit;
	std::cout << *rit << std::endl;
	++rit;
	std::cout << *rit << std::endl;

	it = ctn.begin();
	ctn.erase(it);
	it = ctn.begin();
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
}

template<typename T, typename C>
void	print_content(ft::map<T,C> & ctn)
{
	typename ft::map<T, C>::iterator it = ctn.begin();
	typename ft::map<T, C>::iterator ite = ctn.end();
	typename ft::map<T, C>::reverse_iterator rit = ctn.rbegin();

	std::cout << "-*-*-*- MAP -*-*-*-" << std::endl;
	std::cout << "size: " << ctn.size() << std::endl;
	
	ctn.insert(ft::make_pair(999999, 999999));
	while (it != ite)
	{
		std::cout << it->first << " " << it->second << std::endl;
		++it;
	}

	it = ctn.begin();
	std::cout << it->first << " " << it->second << std::endl;
	++it;
	std::cout << it->first << " " << it->second << std::endl;
	--it;
	std::cout << it->first << " " << it->second << std::endl;
	++it;
	++it;
	std::cout << it->first << " " << it->second << std::endl;
	std::cout << rit->first << " " << rit->second << std::endl;
	++rit;
	std::cout << rit->first << " " << rit->second << std::endl;
	++rit;
	std::cout << rit->first << " " << rit->second << std::endl;

	it = ctn.begin();
	ctn.erase(it);
	it = ctn.begin();
	while (it != ite)
	{
		std::cout << it->first << " " << it->second << std::endl;
		++it;
	}
		
#if USE_STL == 0 && 0
	typename ft::map<T, C>::iterator root = ctn._root;
	std::cout << root->first << std::endl;
	ctn.print_tree(ctn._root);
#endif 


}

template<typename T>
void	print_content(ft::set<T> & ctn)
{
	typename ft::set<T>::iterator it = ctn.begin();
	typename ft::set<T>::iterator ite = ctn.end();
	typename ft::set<T>::reverse_iterator rit = ctn.rbegin();

	std::cout << "-*-*-*- MAP -*-*-*-" << std::endl;
	std::cout << "size: " << ctn.size() << std::endl;
	
	ctn.insert(ft::make_pair(999999, 999999));
	while (it != ite)
	{
		std::cout << it->first << " " << it->second << std::endl;
		++it;
	}

	it = ctn.begin();
	std::cout << it->first << " " << it->second << std::endl;
	++it;
	std::cout << it->first << " " << it->second << std::endl;
	--it;
	std::cout << it->first << " " << it->second << std::endl;
	++it;
	++it;
	std::cout << it->first << " " << it->second << std::endl;
	std::cout << rit->first << " " << rit->second << std::endl;
	++rit;
	std::cout << rit->first << " " << rit->second << std::endl;
	++rit;
	std::cout << rit->first << " " << rit->second << std::endl;

	it = ctn.begin();
	ctn.erase(it);
	it = ctn.begin();
	while (it != ite)
	{
		std::cout << it->first << " " << it->second << std::endl;
		++it;
	}
}


template<typename T>
void	print_content(ft::stack<T> & ctn)
{
	std::cout << "-*-*-*- STACK -*-*-*-" << std::endl;
	std::cout << "size: " << ctn.size() << std::endl;
	
	while (!ctn.empty())
	{
		std::cout << ctn.top() << std::endl;
		ctn.pop();
	}
}

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand(), rand()));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand();
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;


/* MY TESTS */
	std::cout << ((USE_STL) ? "STL" : "FT") << std::endl;

	ft::vector<int> vec;
	ft::map<int,int> map;
	ft::stack<int> stack;
	ft::set<int> set;
	int	data[] = {11,24,88,9,49,55,77,12,69,39,22,48,86,70,99,85,95,66,47,90,97,21,26,17,16,64,67,89,71,96,35,30,45,98,78,83,61,57,56,29,28,1,5,91,44,4,75,50,32,73,92,84,14,33,54,20,19,79,6,87,46,42,34,10,43,7,65,68,93,100,2,74,31,81,76,40,41,53,80,63,37,15,13,3,62,94,52,27,59,38,8,36,60,18,72,58,23,25,82,51};

	for (int i = 0; i < 100; i++)
	{
		vec.push_back(data[i]);
		map.insert(ft::make_pair(data[i], i));
		set.insert(data[i]);
		stack.push(data[i]);
	}

	/* Vector */
	print_content<int>(vec);
	print_content<int>(stack);
	print_content<int, int>(map);

	return (0);
}