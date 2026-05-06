#pragma once

#include <vector>

class HeapSort
{
public:
    HeapSort();

    void Reset();
    void Step(std::vector<int>& values);

    bool IsFinished() const;

    int GetCurrentIndex() const;
    int GetLeftChildIndex() const;
    int GetRightChildIndex() const;
    int GetLargestIndex() const;
    int GetHeapEndIndex() const;

    int GetComparisons() const;
    int GetSwaps() const;

private:
    enum class Phase
    {
        BuildHeap,
        ExtractMax,
        Finished
    };

    Phase phase;

    int heapSize;
    int buildIndex;

    int currentIndex;
    int leftChildIndex;
    int rightChildIndex;
    int largestIndex;

    int comparisons;
    int swaps;

    bool isHeapifying;

    void StartHeapify(int index);
    bool HeapifyStep(std::vector<int>& values);
};