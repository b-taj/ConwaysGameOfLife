#include "raylib.h"
#include <iostream>
#include <cstdlib> 
#include <ctime>  
using namespace std;


const int rows = 80;
const int cols = 100;
int terminalWidth = 1000;
int terminalHeight = 800;
int squareSize = 10;


void populateGrid(int numbers[rows][cols], int rows, int cols) {

    srand(time(0)); // Seed the random number generator

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            int random_num = (rand() % 100) + 1; // Range 1 to 100
            if (random_num <= 20) { // 20% chance of being 1
                numbers[i][j] = 1;
            }           
            else {
                numbers[i][j] = 0;
            }
        }
    }
}

void checkNeighbours(int numbers[rows][cols], int newNumbers[rows][cols], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            int liveNeighbours = 0;
            for (int x = i -1; x <= i + 1; x++) {
                for (int y = j - 1; y <= j + 1; y++) {
                    if (x >= 0 && x < rows && y >= 0 && y < cols) { // Check bounds
                        if (x == i && y == j) {
                            continue;
                        }
                        if (numbers[x][y] == 1) {
                            liveNeighbours++;
                            }
                        }
                    }
                }
            if (numbers[i][j] == 1) //cell is live
            {
           //the cell is live and has 2 or 3 live neighbours, it stays alive
                if (liveNeighbours == 2 || liveNeighbours == 3) {
                newNumbers[i][j] = 1;
                }             
                //underpopuluation and overpopulation, the cell dies
                else {
                newNumbers[i][j] = 0;
                }
            }

            else //cell is dead
            {
                //the cell is dead and has exactly 3 live neighbours, it becomes alive
                if (liveNeighbours == 3) {
                    newNumbers[i][j] = 1;
                }
                else {
                    newNumbers[i][j] = 0;
                }
            }
        }
    }
}

void printGrid(int numbers[rows][cols], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
			DrawRectangleLines(j * squareSize, i * squareSize, squareSize, squareSize, LIGHTGRAY);
			
            if (numbers[i][j] == 1) {
                DrawRectangle(j * squareSize, i * squareSize, squareSize, squareSize, ORANGE);
            }
        }
    }
}

void copyGrid(int numbers[rows][cols], int newNumbers[rows][cols], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            numbers[i][j] = newNumbers[i][j];
        }
    }
}

void mouseInteraction(int numbers[rows][cols])
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        int col = mouseX / squareSize;
        int row = mouseY / squareSize;

        if (row >= 0 && row < rows &&
            col >= 0 && col < cols)
        {
            numbers[row][col] = !numbers[row][col];
        }
    }
}

int main()
{	
	int numbers[rows][cols];
	int newNumbers[rows][cols];

	populateGrid(numbers, rows, cols);

    InitWindow(terminalWidth, terminalHeight, "Conway's Game of Life");

	float timer = 0.0f;

	while (!WindowShouldClose())
	{
    	timer += GetFrameTime();

		mouseInteraction(numbers);

    	if (timer >= 0.1f)
    	{
			checkNeighbours(numbers, newNumbers, rows, cols);

        	copyGrid(numbers, newNumbers, rows, cols);

        	timer = 0.0f;
    	}

    	BeginDrawing();

    	ClearBackground(BLACK);

    	printGrid(numbers, rows, cols);

    	EndDrawing();
	}

    CloseWindow();

    return 0;
}