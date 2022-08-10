//
// Created by Sevent on 2022/8/9.
//

#ifndef ALGORITHM_VECTOR_H
#define ALGORITHM_VECTOR_H
#include <iostream>
template <typename T>
class Vector
{
public:
public:
    Vector()
    {
        ReAlloc(2);
    }

    void PushBack(const T& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(m_Capacity + m_Capacity / 2);

        m_Data[m_Size] = value;
        m_Size++;
    }

    void PushBack(T&& value)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(m_Capacity + m_Capacity / 2);

        m_Data[m_Size] = std::move(value);
        m_Size++;
    }

    const T& operator[] (size_t index) const
    {
        return m_Data[index];
    }

    T& operator[] (size_t index)
    {
        return m_Data[index];
    }

    size_t Size()
    {
        return m_Size;
    }

    template<class... Args>
    T& EmplaceBack(Args&&... args)
    {
        if (m_Size >= m_Capacity)
            ReAlloc(m_Capacity + m_Capacity / 2);

        new(&m_Data[m_Size]) T(std::forward<Args>(args)...);
//        m_Data[m_Size] = T(std::forward<Args>(args)...);
        return m_Data[m_Size++];
    }

    void PopBack()
    {
        if (m_Size > 0)
        {
            m_Size--;
            m_Data[m_Size].~T();
        }
    }

    void Clear()
    {
        for (int i = 0; i < m_Size; ++i) {
            m_Data[i].~T();
        }
        m_Size = 0;
    }

    ~Vector()
    {
        Clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T)) ;
    }

private:
    void ReAlloc(size_t newCapacity)
    {
        T* newBlock = (T*)::operator new(newCapacity * sizeof(T));
        m_Size = m_Size>newCapacity? newCapacity:m_Size;
        for (int i = 0; i < m_Size; ++i)
            newBlock[i] =  std::move(m_Data[i]);

        for (int i = 0; i < m_Size; ++i) {
            m_Data[i].~T();
        }

        ::operator delete(m_Data, m_Capacity * sizeof(T)) ;
        m_Data = newBlock;
        m_Capacity = newCapacity;
    }
    T* m_Data = nullptr;
    size_t m_Size  = 0;
    size_t m_Capacity = 0;
};

template<typename T>
void PrintVector(Vector<T>& vector)
{
    for (int i = 0; i < vector.Size(); ++i) {
        std::cout<<vector[i]<<std::endl;

    }
}



#endif //ALGORITHM_VECTOR_H
