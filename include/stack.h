// объявление и реализация шаблонного стека
// стек поддерживает операции: 
// - вставка элемента, 
// - извлечение элемента, 
// - просмотр верхнего элемента (без удаления)
// - проверка на пустоту, 
// - получение количества элементов в стеке
// - очистка стека
// при вставке в полный стек должна перевыделяться память

#pragma once

#include <iostream>

using namespace std;

const size_t MAX_STACK_CAPACITY = 10000000;

template <typename T>
class stack
{
private:
	size_t capacity;
	size_t size;
	T* data;

	bool full()
	{
		return(size == capacity);
	}

public:
	stack(const size_t capacity_ = 10) :capacity(capacity_), size(0)
	{
		if (capacity > MAX_STACK_CAPACITY)
		{
			throw "capacity_is_too_large";
		}

		data = new T[capacity];
	}

	~stack()
	{
		delete[] data;
	}

	size_t stack_size()
	{
		return size;
	}

	bool empty()
	{
		return(size == 0);
	}

	void clear()
	{
		size = 0;
		delete[] data;
		data = new T[capacity];
	}

	void change_capacity()
	{
		if (capacity * 2 <= MAX_STACK_CAPACITY)
		{
			capacity *= 2;
		}
		else
		{
			capacity = MAX_STACK_CAPACITY;
		}
		if (capacity == 0)
		{
			capacity++;
		}
		T* temp = new T[capacity];
		for (size_t i = 0; i < size; i++)
		{
			temp[i] = data[i];
		}
		delete[] data;
		data = temp;
	}

	void push(const T& elem)
	{
		if (size + 1 > MAX_STACK_CAPACITY)
		{
			throw "MAX_CAPACITY";
		}
		if (full())
		{
			change_capacity();
		}
		size++;
		data[size - 1] = elem;
	}

	T pop()
	{
		if (empty())
		{
			throw "STACK_EMPTY";
		}
		T temp = data[size - 1];
		size--;
		return temp;
	}

	T& top()
	{
		if (empty())
		{
			throw "STACK_EMPTY";
		}
		return data[size - 1];
	}
};