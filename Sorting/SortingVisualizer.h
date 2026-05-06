#pragma once

#include "raylib.h"

#include "BubbleSort.h"
#include "SelectionSort.h"
#include "HeapSort.h"

#include <vector>

enum class SortingAlgorithm
{
    Bubble,
    Selection,
    Heap
};

class SortingVisualizer
{
public:
    SortingVisualizer();

    void HandleInput();
    void Update();
    void Draw();

private:
    static constexpr int ScreenWidth = 1280;
    static constexpr int ScreenHeight = 720;
    static constexpr int UiHeight = 340;

    std::vector<int> values;

    BubbleSort bubbleSort;
    SelectionSort selectionSort;
    HeapSort heapSort;

    SortingAlgorithm currentAlgorithm;

    int barCount;
    int stepsPerFrame;

    bool isSorting;
    bool isSorted;

    void GenerateValues();
    void ResetCurrentAlgorithm();
    void StepCurrentAlgorithm();

    bool IsCurrentAlgorithmFinished() const;
    int GetCurrentComparisons() const;
    int GetCurrentSwaps() const;

    const char* GetCurrentAlgorithmName() const;

    void DrawBars();
    void DrawUI();
};