#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4  // Define the size of the grid (4x4)

// Function to initialize the board with pairs of numbers
void initializeBoard(int board[SIZE][SIZE], int revealed[SIZE][SIZE]) {
    int numbers[SIZE * SIZE] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8};

    // Shuffle the numbers randomly
    srand(time(NULL));
    for (int i = 0; i < SIZE * SIZE; i++) {
        int randomIndex = rand() % (SIZE * SIZE);
        int temp = numbers[i];
        numbers[i] = numbers[randomIndex];
        numbers[randomIndex] = temp;
    }

    // Fill the board with shuffled numbers
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = numbers[index++];
            revealed[i][j] = 0;  // Initialize revealed state to false (0)
        }
