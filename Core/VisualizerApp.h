#pragma once

#include "Sorting/SortingVisualizer.h"

class VisualizerApp
{
public:
    VisualizerApp();
    ~VisualizerApp();

    void Run();

private:
    static constexpr int ScreenWidth = 1280;
    static constexpr int ScreenHeight = 720;

    SortingVisualizer sortingVisualizer;

    void HandleInput();
    void Update();
    void Draw();
};