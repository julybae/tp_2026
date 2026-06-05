#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include "Vector.hpp"
#include <stdexcept>

template <typename T>
class PriorityQueue
{
public:
    PriorityQueue();
    ~PriorityQueue() = default;

    void push(const T& value);
    void push(T&& value);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    size_t size() const;
    void clear();

private:
    Vector<T> data_;

    void siftUp(size_t index);
    void siftDown(size_t index);
};

template <typename T>
PriorityQueue<T>::PriorityQueue():
data_()
{}

template <typename T>
void PriorityQueue<T>::push(const T& value)
{
    data_.push_back(value);
    siftUp(data_.size() - 1);
}

template <typename T>
void PriorityQueue<T>::push(T&& value)
{
    data_.push_back(std::move(value));
    siftUp(data_.size() - 1);
}

template <typename T>
void PriorityQueue<T>::pop()
{
    if (empty()) throw std::out_of_range("Empty queue");

    data_[0] = data_[data_.size() - 1];
    data_.pop_back();
    if (!empty()) siftDown(0);
}

template <typename T>
T& PriorityQueue<T>::top()
{
    if (empty()) throw std::out_of_range("Empty queue");
    return data_[0];
}

template <typename T>
const T& PriorityQueue<T>::top() const
{
    if (empty()) throw std::out_of_range("Empty queue");
    return data_[0];
}

template <typename T>
bool PriorityQueue<T>::empty() const
{
    return data_.empty();
}

template <typename T>
size_t PriorityQueue<T>::size() const
{
    return data_.size();
}

template <typename T>
void PriorityQueue<T>::clear()
{
    data_.clear();
}

template <typename T>
void PriorityQueue<T>::siftUp(size_t index)
{
    while (index > 0)
    {
        size_t parent = (index - 1) / 2;
        if (data_[parent] >= data_[index]) break;
        T temp = data_[parent];
        data_[parent] = data_[index];
        data_[index] = temp;
        index = parent;
    }
}

template <typename T>
void PriorityQueue<T>::siftDown(size_t index)
{
    while (true)
    {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t largest = index;
        if (left < data_.size() && data_[left] > data_[largest]) largest = left;
        if (right < data_.size() && data_[right] > data_[largest]) largest = right;
        if (largest == index) break;
        T temp = data_[index];
        data_[index] = data_[largest];
        data_[largest] = temp;
        index = largest;
    }
}
#endif
