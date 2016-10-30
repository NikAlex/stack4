#include <iostream>
#include <new>  
#include <stdexcept>
#include <vector>
     
template<typename T> //копирование памяти
auto mem_copy(const T * tmp, size_t L, size_t R) -> T * {
	T * arr = new T[R];
	try {
		std::copy(tmp, tmp + L, arr);
	}
	catch (...) {
		delete[] arr;
		throw;
	}
	return arr;
}

  
class BitSet {
public:
	BitSet(size_t size = 0);
	auto reset() noexcept -> void;
	auto reset(size_t tmp)-> void;
	auto set() noexcept -> void;
	auto set(size_t tmp)-> void;
	auto test(size_t tmp) const-> int;
	auto resize() noexcept -> void;
	auto size() const noexcept->size_t;
private: 
	std::vector<int> bitset;

};
auto BitSet::size() const noexcept -> size_t {//получаем размер битсета
	return bitset.capacity();
}

BitSet::BitSet(size_t size): bitset(size) {//инициализируем битсет
	this->reset();
}


auto BitSet::reset() noexcept->void {//сбрасываем значения битсета
	for (auto i : bitset) {
		i = 0;
	}
}


auto BitSet::reset(size_t tmp)->void {//сбрасываем конкретное значение
	if (tmp < bitset.size()) {
		bitset.at(tmp) = 0;
	}
	else {
		throw std::out_of_range("Error");
	}
}


auto BitSet::set() noexcept->void {//устанавливаем все 1 
	for (auto i : bitset) {
		i = 1;
	}
}


auto BitSet::set(size_t tmp)->void {//устанавливаем 1 в нужном месте
	if (tmp < bitset.size()) {
		bitset.at(tmp) = 1;
	}
	else {
		throw std::out_of_range("Error");
	}
}


auto BitSet::test(size_t tmp) const->int {//проверка битсета
	if (tmp < bitset.size()) {
		return bitset.at(tmp);
	}
	else {
		throw std::out_of_range("Error");
	}
}

auto BitSet::resize() noexcept -> void {//увеличение вектора знач-я битсета
	bitset.resize(bitset.size() * 2 + (bitset.size() == 0));
}

//__________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________

template<typename T>
class allocator
{
public:
	explicit
	allocator(size_t size = 0);
	allocator(allocator const & tmp);
	~allocator();
	auto resize() ->void;
	auto construct(T * ptr, T const& value) ->void;
	auto destroy(T * ptr)->void;
	
	auto swap(allocator& other)->void;
	auto operator=(allocator const&)->allocator& = delete;

	auto get() noexcept->T *;
	auto get() const noexcept->T const *;
	auto count() const noexcept->size_t;
	auto full() const noexcept->bool;
	auto empty() const noexcept->bool;

	template <typename FwdIter>
	auto destroy(FwdIter first, FwdIter last)->void;
	
	
private:
	T * ptr_;
	size_t size_;
	size_t count_;
	BitSet bs;


};

//__________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________




template <typename T>//конструктор с параметром 
allocator<T>::allocator(size_t size): ptr_(static_cast<T *>(size == 0 ? nullptr : operator new(size * sizeof(T)))), size_(size), count_(0),bs(0) {};

template<typename T>//конструктор копирования 
allocator<T>::allocator(allocator const & tmp) :
	ptr_(static_cast<T *>(tmp.size_ == 0 ? nullptr : operator new(tmp.size_ * sizeof(T)))),size_(tmp.size_),count_(0),bs(tmp.bs) {
	
	for (size_t i = 0; i < tmp.count_; ++i) {
		if (bs.test(i)) {
			(*this).construct((*this).ptr_ + i, tmp.ptr_[i]);
		}
	}
}

template <typename T>//деструктор
allocator<T>::~allocator() {
	if (count_ > 0) {
		destroy(ptr_, ptr_ + count_);
	}
	operator delete(ptr_);
};

template <typename T>//реализация свап
auto allocator<T>::swap(allocator & other)->void {
	std::swap(ptr_, other.ptr_);
	std::swap(size_, other.size_);
	std::swap(count_, other.count_);
	std::swap(bs, other.bs);
};

template <typename T>//инициализация
auto allocator<T>::construct(T * ptr, T const & value)->void {
	if (ptr < ptr_ || ptr > ptr_ + size_) {
		throw std::out_of_range("Error");
	}
	new(ptr) T(value);
	std::cout << count_ << std::endl;
	bs.set(count_);
	++count_;
	
	
	
}

template <typename T>//удаление всего ptr_
auto allocator<T>::destroy(T * ptr)->void
{
	if (ptr < ptr_ || ptr > ptr_ + size_) {
		throw std::out_of_range("Error");
	}
	ptr->~T();

	--count_;
	bs.reset(count_);
	
	
}


template <typename T>//удаление диапазона
template<typename FwdIter>
auto allocator<T>::destroy(FwdIter first, FwdIter last)->void
{
	for (; first != last; ++first) {
		destroy(&*first);
	}
}

template<typename T>//увеличиваем память
auto allocator<T>::resize()-> void {
	size_t size = size_ * 2 + (size_ == 0);
	T * newArray = mem_copy(ptr_, count_, size);
	delete[] ptr_;
	ptr_ = newArray;
	size_ = size;
	bs.resize();
}

template<typename T>//проверка на пустоту
auto allocator<T>::empty() const noexcept-> bool {
	return (count_ == 0);
}

template<typename T>//проверка на заполненность
auto allocator<T>::full() const noexcept-> bool {
	return (count_ == size_);
}

template<typename T>//получить ptr_
auto allocator<T>::get() noexcept-> T * {
	return ptr_;
}

template<typename T>//получить ptr_ const метод
auto allocator<T>::get() const noexcept-> T const * {
	return ptr_;
}

template<typename T>//вернуть count_
auto allocator<T>::count() const noexcept-> size_t {
	return count_;
}

//__________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________

template <typename T>
class stack 
{
public:
	explicit stack(size_t size = 0);/*noexcept*/
	stack(stack const &); /*strong*/
	auto count() const noexcept->size_t;/*noexcept*/
	auto push(T const &)->void;/*strong*/
	auto pop()->void;/*strong*/
	auto top() const->const T&;/*strong*/
	~stack(); 	/*noexcept*/
	auto operator=(const stack &tmp)->stack&;/*strong*/
	auto empty() const noexcept->bool;/*noexcept*/
private:
	allocator<T> allocate;
};

//__________________________________________________________________________________________________________________
//__________________________________________________________________________________________________________________



template<typename T>//проверка на пустоту
auto stack<T>::empty() const noexcept->bool {
	return (allocate.count() == 0);
}

template <typename T>//деструктор стэка
stack<T>::~stack() {
	allocate.destroy(allocate.get(), allocate.get() + allocate.count());
};

template <typename T>//конструктор с параметром
stack<T>::stack(size_t size) : allocate(size) {};



template <typename T>//добавление элементов в стэк
auto stack<T>::push(T const &val)->void {
	if (allocate.empty() == true || allocate.full() == true) {
		allocate.resize();
	}
	allocate.construct(allocate.get() + allocate.count(), val);
}


template <typename T>//конструктор копирования
stack<T>::stack(stack const &tmp):allocate(tmp.allocate) {};

template <typename T>//оператор присваивания
auto stack<T>::operator=(const stack &tmp)->stack&  {
	if (this != &tmp) {
		
		(allocator<T>(tmp.allocate)).swap((*this).allocate);
	}
	return *this;
}


template <typename T>//вернуть count_
auto stack<T>::count() const noexcept->size_t {
	return allocate.count();
}

template <typename T>//удаление элемента
auto stack<T>::pop()->void {
	if (allocate.count() == 0) throw std::logic_error("Empty!");
	allocate.destroy(allocate.get() + allocate.count());
}

template <typename T>//возвращаем верхний элемент стэка
auto stack<T>::top() const->const T&{
	if (allocate.count() == 0) throw std::logic_error("Empty!");
return allocate.get()[allocate.count() - 1];

}
