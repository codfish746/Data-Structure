﻿#pragma once
#include<iostream>
using namespace std;
//单向链表
template<typename T>
struct DListNode {
	T date;
	DListNode* RLink;
	DListNode* LLink;
	DListNode(DListNode<T> *l=0,DListNode<T>* r=0) {
		LLink = l;
		RLink = r;
	}
	DListNode(T t, DListNode<T> *l, DListNode<T>* r) {
		date = t;
		LLink = l;
		RLink = r;
	}
};


template<typename T>
class DoublyList
{
public:
	DoublyList();
	virtual ~DoublyList();
	bool prepend(T t);		//在头上插入
	bool append(T t);		//在尾部追加
	void makeEmpty();						//清空链表，保存头节点

	DoublyList<T>& operator<<(T t);
	int getSize();

	DListNode<T>* locate(int index);
	DListNode<T>* getFirst();
	DListNode<T>* getLast();
	void output(bool tof=true);
protected:
	DListNode<T>* first;
	DListNode<T>* last;
	int size;
};

template<typename T>
inline DoublyList<T>::DoublyList()
{
	first = new DListNode<T>;
	last = first;
	size = 0;
}

template<typename T>
inline DoublyList<T>::~DoublyList()
{
	makeEmpty();
	delete first;
	first = NULL;
}

template<typename T>
inline bool DoublyList<T>::prepend(T t)
{
	DListNode<T>* newNode = new DListNode<T>(t, first, first->RLink);
	if (!newNode->RLink) {
		last = newNode;
	}
	else
	{
		first->RLink = newNode;
		newNode->RLink->LLink = newNode;
	}
	size++;
	return true;
}

template<typename T>
inline bool DoublyList<T>::append(T t)
{
	DListNode<T>* newNode = new DListNode<T>(t, last, NULL);
	last->RLink = newNode;
	last = last->RLink;
	size++;
	return false;
}

template<typename T>
inline void DoublyList<T>::makeEmpty()
{
	
	while (first->RLink)
	{
		DListNode<T>* item = first->RLink;
		first->RLink = item->RLink;
		delete item;
	}
	first->RLink = NULL;
	size = 0;
	last = first;
}

template<typename T>
inline DoublyList<T>& DoublyList<T>::operator<<(T t)
{
	// TODO: 在此处插入 return 语句
	// 
	this->append(t);
	return *this;
}

template<typename T>
inline int DoublyList<T>::getSize()
{
	return size;
}

template<typename T>
inline DListNode<T>* DoublyList<T>::locate(int index)
{
	if (index<0 || index>size - 1) {
		throw "exception";
	}
	DListNode<T>* node;
	if (index < size / 2) {
		node = first->RLink;
		for (int i = 0; i < index; i++)
		{
			node = node->RLink;
		}
	}
	else
	{
		node = last;
		for (int i = size-1; i > index; i--)
		{
			node = node->LLink;
		}
	}
	return node;
}

template<typename T>
inline DListNode<T>* DoublyList<T>::getFirst()
{
	return first->RLink;
}

template<typename T>
inline DListNode<T>* DoublyList<T>::getLast()
{
	return last;
}

template<typename T>
inline void DoublyList<T>::output(bool tof)
{
	cout << "这个链表，长度为：" << size << endl;
	cout << "头节点的数据为： " << first->RLink->date << endl;
	cout << "尾节点的数据为： " << last->date << endl;
	cout << "各个节点的数据依次遍历为: ";
	DListNode<T>* node;
	if (tof) {
		node = first->RLink;
		while (node)
		{
			cout << node->date;
			node = node->RLink;
		}
	}
	else
	{
		node = last;
		while (node!=first)
		{
			cout << node->date;
			node = node->LLink;
		}
	}
}
