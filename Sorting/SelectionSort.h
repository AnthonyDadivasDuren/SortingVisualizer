#pragma once

#include <vector>

class SelectionSort
{
public:
    SelectionSort();

    void Reset();
    void Step(std::vector<int>& values);

    bool IsFinished() const;
    int GetCurrentIndex() const;
    int GetSelectedIndex() const;
    int GetMinimumIndex() const;
    int GetComparisons() const;
    int GetSwaps() const;

private:
    int currentIndex;
    int selectedIndex;
    int minimumIndex;

    int comparisons;
    int swaps;

    bool isFinished;
};