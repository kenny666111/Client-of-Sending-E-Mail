#pragma once

#include "resource.h"

template <typename T>
struct NODE{
	T data;
	NODE * prev, * next;
	NODE(){prev=next=0;}
};

template <typename T>
class BiCNode{

public:
	int GetLength()
	{return length;}
	NODE<T> * GetHead();
	NODE<T> * GetTail();
	NODE<T> * FindNode(T a);

	bool InsertNode(T a, NODE<T> * b=0);
	bool InsertBefore(T a, NODE<T> * b);

	bool Delete(NODE<T> * a);
	bool ModifyData(T a, NODE<T> * b);

	BiCNode();
	BiCNode(T a[], int n);
private:
	NODE<T> * mhead, * mtail, _mnhead;
	int length;
};

template <typename T>
class Stackp{

public:
	T Pop();
	T GetLast();
	void Push(T & a);

	BiCNode<T> mnode;
};

template <typename T>
class SQueue{

public:
	T DeQueue();
	T GetLast();
	void EnQueue(T & a);

	BiCNode<T> mnode;
};



















template <typename T>
BiCNode<T>::BiCNode()
{
	mhead=mtail=&_mnhead;
	length=0;
	mhead->prev=mhead->next=mhead;
}

template <typename T>
BiCNode<T>::BiCNode(T a[], int n)
{
	mhead=mtail=&_mnhead;
	length=n;
	
	NODE<T> * p=mhead;
	for(int i=0;i<n;i++)
	{
		p->next=new NODE<T>;
		p->next->prev=p;
		p=p->next;
		p->data=a[i];
	}

	p->next=mhead;
	mhead->prev=p;
	mtail=p;
}

template <typename T>
NODE<T> * BiCNode<T>::GetHead()
{
	return mhead;
}

template <typename T>
NODE<T> * BiCNode<T>::GetTail()
{
	return mtail;
}

template <typename T>
bool BiCNode<T>::ModifyData(T a, NODE<T> *b)
{
	for(NODE<T> * p=mhead->next;p!=mhead;p=p->next)
	{
		if(p==b)
		{
			p->data=a;
			return true;
		}
	}
	return false;
}

template <typename T>
bool BiCNode<T>::Delete(NODE<T> *a)
{
	if(!a||length==0)
		return false;
	if(a==mtail)
		mtail=mtail->prev;
	a->next->prev=a->prev;
	a->prev->next=a->next;
	delete a;
	length--;
	return true;
}

template <typename T>
NODE<T> * BiCNode<T>::FindNode(T a)
{
	for(NODE<T> * p=mhead->next;p!=mhead;p=p->next)
	{
		if(p->data==a)
			return p;
	}
	return NULL;
}

template <typename T>
bool BiCNode<T>::InsertBefore(T a, NODE<T> * b)
{
	if(b==mhead)
	{
		mtail->next=new NODE<T>;
		mtail->next->prev=mtail;
		mtail=mtail->next;
		mtail->data=a;
		mtail->next=mhead;
		mhead->prev=mtail;
	}
	else
	{
		NODE<T> * p=b->prev;
		b->prev=new NODE<T>;
		b->prev->next=b;
		b=b->prev;
		b->data=a;
		b->prev=p;
		p->next=b;
	}
	length++;
	return true;
}

template <typename T>
bool BiCNode<T>::InsertNode(T a, NODE<T> * b)
{
	if(b==0)
	{
		this->InsertBefore(a,mhead);
	}
	else
	{
		this->InsertBefore(a,b->next);
	}
	return true;
}

template <typename T>
T Stackp<T>::Pop()
{
	if(mnode.GetLength()==0)
		throw -1;
	T data=mnode.GetTail()->data;
	mnode.Delete(mnode.GetTail());
	return data;
}

template <typename T>
T Stackp<T>::GetLast()
{
	if(mnode.GetLength()==0)
		throw -1;
	T data=mnode.GetTail()->data;
	return data;
}

template <typename T>
void Stackp<T>::Push(T &a)
{
	mnode.InsertNode(a);
}

template <typename T>
T SQueue<T>::DeQueue()
{
	if(mnode.GetLength()==0)
		throw -1;
	T data=mnode.GetHead()->next->data;
	mnode.Delete(mnode.GetHead()->next);
	return data;
}

template <typename T>
T SQueue<T>::GetLast()
{
	if(mnode.GetLength()==0)
		throw -1;
	T data=mnode.GetHead()->next->data;
	return data;
}

template <typename T>
void SQueue<T>::EnQueue(T &a)
{
	mnode.InsertNode(a);
}