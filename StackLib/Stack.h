#pragma once

#include <iostream>

using namespace std;

template <class T>
class TStack
{
protected:
  int size; 
  T* data; 
  int top; 
  bool flag; 
public:
  TStack(int _size = 1, bool _flag = true);
  TStack(const TStack<T>& _v); 
  ~TStack();

  TStack<T>& operator =(const TStack<T>& _v); 

  void Put(T d);
  T Get();
  void SetData(T* _data, int _size, int _top);
  void Resize(int _size = 1);

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TStack<T1>& A);
  template <class T1>
  friend istream& operator >> (istream& istr, TStack<T1>& A);

  int IsEmpty() const; 
  int IsFull() const; 
  int GetSize();
  int GetCount(); 
};

template <class T1>
ostream& operator<< (ostream& ostr, const TStack<T1>& A) {
  for (int i = 0; i < A.top; i++) {
    ostr << A.data[i] << endl;
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TStack<T1>& A) {
  int count;
  istr >> count;
  for (int i = 0; i < count; i++)
  {
    T1 d;
    istr >> d;
    A.Put(d);
  }
  return istr;
}

template<class T>
TStack<T>::TStack(int _size, bool _flag)
{
  if (_size > 0)
  {
    this->size = _size;
    this->flag = _flag;
    if (flag) 
    {
      data = new T[size];
      for (int i = 0; i < size; i++)
        data[i] = 0;
    }
    this->top = 0;
  }
  else
    throw "negative size";
}

template <class T>
TStack<T>::TStack(const TStack<T>& _v)
{
  size = _v.size;
  top = _v.top;
  flag = _v.flag;
  if (flag)
  {
    data = new T[size];
    for (int i = 0; i < size; i++)
      data[i] = _v.data[i];
  }
  else
  {
    data = _v.data;
  }
}

template <class T>
TStack<T>::~TStack()
{
  size = 0;
  if (flag)
  {	
    if (data != nullptr)
    {
      delete[] data;
      data = 0;
    }
    else
      throw - 1;
  }
}

template <class T>
TStack<T>& TStack<T>::operator =(const TStack<T>& _v)
{
  if (this == &_v)
    return *this;
  size = _v.size;
  flag = _v.flag;
  if (flag)
  {
    delete[] data;
    data = new T[size];
    for (int i = 0; i < size; i++)
      data[i] = _v.data[i];
  }
  else
  {
    data = _v.data;
  }
  top = _v.top;
  return *this;
}

template<class T>
void TStack<T>::Put(T d)
{
  if (top >= size)
    throw "stack overflow";

  data[top] = d;
  top++;
}

template<class T>
T TStack<T>::Get()
{
  if (top == 0)
    throw "stack is empty";
  T d = data[top - 1];
  top--;
  return d;
}

template<class T>
void TStack<T>::SetData(T* _data, int _size, int _top)
{
  if (flag)
  {
    if (data != nullptr)
      delete[] data;
  }
  size = _size;
  flag = false;
  data = _data;
  top = _top;
}

template<class T>
void TStack<T>::Resize(int _size)
{
  if (data == nullptr)
  {
    if (_size > size)
      size = _size + 1;
    data = new T[size];
    if (data == nullptr)
      throw - 1;
  }
  else if ((top + _size) > size)
  {
    T* temp = new T[_size];
    if (temp == nullptr)
      throw - 1;
    for (int i = 0; i < this->GetCount(); ++i)
      temp[i] = this->Get();

    delete[] data;
    data = temp;
    size = _size;
  }
}

template<class T>
int TStack<T>::IsEmpty() const
{
  return (top == 0);
}

template<class T>
int TStack<T>::IsFull() const
{
  return (size == top);
}

template <class T>
int TStack<T>::GetSize()
{
  return size;
}

template<class T>
int TStack<T>::GetCount()
{
  return top;
}