#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Item {
	Item <T>* prevNode;
	T data;
	Item() {
		prevNode = nullptr;
	}

	Item(T Data) : data(Data) {
		prevNode = nullptr;
	}
};

template <typename T>
class Stack {
	Item <T>* top;
	//int Ssize;

public:
	Stack() {
		top = nullptr;
	}

	void push(T dataItem) {
		Item<T>* newItem = new Item<T>(dataItem);
		newItem->prevNode = top;
		top = newItem;
	}

	T getTop() {
		return top->data;
	}

	bool isEmpty() {
		return top == nullptr;
	}

	//Throw an error in isEmpty().
	T pop() {
		if (isEmpty()) {
			throw std::invalid_argument("ERROR: Stack is empty.");
		}
		T data = top->data;
		Item<T>* toDelete = top;
		top = top->prevNode;
		delete toDelete;
		return data;
	}

	void clear() {
		while (top != nullptr) {
			Item<T>* toDelete = top;
			top = top->prevNode;
			delete toDelete;
		}
	}

	void Display() {
		cout << "Displaying Stack..." << endl << endl;
		Item <T>* cursor = top;
		while (cursor) {
			cout << cursor->data << ", " << endl;
			cursor = cursor->prevNode;
		}
		cout << endl << endl;
		cout << "That's it." << endl;
	}

	//haven't checked for all datatypes
	string parseStack() {
		Item <T>* cursor = top;
		string returnTo = "";

		while (cursor) {
			string converted = to_string(cursor->data);
			returnTo += converted;
			if (cursor->prevNode)
				returnTo += ",";
			cursor = cursor->prevNode;
		}
		return returnTo;
	}


};