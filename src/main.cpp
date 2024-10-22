#include "raylib.h"
#include "Grid.h"
#include <iostream>
#include "GameManager.h"
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main() {

    static plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
    plog::init(plog::verbose, &consoleAppender);
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Connect 4 Board");
    SetTargetFPS(60);

    Grid grid(SCREEN_WIDTH, SCREEN_HEIGHT);
    GameManager gameManager(grid);

    while (!WindowShouldClose()) {
        gameManager.update();

        BeginDrawing();
        ClearBackground(WHITE);
        gameManager.handleRender();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}