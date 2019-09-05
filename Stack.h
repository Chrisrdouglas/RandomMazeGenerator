/***********Generic Stack Class******************
* Trying to make this class as generic as possible for use in future projects.
* It has the following variables:
*		T* stack:
*				the actual data will be stored in an array and this will point to it
*		int size:
*				this int is used to locate the top of the stack
*		int capacity:
*				used to increase the size of the stack when appropiate.
*				it is also used to see when the stack is full.
*
* It has the following methods:
*		bool push(const T a):
*				pushes an item onto the stack and returns true. if the stack
*				is full then it will return false and not push the item onto
*				the stack
*		bool pop(T & item):
*				gets the element on the top of the stack and places it into
*				some variable then removes that item from the stack
*		bool getTop(T & item):
*				gets the top of the stack and places it into some variable.
*				this does not remove it from the stack
*		bool isEmpty():
*				reports if there is anything on the stack.
*		void print():
*				prints the contents of the stack. if the stack is empty then
*				it will print "Contents of the stack: and nothing else
*		void chrisExpand():
*				a slow and costly method that increases the size of the stack
*				by n units each time by making a new array with the new capacity
*				and then deletes the old one.
*		void chrisPush(const T item):
*				a method that pushes an item onto the stack. if the stack is full
*				then this method can resize it.
*
* It has the following constructors + destructor:
*		Stack():
*				makes a stack of size 100;
*		Stack(int s):
*				Allows a Stack object to me made with the capacity of s
*		~Stack():
*				Deletes T* stack. 
*/

//	Professor,
//		I could have put part of it in a .cpp file but i figured this would make for less files to keep track of on your end.
//		hope that helped! - chris

#ifndef STACK_H
#define STACK_H

#pragma once

#include <iostream>

template <typename T>
class Stack
{
private://data has been made private to prevent other classes from causing chaos
	T* stack;
	int size, capacity;

public:

	/************Stack(int)***************
	* Constructor that takes a single int to make a custom sized stack.
	* s is used for the initial size
	*/
	Stack(int s)
	{
		stack = new T[s];
		size = 0;
		capacity = s;
	}

	/************Stack()***************
	* Generic constructor that takes no arguments
	*/
	Stack()
	{
		capacity = 100;
		stack = new T[capacity];
		size = 0;
	}

	/************~Stack()***************
	* Generic destructor that takes no arguments
	* and releases the allocated memory
	*/
	~Stack()
	{
		delete[] stack;
	}


	/************push()***************
	* places an object on top of the stack
	* If the stack is full (all of the
	* dynamically allocated memory has been
	* used) then it returns false.
	* If the ojbect was sucessfully pushed
	* onto the stack then the method
	* returns true.
	*/
	bool push(const T a) 
	{
		if (size == capacity) { return false; } //if the size equals the capacity then the stack is full
		stack[size++] = a;
		return true; // at this point a should have been pushed onto the stack
	}


	/************pop()***************
	* Gets the object on top of the stack
	* and gives it to item.
	* If the stack is empty then it returns
	* false.
	* If the stack is not empty then it
	* give the top of the stack to item and
	* returns true.
	*/
	bool pop(T & item)
	{
		if (isEmpty()) { return false; } //if the size is 0 then there is nothing on the stack and there is nothing to fill item with
		item = stack[--size];
		return true; //the item has been popped
	}

	/************getTop()***************
	* Similar functionallity to pop but
	* the object at the top of the stack
	* doesn't dissapear.
	* If the stack is empty then it returns
	* false.
	* If the stack is not empty then it
	* give the top of the stack to item and
	* returns true.
	*/
	bool getTop(T & item) const
	{
		if (isEmpty()) { return false; } //if the size is 0 then there is nothing on the stack and there is nothing to fill item with
		item = stack[size-1];
		return true; //the item has been popped
	}

	/************getTop()***************
	* If the stack is empty then it returns
	* false.
	* If the stack is not empty then it
	* returns true.
	*/
	bool isEmpty() const
	{
		if (size == 0) { return true; }
		return false;
	}


	/************print()***************
	* Prints the contents of the stack
	* false.
	* If the stack is not empty then it
	* returns true.
	*/
	void print() const
	{
		std::cout << "Contents of stack: ";
		for (int i = size-1; i > -1; i--) //while i is greater than or equal to zero it will print to stdout the contents of stack[i]
		{
			std::cout << stack[i] << ' ';
		}
		std::cout << '\n';
	}
	/************chrisExpand()***************
	* The chrisExpand() method enables the
	* user of this class to increase the size
	* of the stack by a size of n.
	* This is used by the chrisPush() method.
	*/
	void chrisExpand(int n) //slow and costly
	{
		capacity += n; //increase the size of the stack by twenty at a time
		T * stack2 = new T[capacity];
		
		for (int i = 0; i < size; i++) // while i is less than size, fill stack2 with the stack1
		{
			stack2[i] = stack[i]; //this is a bit costly..
		}

		delete[] stack; // releases the old stack
		stack = stack2; //assigns the new stack
	}


	/************chrisPush()***************
	* places an object on top of the stack
	* If the stack is full (all of the
	* dynamically allocated memory has been
	* used) then it calls the chrisExpand
	* method.
	* If the ojbect was sucessfully pushed
	* onto the stack then the method
	* returns true.
	*/
	bool chrisPush(const T item) 
	{
		if (size == capacity) { chrisExpand(20); } // if it is full then increase the size of the method by 20 units
		stack[size++] = item; // add the item to the sack then increment the size 
		return true;
	}
};

#endif