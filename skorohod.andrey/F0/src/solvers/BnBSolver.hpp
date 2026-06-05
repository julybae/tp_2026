#ifndef BNB_SOLVER_HPP
#define BNB_SOLVER_HPP

#include "Solver.hpp"
#include "../containers/PriorityQueue.hpp"
#include "../containers/Vector.hpp"

class BnBSolver : public Solver
{
public:
    KnapsackSolution solve(const KnapsackInstance& instance) override;
    const char* getName() const override { return "Branch and Bound"; }
private:
    struct ItemData
    {
        Item item;
        int originalIndex;
        bool operator>(const ItemData& other) const { return item.getDensity() > other.item.getDensity(); }
        bool operator<(const ItemData& other) const { return item.getDensity() < other.item.getDensity(); }

    };

    struct Node
    {
        int level;
        int weight;
        int value;
        double bound;
        Vector<int> taken;

        bool operator>(const Node& other) const { return bound > other.bound; }
        bool operator>=(const Node& other) const { return bound >= other.bound; }
    };

    Vector<ItemData> sortedItems;
    int capacity;
    int bestValue;
    Vector<int> bestTaken;

    double computeBound(int level, int currentWeight, int currentValue) const;

};

#endif