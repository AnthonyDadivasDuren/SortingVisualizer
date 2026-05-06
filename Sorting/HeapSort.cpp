#include "HeapSort.h"

HeapSort::HeapSort()
    : phase(Phase::BuildHeap)
    , heapSize(0)
    , buildIndex(0)
    , currentIndex(-1)
    , leftChildIndex(-1)
    , rightChildIndex(-1)
    , largestIndex(-1)
    , comparisons(0)
    , swaps(0)
    , isHeapifying(false)
{
}

void HeapSort::Reset()
{
    phase = Phase::BuildHeap;

    heapSize = 0;
    buildIndex = 0;

    currentIndex = -1;
    leftChildIndex = -1;
    rightChildIndex = -1;
    largestIndex = -1;

    comparisons = 0;
    swaps = 0;

    isHeapifying = false;
}

void HeapSort::Step(std::vector<int>& values)
{
    if (phase == Phase::Finished)
    {
        return;
    }

    int count = static_cast<int>(values.size());

    if (count <= 1)
    {
        phase = Phase::Finished;
        return;
    }

    if (heapSize == 0)
    {
        heapSize = count;
        buildIndex = count / 2 - 1;
    }

    switch (phase)
    {
    case Phase::BuildHeap:
    {
        if (buildIndex < 0)
        {
            phase = Phase::ExtractMax;
            isHeapifying = false;
            return;
        }

        if (!isHeapifying)
        {
            StartHeapify(buildIndex);
        }

        bool finishedHeapify = HeapifyStep(values);

        if (finishedHeapify)
        {
            buildIndex--;
            isHeapifying = false;
        }

        break;
    }

    case Phase::ExtractMax:
    {
        if (heapSize <= 1)
        {
            phase = Phase::Finished;
            return;
        }

        if (!isHeapifying)
        {
            int temp = values[0];
            values[0] = values[heapSize - 1];
            values[heapSize - 1] = temp;

            swaps++;

            heapSize--;

            StartHeapify(0);
        }

        bool finishedHeapify = HeapifyStep(values);

        if (finishedHeapify)
        {
            isHeapifying = false;
        }

        break;
    }

    case Phase::Finished:
        break;
    }
}

void HeapSort::StartHeapify(int index)
{
    currentIndex = index;
    leftChildIndex = -1;
    rightChildIndex = -1;
    largestIndex = index;

    isHeapifying = true;
}

bool HeapSort::HeapifyStep(std::vector<int>& values)
{
    if (currentIndex < 0 || currentIndex >= heapSize)
    {
        return true;
    }

    leftChildIndex = currentIndex * 2 + 1;
    rightChildIndex = currentIndex * 2 + 2;
    largestIndex = currentIndex;

    if (leftChildIndex < heapSize)
    {
        comparisons++;

        if (values[leftChildIndex] > values[largestIndex])
        {
            largestIndex = leftChildIndex;
        }
    }

    if (rightChildIndex < heapSize)
    {
        comparisons++;

        if (values[rightChildIndex] > values[largestIndex])
        {
            largestIndex = rightChildIndex;
        }
    }

    if (largestIndex != currentIndex)
    {
        int temp = values[currentIndex];
        values[currentIndex] = values[largestIndex];
        values[largestIndex] = temp;

        swaps++;

        currentIndex = largestIndex;

        return false;
    }

    return true;
}

bool HeapSort::IsFinished() const
{
    return phase == Phase::Finished;
}

int HeapSort::GetCurrentIndex() const
{
    return currentIndex;
}

int HeapSort::GetLeftChildIndex() const
{
    return leftChildIndex;
}

int HeapSort::GetRightChildIndex() const
{
    return rightChildIndex;
}

int HeapSort::GetLargestIndex() const
{
    return largestIndex;
}

int HeapSort::GetHeapEndIndex() const
{
    return heapSize;
}

int HeapSort::GetComparisons() const
{
    return comparisons;
}

int HeapSort::GetSwaps() const
{
    return swaps;
}