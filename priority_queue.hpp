#pragma once

#include <vector>
#include <algorithm>

template <class T, class COMPCOST, class COMPELEM>
class PriorityQueue
{
private:
    std::vector<T> v;
    COMPCOST compCost;
    COMPELEM compElem;

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

    void remove(const T& element)
    {
        for (auto i = v.begin(); i != v.end(); ++i)
        {
            if (compElem(*i, element))
            {
                v.erase(i);
                break;
            }
        }
    }
};
