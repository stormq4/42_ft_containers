/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_test.cpp                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: sde-quai <sde-quai@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/16 10:57:00 by sde-quai      #+#    #+#                 */
/*   Updated: 2022/09/19 14:25:48 by sde-quai      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <sstream>

#ifdef STD
	#include <vector>
	namespace ft = std;
#else
	#include "ft_vector.hpp"
#endif

// Constructors & Destructors
TEST_CASE("constructor test", "[vector]"){
	ft::vector<int> first;                                // empty vector of ints
	ft::vector<int> second (4,100);                       // four ints with value 100
	ft::vector<int> third (second.begin(),second.end());  // iterating through second
	ft::vector<int> fourth (third);                       // a copy of third

	// the iterator constructor can also be used to construct from arrays:
	int myints[] = {16,2,77,29};
	ft::vector<int> test (myints, myints + sizeof(myints) / sizeof(int) );
	CHECK(test[0] == 16);
	CHECK(test[1] == 2);
	CHECK(test[2] == 77);
	CHECK(test[3] == 29);
}

TEST_CASE("Copy assignemnt", "[vector]"){
	ft::vector<int> foo (3,0);
	ft::vector<int> bar (5,0);

	bar = foo;
	foo = ft::vector<int>();
	CHECK(foo.size() == 0);
	CHECK(bar.size() == 3);
}

// Iterators
TEST_CASE("Begin & end", "[vector]") {
	ft::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::stringstream ss;
	ss << "myvector contains:";
	for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
		ss << ' ' << *it;
	CHECK(ss.str() == "myvector contains: 1 2 3 4 5");
}

TEST_CASE("Rend & Rbegin", "[vector]") {
	ft::vector<int> myvector (5);  // 5 default-constructed ints

	ft::vector<int>::reverse_iterator rit = myvector.rbegin();

	int i=0;
	for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
		*rit = ++i;

	std::stringstream ss;
	ss << "myvector contains:";
	for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
		ss << ' ' << *it;
	CHECK(ss.str() == "myvector contains: 5 4 3 2 1");
}

TEST_CASE("Cbegin && Cend", "[vector]") {
	ft::vector<int> myvector = {10,20,30,40,50};

	std::stringstream ss;
	ss << "myvector contains:";

	for (auto it = myvector.cbegin(); it != myvector.cend(); ++it)
    	ss << ' ' << *it;
	CHECK(ss.str() == "myvector contains: 10 20 30 40 50");
}

TEST_CASE("Crend && End", "[vector]") {
	ft::vector<int> myvector = {1,2,3,4,5};

	std::stringstream ss;
	ss << "myvector backwards:";
	for (auto rit = myvector.crbegin(); rit != myvector.crend(); ++rit)
    	ss << ' ' << *rit;
	CHECK(ss.str() == "myvector backwards: 5 4 3 2 1");
}


// Capicity
TEST_CASE("Size", "[vector]") {
	ft::vector<int> myints;
	CHECK(myints.size() == 0);
	for (int i=0; i<10; i++) myints.push_back(i);
	CHECK(myints.size() == 10);
	myints.insert(myints.end(),10,100);
	CHECK(myints.size() == 20);
	myints.pop_back();
	CHECK(myints.size() == 19);
}

TEST_CASE("Max size && Capacity", "[vector]") {
	ft::vector<int> myvector;

	// set some content in the vector:
	for (int i=0; i<100; i++) myvector.push_back(i);
	CHECK(myvector.size() == 100);
	CHECK(myvector.capacity() == 128);
	// CHECK(myvector.max_size() == 1073741823);
}

TEST_CASE("Resize", "[vector]") {
	ft::vector<int> myvector;

	// set some initial content:
	for (int i=1;i<10;i++) myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);
	std::stringstream ss;
	ss << "myvector contains:";
	for (int i=0;i<myvector.size();i++)
		ss << ' ' << myvector[i];
	std::string test = ss.str();
	CHECK(test == "myvector contains: 1 2 3 4 5 100 100 100 0 0 0 0");
}

TEST_CASE("Empty") {
	ft::vector<int> myvector;
	int sum (0);

	for (int i=1;i<=10;i++) myvector.push_back(i);

	while (!myvector.empty())
	{
		sum += myvector.back();
		myvector.pop_back();
	}
	CHECK(myvector.empty() == true);
	CHECK(sum == 55);
}

TEST_CASE("Reserve", "[vector]") {
	ft::vector<int>::size_type sz;

	ft::vector<int> foo;
	sz = foo.capacity();
	for (int i=0; i<100; ++i) {
		foo.push_back(i);
		if (sz!=foo.capacity()) {
			sz = foo.capacity();
		}
	}

	ft::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	for (int i=0; i<100; ++i) {
		bar.push_back(i);
		if (sz!=bar.capacity()) {
			sz = bar.capacity();
			CHECK(sz == 100);
		}
	}
}

TEST_CASE("Shrink to fit", "[vector]") {

	ft::vector<int> myvector (100);
	CHECK(myvector.capacity() == 100);

	myvector.resize(10);
	CHECK(myvector.capacity() == 100);

	myvector.shrink_to_fit();
	CHECK(myvector.capacity() == 10);

}

// Element Access
TEST_CASE("Operator []", "[vector]") {
	ft::vector<int> myvector (10);   // 10 zero-initialized elements

	ft::vector<int>::size_type sz = myvector.size();

	// assign some values:
	for (unsigned i=0; i<sz; i++) myvector[i]=i;

	// reverse vector using operator[]:
	for (unsigned i=0; i<sz/2; i++)
	{
		int temp;
		temp = myvector[sz-1-i];
		myvector[sz-1-i]=myvector[i];
		myvector[i]=temp;
	}
	std::stringstream ss;
	ss << "myvector contains:";
	for (unsigned i=0; i<sz; i++)
		ss << ' ' << myvector[i];
	std::string test = ss.str();
	CHECK(test == "myvector contains: 9 8 7 6 5 4 3 2 1 0");
}

TEST_CASE("At", "[vector]") {
	ft::vector<int> myvector (10);   // 10 zero-initialized ints

	// assign some values:
	for (unsigned i=0; i<myvector.size(); i++)
		myvector.at(i)=i;

	std::stringstream ss;
	ss << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		ss << ' ' << myvector.at(i);
	CHECK(ss.str() == "myvector contains: 0 1 2 3 4 5 6 7 8 9");
}

TEST_CASE("Front && Back", "[vector]") {
	ft::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);
	myvector.push_back(1100);
	myvector.push_back(8);

	size_t test = myvector.front() - myvector.back();
	CHECK(myvector.front() == 78);
	CHECK(myvector.back() == 8);
	CHECK(test == 70);
}

TEST_CASE("Data", "[vector]") {
	ft::vector<int> myvector (5);

	int* p = myvector.data();

	*p = 10;
	++p;
	*p = 20;
	p[2] = 100;

	std::stringstream ss;
	ss << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); ++i)
		ss << ' ' << myvector[i];
	CHECK(ss.str() == "myvector contains: 10 20 0 100 0");
}

// Modifiers
TEST_CASE("Assign", "[vector]") {
	ft::vector<int> first;
	ft::vector<int> second;
	ft::vector<int> third;

	first.assign (7,100);             // 7 ints with a value of 100

	ft::vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	CHECK(7 == first.size());
	CHECK(5 == second.size());
	CHECK(3 == third.size());
}

TEST_CASE("Push_back", "[vector]") {
	ft::vector<int> myvector;
	for (int i = 0; i < 10; i++)
		myvector.push_back(i * 10);
	for (int i = 0; i < 10; i++)
		CHECK(myvector[i] == i * 10);
	CHECK(myvector.size() == 10);
}

TEST_CASE("Pop_back", "[vector]") {
	int myInt[] = {1, 3, 5, 7, -100, 200, 9000};
	ft::vector<int> vec;
	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);
	vec.push_back(7);
	vec.push_back(-100);
	vec.push_back(200);
	vec.push_back(9000);

	vec.pop_back();
	vec.pop_back();
	vec.pop_back();
	CHECK(vec.size() == 4);
	CHECK(vec[0] == 1);
	CHECK(vec[1] == 3);
	CHECK(vec[2] == 5);
	CHECK(vec[3] == 7);
}

TEST_CASE("Insert", "[vector]") {
	ft::vector<int> myvector (3,100);
	ft::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert ( it , 200 );

	myvector.insert (it,2,300);

	// "it" no longer valid, get a new one:
	it = myvector.begin();

	ft::vector<int> anothervector (2,400);
	myvector.insert(it+2,anothervector.begin(),anothervector.end());

	int myarray [] = { 501,502,503 };
	myvector.insert(myvector.begin(), myarray, myarray+3);

	std::stringstream ss;
	ss << "myvector contains:";
	for (it=myvector.begin(); it<myvector.end(); it++)
		ss << ' ' << *it;
	CHECK(myvector.size() == 11);
	CHECK(ss.str() == "myvector contains: 501 502 503 300 300 400 400 200 100 100 100");
}

TEST_CASE("Erase", "[vector]") {
	ft::vector<int> myvector;

	// set some values (from 1 to 10)
	for (int i=1; i<=10; i++)
		myvector.push_back(i);

	// erase the 6th element
	myvector.erase(myvector.begin()+5);

	// erase the first 3 elements:
	myvector.erase(myvector.begin(),myvector.begin()+3);

	std::stringstream ss;
	ss << "myvector contains:";
	for (size_t i=0; i<myvector.size(); ++i)
		ss << ' ' << myvector[i];
	CHECK(ss.str() == "myvector contains: 4 5 7 8 9 10");
}

TEST_CASE("Swap", "[vector]") {
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::stringstream ss;
	ss << "foo contains:";
	for (unsigned i=0; i<foo.size(); i++)
		ss << ' ' << foo[i];

	std::stringstream ss2;
	ss2 << "bar contains:";
	for (unsigned i=0; i<bar.size(); i++)
		ss2 << ' ' << bar[i];
	CHECK(ss.str() == "foo contains: 200 200 200 200 200");
	CHECK(ss2.str() == "bar contains: 100 100 100");
}

TEST_CASE("Clear", "[vector]") {
	ft::vector<int> myvector;
	myvector.push_back (100);
	myvector.push_back (200);
	myvector.push_back (300);

	std::stringstream ss;
	ss << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		ss << ' ' << myvector[i];

	myvector.clear();
	myvector.push_back (1101);
	myvector.push_back (2202);

	std::stringstream ss2;
	ss2 << "myvector contains:";
	for (unsigned i=0; i<myvector.size(); i++)
		ss2 << ' ' << myvector[i];
	CHECK(ss.str() == "myvector contains: 100 200 300");
	CHECK(ss2.str() == "myvector contains: 1101 2202");	
}

TEST_CASE("Emplace", "[vector]") {
	ft::vector<int> myvector = {10,20,30};

	auto it = myvector.emplace( myvector.begin()+1, 100 );
	myvector.emplace( it, 200 );
	myvector.emplace( myvector.end(), 300 );

	std::stringstream ss;
	ss << "myvector contains:";
	for (size_t i = 0; i < myvector.size(); i++)
		ss << ' ' << myvector[i];
	CHECK(ss.str() == "myvector contains: 10 200 100 20 30 300");
}

TEST_CASE("Emplace_back", "[vector]") {
	ft::vector<int> myvector = {10,20,30};

	myvector.emplace_back(100);
	myvector.emplace_back(200);

	std::stringstream ss;
	ss << "myvector contains:";
	for (size_t i = 0; i < myvector.size(); i++)
		ss << ' ' << myvector[i];
	CHECK(ss.str() == "myvector contains: 10 20 30 100 200");
}

// Allocator
TEST_CASE("Get_allocator", "[vector]") {
	ft::vector<int> myvector;
	int * p;
	unsigned int i;

	// allocate an array with space for 5 elements using vector's allocator:
	p = myvector.get_allocator().allocate(5);

	// construct values in-place on the array:
	for (i=0; i<5; i++) myvector.get_allocator().construct(&p[i],i);

	std::stringstream ss;
	ss << "The allocated array contains:";
	for (i=0; i<5; i++) ss << ' ' << p[i];

	// destroy and deallocate:
	for (i=0; i<5; i++) 
		myvector.get_allocator().destroy(&p[i]);
	
	myvector.get_allocator().deallocate(p,5);
	
	CHECK(ss.str() == "The allocated array contains: 0 1 2 3 4");
}

TEST_CASE("Realtional Operators", "[vector]") {
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (2,200);   // two ints with a value of 200

	std::stringstream ss;
	if (foo==bar) ss << "foo and bar are equal";
	if (foo!=bar) ss << "foo and bar are not equal";
	CHECK(ss.str() == "foo and bar are not equal");
	
	std::stringstream ss1;

	if (foo< bar) ss1 << "foo is less than bar";
	if (foo> bar) ss1 << "foo is greater than bar";
	CHECK(ss1.str() == "foo is less than bar");

	
	std::stringstream ss2;
	if (foo<=bar) ss2 << "foo is less than or equal to bar";
	if (foo>=bar) ss2 << "foo is greater than or equal to bar";
	CHECK(ss2.str() == "foo is less than or equal to bar");

}

TEST_CASE("Swap 2", "[vector]") {

	unsigned int i;
	ft::vector<int> foo (3,100);   // three ints with a value of 100
	ft::vector<int> bar (5,200);   // five ints with a value of 200

	foo.swap(bar);

	std::stringstream ss;
	ss << "foo contains:";
	for (ft::vector<int>::iterator it = foo.begin(); it!=foo.end(); ++it)
		ss << ' ' << *it;
	CHECK(ss.str() == "foo contains: 200 200 200 200 200");
	
	std::stringstream ss1;

	ss1 << "bar contains:";
	for (ft::vector<int>::iterator it = bar.begin(); it!=bar.end(); ++it)
		ss1 << ' ' << *it;
	CHECK(ss1.str() == "bar contains: 100 100 100");
}
