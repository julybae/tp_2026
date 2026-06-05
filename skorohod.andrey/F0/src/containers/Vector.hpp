#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class Vector
{
    public:
    Vector(){}
    Vector(std::size_t size);
    Vector(std::size_t size, T&& value);
    Vector(const Vector& other);
    Vector(Vector&& other);
    ~Vector(){} 



    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return !size_; }
    


    void swap(Vector & other);
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other);



    T& operator[](size_t index) { return data_[index]; }
    const T& operator[](size_t index) const { return data_[index]; }
    T& at(size_t index);
    const T& at(size_t index) const;
    T& front() { return data_[0]; }
    T& back() { return data_[size_ - 1]; }



    void push_back(const T& value);
    void push_back(T&& value);
    void insert(std::size_t index, const T& value);
    void insert(std::size_t index, T&& value);



    void erase(std::size_t index);
    void erase(std::size_t first, std::size_t last);
    void pop_back();
    void clear();



    void resize(std::size_t new_size);
    void resize(std::size_t new_size, const T& value);
    void reserve(std::size_t new_cap);
    void shrink_to_fit();



    bool operator==(const Vector& other) const;
    bool operator!=(const Vector& other) const { return !(*this == other); }
    bool operator<(const Vector& other) const;
    bool operator>(const Vector& other) const { return (!(*this < other) && *this != other); }
    bool operator>=(const Vector& other) const { return ((*this > other) || *this == other); }
    bool operator<=(const Vector& other) const { return ((*this < other) || *this == other); }


    void quickSort();
    void bubbleSort();
    void reverse();

    private:
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
    std::unique_ptr<T[]> data_ { nullptr };

    void quickSortRecursive(std::size_t left, std::size_t right);
    std::size_t partition(std::size_t left, std::size_t right);

};


template <typename T>
Vector<T>::Vector(std::size_t size):
size_(size),
capacity_(size),
data_(new T[capacity_])
{}

template <typename T>
Vector<T>::Vector(std::size_t size, T&& value):
size_(size),
capacity_(size),
data_(new T[capacity_])
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = value;
    }
}

template <typename T>
Vector<T>::Vector(const Vector& other):
size_(other.size_),
capacity_(other.capacity_),
data_(new T[capacity_])
{
    for (std::size_t i = 0; i < size_; ++i)
    {
        data_[i] = other.data_[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector&& other):
size_(other.size_),
capacity_(other.capacity_),
data_(std::move(other.data_))
{
    other.size_ = 0;
    other.capacity_ = 0;
}

template <typename T>
void Vector<T>::swap(Vector & other)
{

    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other)
    {
        Vector buff(other);
        this->swap(buff);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other)
{
    if (this != &other)
    {
        size_ = other.size_;
        capacity_ = other.capacity_;
        data_ = std::move(other.data_);
        other.size_ = 0;
        other.capacity_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}

template <typename T>
T& Vector<T>::at(size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("out of range");
    }

    return data_[index];
}

template <typename T>
const T& Vector<T>::at(size_t index) const
{
    if (index >= size_)
    {
        throw std::out_of_range("out of range");
    }

    return data_[index];
}

template <typename T>
void Vector<T>::push_back(const T& value)
{
    if (size_ == capacity_)
    {
        if (!capacity_) 
        {
            ++capacity_;
        }
        else
        {
            capacity_ *= 2;
        }
        
        std::unique_ptr<T[]> new_data(new T [capacity_]);

        for (std::size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }

        new_data[size_] = value;
        data_ = std::move(new_data);
        ++size_;
    }
    else
    {
        data_[size_] = value;
        ++size_;
    }
    
}

template <typename T>
void Vector<T>::push_back(T&& value)
{
    if (size_ == capacity_)
    {
        if (!capacity_) 
        {
            ++capacity_;
        }
        else
        {
            capacity_ *= 2;
        }
        
        std::unique_ptr<T[]> new_data(new T [capacity_]);

        for (std::size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }

        new_data[size_] = std::move(value);
        data_ = std::move(new_data);
        ++size_;
    }
    else
    {
        data_[size_] = std::move(value);
        ++size_;
    }
}

template <typename T>
void Vector<T>::insert(std::size_t index, const T& value)
{
    if (index > size_) throw std::out_of_range("insert out of range");
    if (size_ == capacity_)
    {
        if (!capacity_) capacity_ = 1;
        else capacity_ *= 2;
        std::unique_ptr<T[]> new_data(new T[capacity_]);
        for (std::size_t i = 0; i < index; ++i)
        {
            new_data[i] = data_[i];
        }
        new_data[index] = value;
        for (std::size_t i = index + 1; i <= size_; ++i)
        {
            new_data[i] = data_[i - 1];
        }
        data_ = std::move(new_data);
        ++size_;
    }
    else
    {
        for (std::size_t i = size_; i > index; --i)
        {
            data_[i] = data_[i - 1];
        }
        data_[index] = value;
        ++size_;
    }
}

template <typename T>
void Vector<T>::insert(std::size_t index, T&& value)
{
    if (index > size_) throw std::out_of_range("insert out of range");
    if (size_ == capacity_)
    {
        if (!capacity_) capacity_ = 1;
        else capacity_ *= 2;
        std::unique_ptr<T[]> new_data(new T[capacity_]);
        for (std::size_t i = 0; i < index; ++i)
        {    
            new_data[i] = std::move(data_[i]);
        }
        new_data[index] = std::move(value);
        for (std::size_t i = index + 1; i <= size_; ++i)
        {
            new_data[i] = std::move(data_[i - 1]);
        }
        data_ = std::move(new_data);
        ++size_;
    }
    else
    {
        for (std::size_t i = size_; i > index; --i)
        {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[index] = std::move(value);
        ++size_;
    }
}

template <typename T>
void Vector<T>::erase(std::size_t index)
{
    if (index >= size_)
    {
        throw std::out_of_range("out of range");
    } 

    for (std::size_t i = index; i < size_ - 1; ++i)
    {
        data_[i] = data_[i + 1];       
    }

    --size_;
}

template <typename T>
void Vector<T>::erase(std::size_t first, std::size_t last)
{
    if (first >= size_ || last >= size_)
    {
        throw std::out_of_range("out of range");
    } 

    std::size_t delta = last - first + 1;
    std::size_t new_size = size_ - delta;

    for (std::size_t i = first; i < new_size; ++i)
    {
        data_[i] = data_[i + delta];       
    }

    size_ = new_size;
}

template <typename T>
void Vector<T>::pop_back()
{
    if(!empty()) --size_;
}

template <typename T>
void Vector<T>::clear()
{
    size_ = 0;
    capacity_ = 0;
    data_ = nullptr;
}

template <typename T>
void Vector<T>::resize(std::size_t new_size)
{
    if (new_size <= capacity_)
    {
        size_ = new_size;        
    }
    else
    {
        std::unique_ptr<T[]> new_data(new T [new_size]);
        
        for (std::size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }
        
        size_ = new_size;
        capacity_ = new_size;
        data_ = std::move(new_data);
    }
}

template <typename T>
void Vector<T>::resize(std::size_t new_size, const T& value)
{
    if (new_size <= capacity_)
    {
        size_ = new_size;        
    }
    else
    {
        std::unique_ptr<T[]> new_data(new T [new_size]);
        
        for (std::size_t i = 0; i < size_; ++i)
        {
            new_data[i] = data_[i];
        }

        for (std::size_t i = size_; i < new_size; ++i)
        {
            new_data[i] = value;
        }
        
        size_ = new_size;
        capacity_ = new_size;
        data_ = std::move(new_data);
    }
}

template <typename T>
void Vector<T>::reserve(std::size_t new_cap)
{
    if (new_cap <= capacity_) return;
    std::unique_ptr<T[]> new_data(new T[new_cap]);
    for (size_t i = 0; i < size_; ++i) new_data[i] = data_[i];
    data_ = std::move(new_data);
    capacity_ = new_cap;
}

template <typename T>
void Vector<T>::shrink_to_fit()
{
    std::unique_ptr<T[]> new_data(new T [size_]);
    for (std::size_t i = 0; i < size_; ++i)
    {
        new_data[i] = data_[i];
    }
    capacity_ = size_;
    data_ = std::move(new_data);
}

template <typename T>
bool Vector<T>::operator==(const Vector& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }

    for (std::size_t i = 0; i < size_; ++i)
    {
        if (data_[i] != other.data_[i])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
bool Vector<T>::operator<(const Vector& other) const
{
    for (std::size_t i = 0; i < size_ && i < other.size_ ; ++i)
    {
        if (data_[i] != other.data_[i])
        {
            return data_[i] < other.data_[i];
        }
    }
    return size_ < other.size_;
}

template <typename T>
void Vector<T>::bubbleSort()
{
    bool swapped = true;
    while(swapped)
    {
        swapped = false;
        for (std::size_t i = 0; i < size_ - 1; ++i)
        {
            if (data_[i] > data_[i + 1])
            {
                std::swap(data_[i], data_[i + 1]);
                swapped = true;
            }
        }
    }
}

template <typename T>
void Vector<T>::quickSort()
{
    if (size_ <= 1)
        return;
    quickSortRecursive(0, size_ - 1);
}

template <typename T>
void Vector<T>::quickSortRecursive(size_t left, size_t right)
{
    if (left >= right) return;
    size_t pivotIdx = partition(left, right);
    if (pivotIdx > left) quickSortRecursive(left, pivotIdx);
    if (pivotIdx + 1 < right) quickSortRecursive(pivotIdx + 1, right);
}

template <typename T>
size_t Vector<T>::partition(size_t left, size_t right)
{
    T pivot = data_[(left + right) / 2];
    size_t i = left;
    size_t j = right;
    while (true)
    {
        while (i < right && data_[i] < pivot) ++i;
        while (j > left && data_[j] > pivot) --j;
        std::swap(data_[i], data_[j]);
        ++i;
        --j;
    }
    return j;
}

template <typename T>
void Vector<T>::reverse()
{
    for (std::size_t i = 0; i < size_ / 2; ++i)
    {
        std::swap(data_[i], data_[size_ - 1 - i]);
    }
}

#endif
