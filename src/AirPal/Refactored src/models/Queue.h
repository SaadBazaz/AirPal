#pragma once
#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
class Queue {
private:
	T* array;
	int size;
	int capacity;
public:
	typedef T* iterator;

	Queue() {
		array = nullptr;
		size = 0;
		capacity = 0;
	}

	Queue(int Size) {
		array = new T[Size];
		size = 0;
		capacity = Size;
	}

	Queue(int Size, T& initialize) {
		array = new T[Size];
		capacity = Size;
		for (int i = 0; i < capacity; i++)
			array[i] = initialize;
		size = capacity;
	}

	Queue(const Queue& toCopy) {
		array = new T[toCopy.Size()];
		for (int i = 0; i < toCopy.Size(); i++) {
			array[i] = toCopy.array[i];
		}
		size = toCopy.Size();
		capacity = toCopy.Capacity();
	}

	void resize(int capacity, T value = T()) {
		int i = 0;
		if (isEmpty())
			array = new T[capacity];
		else {
			Queue<T> tempstring = *this;
			delete[] this->array;
			this->array = new T[capacity];
			for (i = 0; i < size && i < capacity; i++)
				this->array[i] = tempstring[i];
		}
		for (int j = i; j < capacity; j++) {
			array[j] = value;
		}
		this->capacity = capacity;
	}

	T enqueue(T data) {
		if (size == capacity)
			resize((capacity + 1) * 2);
		return array[size++] = data;
	}

	T dequeue() {
		if (isEmpty())
			return T();
		
		T returnTo = array[0];
		for (int i = 0; i < size-1; i++) {
			array[i] = array[i + 1];
		}
		size--;

		return returnTo;
	}

	int find(T ex) {
		for (int i = 0; i < size; i++)
			if (array[i] == ex)
				return i;
		return -1;
	}

	iterator begin() {
		return array;
	}

	iterator end() {
		if (isEmpty())
			return array;
		return array + Size()-1;
	}

	int Capacity() const {
		return capacity;
	}

	int Size() const {
		return size;
	}

	bool isEmpty() {
		return (array == nullptr) || (size == 0);
	}

	bool erase(iterator it) {
		for (iterator theit = it; theit != end(); theit++)
			*theit = *(theit + 1);
		size--;
		return true;
	}


	void clear() {
		delete[] array;
		size = 0;
		capacity = 0;
	}


	T& operator[](int index) {
		if (isEmpty())
			throw invalid_argument("The vector is empty!");
		if (index < 0 || index >= size)
			throw out_of_range("The index is out of range!");
		return array[index];
	}

	Queue<T> operator=(const Queue& toCopy) {
		if (!isEmpty())
			clear();
		array = new T[toCopy.Size()];
		capacity = toCopy.Capacity();
		for (int i = 0; i < toCopy.Size(); i++)
			array[i] = toCopy.array[i];
		size = toCopy.Size();
		return *this;
	}



	//append a Vector
	Queue<T> operator+(const Queue& toCopy) {

		Queue<T> tempvector;
		for (int i = 0; i < this->size; i++)
			tempvector.enqueue(this->array[i]);

		for (int i = 0; i < toCopy.Size(); i++)
			tempvector.Queue(toCopy.array[i]);

		return tempvector;
	}

	//append a Vector
	Queue<T>& operator+=(const Queue& toCopy) {

		for (int i = 0; i < toCopy.Size(); i++)
			this->enqueue(this->toCopy[i]);

		return *this;
	}
};












//
//template <typename T>
//struct Item {
//	Item <T>* next;
//	T data;
//	Item() {
//		next = nullptr;
//	}
//
//	Item(T Data) : data(Data) {
//		next = nullptr;
//	}
//};
//
//template <typename T>
//class Queue {
//	Item <T>* top;
//	int Qsize;
//
//public:
//	Queue() :Qsize(0) {
//		top = nullptr;
//	}
//
//	bool isEmpty() {
//		return top == nullptr;
//	}
//
//	Item <T>* getTop() const {
//		return top;
//	}
//
//
//	void enqueue(T dataItem) {
//		Item<T>* newItem = new Item<T>(dataItem);
//		Item<T>* currNode = top;
//		Item<T>* prevNode = nullptr;
//		while (currNode != nullptr) {
//			prevNode = currNode;
//			currNode = currNode->next;
//		}
//		if (prevNode) {
//			prevNode->next = newItem;
//		}
//		else {
//			top = newItem;
//		}
//		Qsize++;
//	}
//
//
//
//	T dequeue() {
//		if (isEmpty()) {
//			cout << "EXCEPTION: Cannot dequeue an empty list." << endl;
//			return NULL;
//		}
//		Item<T>* toDelete = top;
//		top = top->next;
//		T temp = toDelete->data;
//		delete toDelete;
//		Qsize--;
//		return temp;
//	}
//
//	void clear() {
//		while (top != nullptr) {
//			Item<T>* toDelete = top;
//			top = top->next;
//			delete toDelete;
//		}
//		cout << "Queue cleared successfully." << endl;
//		Qsize = 0;
//	}
//
//	int getLength() const {
//		return Qsize;
//	}
//
//
//	void Display() {
//		cout << "Displaying Queue..." << endl;
//		Item <T>* cursor = top;
//		while (cursor) {
//			cout << cursor->data << ", ";
//			cursor = cursor->next;
//		}
//		cout << endl;
//
//	}
//
//	Item<T>* operator+=(const Queue<T>& otherQueue) {
//		Item<T>* currNode = top;
//		Item<T>* prevNode = nullptr;
//		while (currNode != nullptr) {
//			prevNode = currNode;
//			currNode = currNode->next;
//		}
//		if (prevNode) {
//			prevNode->next = otherQueue.getTop();
//		}
//		else {
//			top = otherQueue.getTop();
//		}
//		Qsize += otherQueue.getLength();
//		return this->getTop();
//	}
//
//
//};