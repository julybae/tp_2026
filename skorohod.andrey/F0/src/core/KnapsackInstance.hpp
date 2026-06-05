#ifndef KNAPSACK_INSTANCE_HPP
#define KNAPSACK_INSTANCE_HPP

#include "Item.hpp"
#include "../containers/Vector.hpp"

class KnapsackInstance
{
public:
    KnapsackInstance(size_t cap = 0);
    void addItem(const Item&);
    const Vector<Item>& getItems() const;
    int getCapacity() const;
    size_t getItemCount() const;

private:
    Vector<Item> items_;
    int capacity_;
};

#endif
