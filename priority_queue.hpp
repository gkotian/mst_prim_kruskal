#pragma once

#include <vector>
#include <algorithm>

template <class T, class COMP>
class PriorityQueue
{
private:
    std::vector<T> v;
    COMP compCost;

public:
    void push(const T& element)
    {
        v.push_back(element);

        std::sort(v.rbegin(), v.rend(), compCost);
    }

    const T& top()
    {
        return v.back();
    }

    void pop()
    {
        v.pop_back();
    }

    bool isEmpty() const
    {
        return (v.size() == 0);
    }
};
