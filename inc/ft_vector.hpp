/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_vector.hpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 13:08:45 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/09/13 16:34:59 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	FT_VECTOR_HPP
# define FT_VECTOR_HPP

#include <memory>
#include <iostream>
#include <limits>

namespace ft {
    template < class T, class Alloc = std::allocator<T> > class vector {
		
			/***********************************
			************************************				
			-------		Member Types		----
			************************************
			***********************************/
		public:
			typedef	T 					value_type;
			typedef	Alloc 				allocator_type;
			typedef	value_type&			reference;
			typedef const value_type&	const_reference;
			typedef	value_type*			pointer;
			typedef	const value_type*	const_pointer;
			typedef	value_type			iterator; //
			typedef const value_type	const_iterator; //
			typedef iterator			reverse_iterator; //
			typedef const_iterator		const_reverse_iterator; //
			typedef	ptrdiff_t			difference_type;
			typedef	size_t				size_type;

		
		private:
			size_type					_size;
			size_type					_capacity; // what is cappacity??
			allocator_type				_alloc;
			pointer						_array;
			
			
			
			/***********************************
			************************************				
			------	Member functions	--------
			************************************
			***********************************/
			
		public:
		
			/*****************************/
			/*~~~~~~ Constructors ~~~~~~~*/
			/*****************************/
			explicit vector (const allocator_type& alloc = allocator_type())
			: _size(0), _capacity(0), _array(NULL), _alloc(alloc) { return ; }
			
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			: _size(0), _capacity(n), _alloc(alloc) { 
				pointer	tmp;
				
				if (n > 0)
					tmp = alloc.allocate(n);
				else 
					tmp = NULL;
				for (size_type i = 0; i < n; i++) {
					this->push_back(val);
				}
				_array = tmp;
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()); // iterator

			vector (const vector& x)
			: _size(x._size), _capacity(x._capacity), _alloc(x._alloc), _value_type(_x._value_type) { return ; }

			/****************************/
			/*~~~~~~ Destructors ~~~~~~~*/
			/****************************/
			~vector () {
				
			}
			
			/********************************/
			/*~~~~~~ Copy Assignment ~~~~~~~*/
			/********************************/

			vector	&operator= (const vector &ref);

			/**************************/
			/*~~~~~~ Iterators ~~~~~~~*/
			/**************************/

			iterator				begin ();
			const_iterator 			begin () const;
			iterator				end ();
			const_iterator			end () const;
			reverse_iterator		rbegin ();
			const_reverse_iterator	rbegin () const;
			reverse_iterator		rend ();
			const_reverse_iterator	rend () const;
			const_iterator			cbegin () const noexcept;
			const_iterator			cend () const noexcept;
			const_reverse_iterator	crbegin () const noexcept;
			const_reverse_iterator	crend () const noexcept;

			/*************************/
			/*~~~~~~ Capacity ~~~~~~~*/
			/*************************/

			size_type			size () const { return this->_size; };
			
			size_type			max_size () const { return this->_alloc.max_size(); }
			
			void				resize (size_type n, value_type val = value_type()) {
				if (n < _size) {
					while (_size > n)
						this->pop_back();
				}
				// if (n > _size) {
				// 	while (_size < n)
				// 		this->push_back(val);
				// }
				if (n > _capacity) {
					
				}
			}
			
			size_type			capacity () const { return this->_capacity; }
			bool				empty () const { 
				if _size == 0
					return true;
				return false;
			}
			void				reserve (size_type n);
			void				shrink_to_fit ();
			
			/*******************************/
			/*~~~~~~ Element Access ~~~~~~~*/
			/*******************************/

			reference 			operator[] (size_type n);
			const_reference 	operator[] (size_type n) const;	
			reference 			at (size_type n);
			const_reference 	at (size_type n) const;
			reference 			front ();
			const_reference		front () const;
			reference			back ();
			const_reference		back () const;
			value_type*			data () noexcept;
			const value_type*	data () const noexcept;

			/**************************/
			/*~~~~~~ Modifiers ~~~~~~~*/
			/**************************/
			template <class InputIterator>
  			void 				assign (InputIterator first, InputIterator last);
			void 				assign (size_type n, const value_type& val);
			
			void 				push_back (const value_type& val) {
				// if (_size > _capacity)
					// doo something
				this->_alloc.construct(&(this->_array[_size]), val);
				this->_size++;
			}
			
			void 				pop_back () { 
				this->_size--;
				this->_alloc.destroy(&this->(_array[this->_size]));
			}
			
			iterator 			insert (iterator position, const value_type& val);
			void 				insert (iterator position, size_type n, const value_type& val);
			template <class InputIterator>
			void 				insert (iterator position, InputIterator first, InputIterator last);
			iterator 			erase (iterator position);
			iterator 			erase (iterator first, iterator last);
			void 				swap (vector& x);
			
			void 				clear() {
				while (this->empty() == false)
					this->pop_back();
			}
			
			template <class... Args>
			iterator 			emplace (const_iterator position, Args&&... args);
			template <class... Args>
 			void 				emplace_back (Args&&... args);

			/**************************/
			/*~~~~~~ Allocator ~~~~~~~*/
			/**************************/
			allocator_type		get_allocator () const { return this->_alloc; }
			
	};
	
	/*************************************/
	/*~~~~~~ Relational Operators ~~~~~~~*/
	/*************************************/
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);\

	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

	/*********************/
	/*~~~~~~ Swap ~~~~~~~*/
	/*********************/
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

};

#endif
