#include "SortingVisualizer.h"

SortingVisualizer::SortingVisualizer()
    : currentAlgorithm(SortingAlgorithm::Bubble)
    , barCount(100)
    , stepsPerFrame(2)
    , isSorting(false)
    , isSorted(false)
    
{
    GenerateValues();
}

void SortingVisualizer::HandleInput()
{
    if (IsKeyPressed(KEY_R))
    {
        GenerateValues();
    }

    if (IsKeyPressed(KEY_ONE))
    {
        currentAlgorithm = SortingAlgorithm::Bubble;
        GenerateValues();
    }

    if (IsKeyPressed(KEY_TWO))
    {
        currentAlgorithm = SortingAlgorithm::Selection;
        GenerateValues();
    }

    if (IsKeyPressed(KEY_THREE))
    {
        currentAlgorithm = SortingAlgorithm::Heap;
        GenerateValues();
    }

    if (IsKeyPressed(KEY_SPACE))
    {
        if (!isSorted)
        {
            isSorting = !isSorting;
        }
    }

    if (IsKeyPressed(KEY_UP))
    {
        stepsPerFrame++;
    }

    if (IsKeyPressed(KEY_DOWN))
    {
        stepsPerFrame--;

        if (stepsPerFrame < 1)
        {
            stepsPerFrame = 1;
        }
    }
}

void SortingVisualizer::Update()
{
    if (!isSorting)
    {
        return;
    }

    int effectiveStepsPerFrame = stepsPerFrame;

    if (currentAlgorithm == SortingAlgorithm::Heap)
    {
        effectiveStepsPerFrame = 1;
    }

    for (int i = 0; i < effectiveStepsPerFrame; i++)
    {
        StepCurrentAlgorithm();

        if (IsCurrentAlgorithmFinished())
        {
            isSorted = true;
            isSorting = false;
            break;
        }
    }
}

void SortingVisualizer::Draw()
{
    DrawUI();
    DrawBars();
}

void SortingVisualizer::GenerateValues()
{
    values.clear();

    barCount = GetRandomValue(50, 100);

    for (int i = 0; i < barCount; i++)
    {
        values.push_back(GetRandomValue(20, 600));
    }

    ResetCurrentAlgorithm();

    isSorting = false;
    isSorted = false;
}

void SortingVisualizer::ResetCurrentAlgorithm()
{
    bubbleSort.Reset();
    selectionSort.Reset();
    heapSort.Reset();
}

void SortingVisualizer::StepCurrentAlgorithm()
{
    switch (currentAlgorithm)
    {
    case SortingAlgorithm::Bubble:
        bubbleSort.Step(values);
        break;

    case SortingAlgorithm::Selection:
        selectionSort.Step(values);
        break;
    case SortingAlgorithm::Heap:
        heapSort.Step(values);
        break;
    }
    
}

bool SortingVisualizer::IsCurrentAlgorithmFinished() const
{
    switch (currentAlgorithm)
    {
    case SortingAlgorithm::Bubble:
        return bubbleSort.IsFinished();

    case SortingAlgorithm::Selection:
        return selectionSort.IsFinished();

    case SortingAlgorithm::Heap:
        return heapSort.IsFinished();

    default:
        return true;
    }
}

int SortingVisualizer::GetCurrentComparisons() const
{
    switch (currentAlgorithm)
    {
    case SortingAlgorithm::Bubble:
        return bubbleSort.GetComparisons();

    case SortingAlgorithm::Selection:
        return selectionSort.GetComparisons();

    case SortingAlgorithm::Heap:
        return heapSort.GetComparisons();

    default:
        return 0;
    }
}

int SortingVisualizer::GetCurrentSwaps() const
{
    switch (currentAlgorithm)
    {
    case SortingAlgorithm::Bubble:
        return bubbleSort.GetSwaps();

    case SortingAlgorithm::Selection:
        return selectionSort.GetSwaps();

    case SortingAlgorithm::Heap:
        return heapSort.GetComparisons();

    default:
        return 0;
    }
}

const char* SortingVisualizer::GetCurrentAlgorithmName() const
{
    switch (currentAlgorithm)
    {
    case SortingAlgorithm::Bubble:
        return "Bubble Sort";

    case SortingAlgorithm::Selection:
        return "Selection Sort";

    case SortingAlgorithm::Heap:
        return "Heap Sort";

    default:
        return "Unknown";
    }
}

void SortingVisualizer::DrawBars()
{
    float barWidth = static_cast<float>(ScreenWidth) / barCount;

    int availableHeight = ScreenHeight - UiHeight;

    int bubbleCurrentIndex = bubbleSort.GetCurrentIndex();

    int selectionCurrentIndex = selectionSort.GetCurrentIndex();
    int selectionSelectedIndex = selectionSort.GetSelectedIndex();
    int selectionMinimumIndex = selectionSort.GetMinimumIndex();

    int heapCurrentIndex = heapSort.GetCurrentIndex();
    int heapLeftChildIndex = heapSort.GetLeftChildIndex();
    int heapRightChildIndex = heapSort.GetRightChildIndex();
    int heapLargestIndex = heapSort.GetLargestIndex();
    int heapEndIndex = heapSort.GetHeapEndIndex();

    for (int i = 0; i < static_cast<int>(values.size()); i++)
    {
        int originalHeight = values[i];

        int barHeight = static_cast<int>((originalHeight / 600.0f) * availableHeight);

        Color color = LIGHTGRAY;

        if (isSorting && !isSorted)
        {
            switch (currentAlgorithm)
            {
            case SortingAlgorithm::Bubble:
                if (i == bubbleCurrentIndex || i == bubbleCurrentIndex + 1)
                {
                    color = RED;
                }
                break;

            case SortingAlgorithm::Selection:
                if (i == selectionSelectedIndex)
                {
                    color = BLUE;
                }
                else if (i == selectionMinimumIndex)
                {
                    color = GREEN;
                }
                else if (i == selectionCurrentIndex)
                {
                    color = RED;
                }
                break;

            case SortingAlgorithm::Heap:
                if (i >= heapEndIndex)
                {
                    color = BLUE;
                }
                else if (i == heapLargestIndex)
                {
                    color = GREEN;
                }
                else if (i == heapCurrentIndex)
                {
                    color = RED;
                }
                else if (i == heapLeftChildIndex || i == heapRightChildIndex)
                {
                    color = ORANGE;
                }
                break;
            }
        }

        DrawRectangle(
            static_cast<int>(i * barWidth),
            ScreenHeight - barHeight,
            static_cast<int>(barWidth - 1),
            barHeight,
            color
        );
    }
}

void SortingVisualizer::DrawUI()
{
    DrawText(TextFormat("Sorting Visualizer - %s", GetCurrentAlgorithmName()), 20, 20, 30, WHITE);
    DrawText("1 = Bubble Sort | 2 = Selection Sort | 3 = Heap Sort", 20, 60, 20, GRAY);
    DrawText("SPACE = Start/Pause | R = Reset | UP/DOWN = Speed", 20, 85, 20, GRAY);

    DrawText(TextFormat("Bars: %i", barCount), 20, 125, 20, WHITE);
    DrawText(TextFormat("Comparisons: %i", GetCurrentComparisons()), 20, 150, 20, WHITE);
    DrawText(TextFormat("Swaps: %i", GetCurrentSwaps()), 20, 175, 20, WHITE);
    DrawText(TextFormat("Steps per frame: %i", stepsPerFrame), 20, 200, 20, WHITE);

    if (currentAlgorithm == SortingAlgorithm::Bubble)
    {
        DrawText("Bubble colors: RED = compared pair", 20, 230, 18, GRAY);
    }
    
    if (currentAlgorithm == SortingAlgorithm::Selection)
    {
        DrawText("Selection colors: BLUE = sorted boundary | GREEN = current minimum | RED = scanning", 20, 230, 18, GRAY);
    }

    if (currentAlgorithm == SortingAlgorithm::Heap)
    {
        DrawText("Heap colors: RED = parent | ORANGE = children | GREEN = largest | BLUE = sorted", 20, 230, 18, GRAY);
    }

    if (isSorted)
    {
        DrawText("SORTED!", 20, 260, 25, GREEN);

        DrawText(
            TextFormat("Final result: %s completed with %i comparisons and %i swaps.",
                GetCurrentAlgorithmName(),
                GetCurrentComparisons(),
                GetCurrentSwaps()),
            20,
            295,
            20,
            WHITE
        );
    }
}