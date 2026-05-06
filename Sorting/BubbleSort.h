#pragma once

#include <vector>

class BubbleSort
{
public:
    BubbleSort();

    void Reset();
    void Step(std::vector<int>& values);

    bool IsFinished() const;
    int GetCurrentIndex() const;
    int GetComparisons() const;
    int GetSwaps() const;

private:
    int currentIndex;
    int currentPass;

    int comparisons;
    int swaps;

    bool isFinished;
};