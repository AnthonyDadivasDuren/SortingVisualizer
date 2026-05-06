#include "BubbleSort.h"

BubbleSort::BubbleSort()
    : currentIndex(0)
    , currentPass(0)
    , comparisons(0)
    , swaps(0)
    , isFinished(false)
{
}

void BubbleSort::Reset()
{
    currentIndex = 0;
    currentPass = 0;

    comparisons = 0;
    swaps = 0;

    isFinished = false;
}

void BubbleSort::Step(std::vector<int>& values)
{
    if (isFinished)
    {
        return;
    }

    int count = static_cast<int>(values.size());

    if (currentPass >= count - 1)
    {
        isFinished = true;
        return;
    }

    if (currentIndex < count - currentPass - 1)
    {
        comparisons++;

        if (values[currentIndex] > values[currentIndex + 1])
        {
            int temp = values[currentIndex];
            values[currentIndex] = values[currentIndex + 1];
            values[currentIndex + 1] = temp;

            swaps++;
        }

        currentIndex++;
    }
    else
    {
        currentIndex = 0;
        currentPass++;
    }
}

bool BubbleSort::IsFinished() const
{
    return isFinished;
}

int BubbleSort::GetCurrentIndex() const
{
    return currentIndex;
}

int BubbleSort::GetComparisons() const
{
    return comparisons;
}

int BubbleSort::GetSwaps() const
{
    return swaps;
}