#include "SelectionSort.h"

SelectionSort::SelectionSort()
    : currentIndex(1)
    , selectedIndex(0)
    , minimumIndex(0)
    , comparisons(0)
    , swaps(0)
    , isFinished(false)
{
}

void SelectionSort::Reset()
{
    currentIndex = 1;
    selectedIndex = 0;
    minimumIndex = 0;

    comparisons = 0;
    swaps = 0;

    isFinished = false;
}

void SelectionSort::Step(std::vector<int>& values)
{
    if (isFinished)
    {
        return;
    }

    int count = static_cast<int>(values.size());

    if (selectedIndex >= count - 1)
    {
        isFinished = true;
        return;
    }

    if (currentIndex < count)
    {
        comparisons++;

        if (values[currentIndex] < values[minimumIndex])
        {
            minimumIndex = currentIndex;
        }

        currentIndex++;
    }
    else
    {
        if (minimumIndex != selectedIndex)
        {
            int temp = values[selectedIndex];
            values[selectedIndex] = values[minimumIndex];
            values[minimumIndex] = temp;

            swaps++;
        }

        selectedIndex++;
        minimumIndex = selectedIndex;
        currentIndex = selectedIndex + 1;
    }
}

bool SelectionSort::IsFinished() const
{
    return isFinished;
}

int SelectionSort::GetCurrentIndex() const
{
    return currentIndex;
}

int SelectionSort::GetSelectedIndex() const
{
    return selectedIndex;
}

int SelectionSort::GetMinimumIndex() const
{
    return minimumIndex;
}

int SelectionSort::GetComparisons() const
{
    return comparisons;
}

int SelectionSort::GetSwaps() const
{
    return swaps;
}