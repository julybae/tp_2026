#ifndef KNAPSACK_SOLUTION_HPP
#define KNAPSACK_SOLUTION_HPP

#include "../containers/Vector.hpp"

class KnapsackSolution
{
public:
    KnapsackSolution();
    KnapsackSolution(KnapsackSolution&& other) noexcept;
    KnapsackSolution& operator=(KnapsackSolution&& other) noexcept;
    void addItem(size_t index, int weight, int value);
    int getTotalValue() const;
    int getTotalWeight() const;
    const Vector<size_t>& getSelectedIndices() const;
    void setTotalValue(int v);
    void setTotalWeight(int w);

private:
    Vector<size_t> selectedIndices_;
    int totalValue_;
    int totalWeight_;
};

#endif