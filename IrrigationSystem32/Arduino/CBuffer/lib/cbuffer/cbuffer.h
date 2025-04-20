#pragma once

template <typename T>
struct Result {
    bool success;  // Успех или ошибка
    T value;       // Значение элемента
};

template <typename T>
class CBuffer
{
    public:
    CBuffer(const unsigned int Capacity);
    ~CBuffer();
    unsigned int Capacity();
    unsigned int Size();
    void Push(const T item); 
    void Clear();
    T operator[](const unsigned int index); 
    bool Empty();

    private:
    unsigned int _capacity;
    unsigned int _size;
    unsigned int _head;
    T* _buffer;
};

template <typename T>
inline CBuffer<T>::CBuffer(const unsigned int Capacity)
{
    _capacity = Capacity;
    _size = 0;
    _head = 0;
    //_tail = 0;
    _buffer = new T[_capacity];
}

template <typename T>
inline CBuffer<T>::~CBuffer()
{
    delete[] _buffer;
}

template <typename T>
inline unsigned int CBuffer<T>::Size()
{
    return _size;
}

template <typename T>
inline unsigned int CBuffer<T>::Capacity()
{
    return _capacity;
}

template <typename T>
inline void CBuffer<T>::Push(const T item)
{
    if (Empty()) 
    {
        //_tail = 0;
        _size = 1;
        _head = 0;
        _buffer[_head] = item;
    }
    else
    {
        _head = ++_head % _capacity;
        _buffer[_head] = item;
        _size = _size < _capacity ? ++_size : _capacity;
    }
    return;
}

template <typename T>
inline void CBuffer<T>::Clear()
{
    _size = 0;
    _head = 0;
}

template <typename T>
inline T CBuffer<T>::operator[](const unsigned int index)
{
    return _buffer[(_head-index)%_capacity];
}

template <typename T>
inline bool CBuffer<T>::Empty()
{
    return Size() == 0;
}
