#include "GreedySolver.hpp"
#include "../containers/Vector.hpp"

KnapsackSolution GreedySolverDensity::solve(const KnapsackInstance& instance)
{
    const Vector<Item>& items = instance.getItems();
    int n = instance.getItemCount();
    int capacity = instance.getCapacity();

    if (n == 0 || capacity <= 0) return KnapsackSolution();

    Vector<ItemData> temp;
    temp.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        ItemData gi;
        gi.item = items[i];
        gi.originalIndex = i;
        temp.push_back(gi);
    }
    temp.bubbleSort();
    temp.reverse();

    KnapsackSolution solution;
    int remaining = capacity;
    for (int i = 0; i < n; ++i)
    {
        if (temp[i].item.getWeight() <= remaining)
        {
            solution.addItem(static_cast<size_t>(temp[i].originalIndex), temp[i].item.getWeight(), temp[i].item.getValue());
            remaining -= temp[i].item.getWeight();
        }
    }

    return solution;
}

KnapsackSolution GreedySolverValue::solve(const KnapsackInstance& instance)
{
    const Vector<Item>& items = instance.getItems();
    int n = instance.getItemCount();
    int capacity = instance.getCapacity();

    if (n == 0 || capacity <= 0) return KnapsackSolution();

    Vector<ItemData> temp;
    temp.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        ItemData gi;
        gi.item = items[i];
        gi.originalIndex = i;
        temp.push_back(gi);
    }
    temp.bubbleSort();
    temp.reverse();

    KnapsackSolution solution;
    int remaining = capacity;
    for (int i = 0; i < n; ++i)
    {
        if (temp[i].item.getWeight() <= remaining)
        {
            solution.addItem(static_cast<size_t>(temp[i].originalIndex), temp[i].item.getWeight(), temp[i].item.getValue());
            remaining -= temp[i].item.getWeight();
        }
    }

    return solution;
}

KnapsackSolution GreedySolverWeigth::solve(const KnapsackInstance& instance)
{
    const Vector<Item>& items = instance.getItems();
    int n = instance.getItemCount();
    int capacity = instance.getCapacity();

    if (n == 0 || capacity <= 0) return KnapsackSolution();

    Vector<ItemData> temp;
    temp.reserve(n);
    for (int i = 0; i < n; ++i)
    {
        ItemData gi;
        gi.item = items[i];
        gi.originalIndex = i;
        temp.push_back(gi);
    }
    temp.bubbleSort();
    temp.reverse();

    KnapsackSolution solution;
    int remaining = capacity;
    for (int i = 0; i < n; ++i)
    {
        if (temp[i].item.getWeight() <= remaining)
        {
            solution.addItem(static_cast<size_t>(temp[i].originalIndex), temp[i].item.getWeight(), temp[i].item.getValue());
            remaining -= temp[i].item.getWeight();
        }
    }

    return solution;
}