#pragma once
#ifndef _MULTYSTACK_
#define _MULTYSTACK_

#include <iostream>
#include <math.h>
#include "Stack.h"
using namespace std;

template <class T1>
class MultyStack: public Stack<T1>
{
protected:
    T1** oldInd;
    int length;
    T1* x;
    int count;
    T1** newInd;
    Stack <T1>* stacks;
public:

    MultyStack();
    MultyStack(int _size, int _count);
    MultyStack(MultyStack<T1>& other);
    ~MultyStack();
    void push(T1 elem, int i);
    T1 pull(int i);
    bool IsFull(int i);
    bool IsEmpty(int i);
    MultyStack<T1>& operator =(MultyStack<T1>& other);
    template <class T1>
    friend ostream& operator<< (ostream& ostr, const MultyStack<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, MultyStack<T1>& A);
    int GetLength();
    int GetCount();
    void Repack(int ind);
    void RelocationRight(int* _sizes, int ind);
    void RelocationLeft(int* _sizes, int ind);
};

template <class T1>
ostream& operator<< (ostream& ostr, const MultyStack<T1>& A) {
    for (int i = 0; i < A.count; i++) {
        ostr << A.stacks[i] << endl;
    }
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, MultyStack<T1>& A)
{
    int count=0;
    istr >> count;
    int size = 0;
    istr >> size;
    A.Resize(size, count);
    for (int i = 0; i < count; i++)
    {
        istr >> A.stacks[i];
    }
    return istr;
}

template <class T1>
MultyStack<T1>::MultyStack()
{
    vs = -1;
    length = 1;
    x = new T1[1];
    stacks= new Stack<T1>[1];
    
}
template <class T1>
MultyStack<T1>::MultyStack(int _size, int _count)
{
    if ((_size <=0) && (_count <=0))
        throw logic_error("invalid_length");
    this->length = _size;
    x = new T1[length];
    this->count = _count;
    int* sizes = new int[count];

    int ost = int(floor (double(_size) / double(_count)));
    
    for (int i = 0; i < (count-1); i++)
    {
        sizes[i] = ost;
    }

    sizes[_count - 1] = _size - (ost * (_count-1));
    stacks = new Stack<T1>[count];
    T1** oldInd = new T1 * [count];
    int k = 0;
    for (int i = 0; i < count; i++)
    {
        stacks[i].set(-1,sizes[i],&(x[k]));
        oldInd[i] = &(x[k]);
        k += sizes[i];
    }
}

template <class T1>
MultyStack<T1>::MultyStack(MultyStack<T1>& other)
{
    length = other.length;
    count = other.count;
    x = new T1[length];
    T1** oldInd = new T1 * [count];
    for (int i = 0; i < length; i++)
        x[i] = other.x[i];
    stacks = new Stack[count];
    int* sizes = new int[count];
    int k = 0;
    for (int i = 0; i < count; i++)
    {
        sizes[i] = stacks[i].GetLength();
        stacks[i] = other.stacks[i];
        oldInd[i] = &(x[k]);
        k += sizes[i];

    }
}
template <class T1>
MultyStack<T1>::~MultyStack()
{
    if (this != 0)
    {
        length = 0;
        count = 0;
        delete[] x;
        if (stacks!=0)
        delete[] stacks;
        x = 0;
    }
}

template<class T1>
inline void MultyStack<T1>::push(T1 elem, int i)
{

    if ((i < 0) && (i>=count))
        throw logic_error("invalid_index");
    if (stacks[i].IsFull())
        (*this).Repack(i);
    stacks[i].push(elem);
}

template<class T1>
inline T1 MultyStack<T1>::pull(int i)
{
    if ((i < 0) && (i >= count))
        throw logic_error("invalid_index");
    if (stacks[i].IsEmpty())
        throw logic_error("stack_is_empty");
    T1 elem=stacks[i].pull();
    return   elem;
}

template<class T1>
inline bool MultyStack<T1>::IsFull(int i)
{
    if ((i < 0) && (i >= count))
        throw logic_error("invalid_index");
    return stacks[i].IsFull();
}

template<class T1>
inline bool MultyStack<T1>::IsEmpty(int i)
{
    if ((i < 0) && (i >= count))
        throw logic_error("invalid_index");
    return stacks[i].IsEmpty();
}

template <class T1>
MultyStack<T1>& MultyStack<T1>::operator =(MultyStack<T1>& other)
{
    if (this == &other)
        return *this;
    count = other.count;
    length = other.length;
    delete[] x;
    delete[] stacks;
    x = new T1[length];
    for (int i = 0; i < length; i++)
        x[i] = other.x[i];
    stacks = new Stack<T1>[count];
    for (int i = 0; i < count; i++)
        stacks[i] = other.stacks[i];
    return *this;
}

template <class T1>
int MultyStack<T1>::GetLength()
{
    return length;
}
template<class T1>
inline int MultyStack<T1>::GetCount()
{
    return count;
}
template<class T1>
inline void MultyStack<T1>::Repack(int ind)
{
    int freeSize = 0;
    for (int i = 0; i < count; i++)
    {

        freeSize += stacks[i].GetLength() - 1 - stacks[i].GetVS();
    }
    if (freeSize==0)
        throw logic_error("multystack_is_full");
    int* sizes = new int[count];
    int ost = int(floor(double(freeSize / count)));

    for (int i = 0; i < count; i++)
    {
        if(i!=ind)
        sizes[i] = stacks[i].GetVS()+1+ost;
    }
  
    sizes[ind] = stacks[ind].GetVS()+length - (ost * (count - 1));
    newInd = new T1 * [count];
    int k = 0;
    for (int i = 0; i < count; i++)
    {
        newInd[i] = &(x[k]);
        k = k + sizes[i];
    }
    for (int i = 0; i < count; i++)
    {
        if (newInd[i] == oldInd[i])
            stacks[i].set(stacks[i].GetVS(), sizes[i], newInd[i]);

        if (newInd[i] < oldInd[i])
            RelocationLeft(sizes, i);
   
        if (newInd[i] > oldInd[i])
            RelocationRight(sizes, i);
    }
    T1** temp = oldInd;
    oldInd = newInd;
    delete[] temp;
    delete[] sizes;

}

template<class T1>
inline void MultyStack<T1>::RelocationRight(int* _sizes, int ind)
{
    int k = 0;
    for (k = ind; k < count; k++)
        if (newInd[k] > oldInd[k])
            continue;
        else
            break;
    k--;
    for (int s = k; s >= ind; s--)
    {
    for (int j = stacks[s].GetVS(); j > -1; j--)
        newInd[s][j] = oldInd[s][j];
    stacks[s].set(stacks[s].GetVS(), _sizes[s], newInd[s]);
    }

}

template<class T1>
inline void MultyStack<T1>::RelocationLeft(int* _sizes, int ind)
{
    for (int j = 0; j <= stacks[ind].GetVS(); j++)
        newInd[ind][j] = oldInd[ind][j];
    stacks[ind].set(stacks[ind].GetVS(), _sizes[ind], newInd[ind]);
}

#endif
