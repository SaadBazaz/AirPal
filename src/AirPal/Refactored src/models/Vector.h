#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class Vector
{
private:
	int size;
	int capacity;
	T* arr;
public:
	typedef T* iterator;
	Vector() {
		arr = nullptr;
		size = 0;
		capacity = 0;
	}
	Vector<T>(int Size) {
		arr = new T[Size];
		size = 0;
		capacity = Size;
	}
	Vector(int Size, T& initialize) {
		array = new T[Size];
		capacity = Size;
		for (int i = 0; i < capacity; i++)
			array[i] = initialize;
		size = capacity;
	}
	Vector(const Vector& toCopy) {
		arr = new T[toCopy.Size()];
		for (int i = 0; i < toCopy.Size(); i++) {
			arr[i] = toCopy.arr[i];
		}
		size = toCopy.Size();
		capacity = toCopy.Capacity();
	}
	void resize(int capacity, T value = T()) {
		int i = 0;
		if (isEmpty())
			arr = new T[capacity];
		else {
			Vector<T> tempstring = *this;
			delete[] this->arr;
			this->arr = new T[capacity];
			for (i = 0; i < size && i < capacity; i++)
				this->arr[i] = tempstring[i];
		}
		for (int j = i; j < capacity; j++) {
			arr[j] = value;
		}
		this->capacity = capacity;
	}
	T push_back(T data) {
		if (size == capacity)
			resize((capacity + 1) * 2);
		return arr[size++] = data;
	}

	T pop() {
		if (isEmpty())
			return T();
		T returnTo = arr[size - 1];
		size--;
		return returnTo;
	}

	int find(T ex) {
		for (int i = 0; i < size; i++)
			if (arr[i] == ex)
				return i;
		return -1;
	}

	iterator begin() {
		return arr;
	}

	iterator end() {
		if (isEmpty())
			return arr;
		return arr + Size() - 1;
	}

	bool erase(iterator it) {
		for (iterator theit = it; theit != end(); theit++)
			*theit = *(theit + 1);
		size--;
		return true;
	}

	int Capacity() const {
		return capacity;
	}

	int Size() const {
		return size;
	}

	bool isEmpty() {
		return (arr == nullptr) || (size == 0);
	}

	void clear() {
		delete[] arr;
		size = 0;
		capacity = 0;
	}

	T& operator[](int index) {
		/*if (isEmpty())
			throw invalid_argument("The vector is empty!");*/
		if (index < 0 || index > size)
			throw out_of_range("The index is out of range!");
		return arr[index];
	}

	Vector<T> operator=(const Vector& toCopy) {
		if (!isEmpty())
			clear();
		arr = new T[toCopy.Size()];
		capacity = toCopy.Capacity();
		for (int i = 0; i < toCopy.Size(); i++)
			arr[i] = toCopy.arr[i];
		size = toCopy.Size();
		return *this;
	}

	//append a Vector
	Vector<T> operator+(const Vector& toCopy) {

		Vector<T> tempvector;
		for (int i = 0; i < this->size; i++)
			tempvector.push_back(this->arr[i]);

		for (int i = 0; i < toCopy.Size(); i++)
			tempvector.push_back(toCopy.arr[i]);

		return tempvector;
	}

	//append a Vector
	Vector<T>& operator+=(const Vector& toCopy) {

		for (int i = 0; i < toCopy.Size(); i++)
			this->push_back(this->toCopy[i]);

		return *this;
	}
	void MakeEmpty();
	T findMin();
	~Vector<T>()
	{
		//cout << "In Vector Class Destructor.\n\n";
		delete[]arr;
	}
};

template <typename T>
T Vector<T>::findMin()
{
	if (isEmpty())
	{
		return NULL;
	}
	else
	{
		T min = arr[0];
		for (int i = 0; i < size; i++)
		{
			if (min > arr[i])
			{
				min = arr[i];
			}
		}
		return min;
	}
}

template <typename T>
void Vector<T>::MakeEmpty()
{
	delete[] arr;
	size = 0;
	arr = new T[capacity];
}
