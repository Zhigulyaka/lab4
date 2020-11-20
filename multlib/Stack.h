#pragma once
#include <iostream>
#ifndef _STACK_
#define _STACK_



using namespace std;

template <class T1>
class Stack
{
protected:
    int length;
    T1* x;
    int vs;
public:

    Stack();
    Stack(int _size);
    Stack(Stack<T1>& other);
    ~Stack();
    void push(T1 elem);
    void set(int _vs, int _size, T1* _x);
    T1 pull();
    bool IsFull();
    bool IsEmpty();
    Stack<T1>& operator =(Stack<T1>& other);
    template <class T1>
    friend ostream& operator<< (ostream& ostr, const Stack<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, Stack<T1>& A);
    T1 EvMax();
    Stack EvCopy(Stack<T1>& other);
    int GetLength();
    int GetVS();
    void Resize(int size);
};

template <class T1>
ostream& operator<< (ostream& ostr, const Stack<T1>& A) {
    for (int i = 0; i < A.vs; i++) {
        ostr << A.x[i] << endl;
    }
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, Stack<T1>& A)
{
    int count;
    istr >> count;
    for (int i = 0; i < count; i++)
    {
        T1 d;
        istr >> d;
        A.push(d);
    }
    return istr;
}

template <class T1>
Stack<T1>::Stack()
{
    vs = -1;
    length = 1;
    x = new T1[1];

}
template <class T1>
Stack<T1>::Stack(int _size)
{
    if (_size < 0)
        throw logic_error("invalid_length");
    this->length = _size;
    x = new T1[length];

    this->vs = -1;
}

template <class T1>
Stack<T1>::Stack(Stack<T1>& other)
{
    length = other.length;
    vs = other.vs;
    x = new T1[length];
    for (int i = 0; i <= vs; i++)
        x[i] = other.x[i];
}
template <class T1>
Stack<T1>::~Stack()
{
    if (this != 0)
    {
        length = 0;
        vs = 0;
        delete[] x;
        x = 0;
    }
}

template<class T1>
inline void Stack<T1>::push(T1 elem)
{

    if ((*this).IsFull())
        throw logic_error("stack_is_full");
    vs++;
    x[vs] = elem;
}

template<class T1>
inline void Stack<T1>::set(int _vs, int _size, T1* _x)
{
    length = _size;
    vs = _vs;

    delete[] (*this).x;
    (*this).x = _x;
}

template<class T1>
inline T1 Stack<T1>::pull()
{

    if ((*this).IsEmpty())
        throw logic_error("stack_is_empty");
    T1 elem = x[vs];
    vs--;
    return elem;
}

template<class T1>
inline bool Stack<T1>::IsFull()
{
    return ((vs + 1) == length);
}

template<class T1>
inline bool Stack<T1>::IsEmpty()
{
    return (vs == -1);
}

template <class T1>
Stack<T1>& Stack<T1>::operator =(Stack<T1>& other)
{
    if (this == &other)
        return *this;
    vs = other.vs;
    length = other.length;
    delete[] x;
    x = new T1[length];
    for (int i = 0; i <= vs; i++)
        x[i] = other.x[i];
    return *this;
}

template<class T1>
inline T1 Stack<T1>::EvMax()
{
    T1 max = 1;
    int j = 0;
    int _vs = (*this).vs;
    for (int i = 0; i <= vs; i++)
    {
        j = pull();
        if ((max < j) && ((j % 2) == 0))
            max = j;
    }
    (*this).vs = _vs;
    return max;

}

template<class T1>
inline Stack<T1> Stack<T1>::EvCopy(Stack<T1>& other)
{
    int j = 0;
    int _vs = other.vs;
    for (int i = 0; i <= _vs; i++)
        if ((other.pull() % 2) == 0)
            j++;
    other.vs = _vs;
    this->x = new T1[j];
    this->length = j;
    this->vs = -1;
    for (int i = 0; i <= _vs; i++)
    {
        j = other.pull();
        if ((j % 2) == 0)
            this->push(j);
    }
    other.vs = _vs;
    return (*this);
}

template <class T1>
int Stack<T1>::GetLength()
{
    return length;
}

template<class T1>
inline int Stack<T1>::GetVS()
{
    return vs;
}

template<class T1>
inline void Stack<T1>::Resize(int size)
{
    if (size < length)
    {
        Stack temp(*this);
        temp.vs = size - 1;
        (*this).x = new T1[size];
        (*this).length = size;
        (*this).vs = -1;
        for (int i = 0; i < size; i++)
            (*this).push(temp.pull());
    }
    if (size > length)
    {
        Stack temp(*this);
        (*this).x = new T1[size];
        (*this).length = size;
        (*this).vs = -1;
        for (int i = 0; i < temp.length; i++)
            (*this).push(temp.pull());
    }
}
#endif