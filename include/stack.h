#pragma once
#include <iostream>

using namespace std;

template <typename T>
class stack
{
public:
	stack();
	stack(const stack&);
	auto count() const noexcept->size_t;
	auto push(T const &)->void;
	auto pop()->T;
	auto empty()->bool;
	~stack();
	auto operator=(const stack&tmp)->stack&;
private:
	T * array_;
	size_t array_size_;
	size_t count_;
};
 
