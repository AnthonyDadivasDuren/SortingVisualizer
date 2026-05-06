#include "VisualizerApp.h"

#include "raylib.h"

VisualizerApp::VisualizerApp()
{
    InitWindow(ScreenWidth, ScreenHeight, "Sorting Visualizer");
    SetTargetFPS(60);
}

VisualizerApp::~VisualizerApp()
{
    CloseWindow();
}

void VisualizerApp::Run()
{
    while (!WindowShouldClose())
    {
        HandleInput();
        Update();
        Draw();
    }
}

void VisualizerApp::HandleInput()
{
    sortingVisualizer.HandleInput();
}

void VisualizerApp::Update()
{
    sortingVisualizer.Update();
}

void VisualizerApp::Draw()
{
    BeginDrawing();

    ClearBackground(BLACK);

    sortingVisualizer.Draw();

    EndDrawing();
}