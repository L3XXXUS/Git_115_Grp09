#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

void initializeBoard(int board[SIZE][SIZE], int revealed[SIZE][SIZE]) {
    int numbers[SIZE * SIZE] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8};

    srand(time(NULL));
    for (int i = 0; i < SIZE * SIZE; i++) {
        int randomIndex = rand() % (SIZE * SIZE);
        int temp = numbers[i];
        numbers[i] = numbers[randomIndex];
        numbers[randomIndex] = temp;
    }

    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = numbers[index++];
            revealed[i][j] = 0;
        }
    }
}

void displayBoard(int board[SIZE][SIZE], int revealed[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (revealed[i][j]) {
                printf(" %d ", board[i][j]);
            } else {
                printf(" * ");
            }
        }
        printf("\n");
    }
}

int isGameOver(int revealed[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (revealed[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

int getValidInput() {
    int input;
    while (scanf("%d", &input) != 1 || input < 1 || input > SIZE) {
        while(getchar() != '\n'); // Clear the buffer
        printf("Invalid input! Please enter a number between 1 and %d: ", SIZE);
    }
    return input;
}

int main() {
    int board[SIZE][SIZE];
    int revealed[SIZE][SIZE];
    int x1, y1, x2, y2;

    initializeBoard(board, revealed);

    printf("Welcome to the Memory Game!\n");
    printf("Match pairs of numbers to win the game.\n");
    printf("Note: Rows and columns are numbered from 1 to %d.\n\n", SIZE);

    while (!isGameOver(revealed)) {
        displayBoard(board, revealed);

        printf("\nEnter the coordinates of the first card (row column): ");
        x1 = getValidInput() - 1;
        y1 = getValidInput() - 1;

        if (revealed[x1][y1]) {
            printf("This card is already revealed! Try again.\n");
            continue;
        }

        revealed[x1][y1] = 1;
        displayBoard(board, revealed);

        printf("\nEnter the coordinates of the second card (row column): ");
        x2 = getValidInput() - 1;
        y2 = getValidInput() - 1;

        if (x1 == x2 && y1 == y2) {
            printf("You selected the same card twice! Try again.\n");
            revealed[x1][y1] = 0;
            continue;
        }

        if (revealed[x2][y2]) {
            printf("This card is already revealed! Try again.\n");
            revealed[x1][y1] = 0;
            continue;
        }

        revealed[x2][y2] = 1;
        displayBoard(board, revealed);

        if (board[x1][y1] == board[x2][y2]) {
            printf("It's a match!\n");
        } else {
            printf("Not a match. Try again.\n");
            revealed[x1][y1] = 0;
            revealed[x2][y2] = 0;
        }
    }

    printf("Congratulations! You've matched all pairs!\n");
    return 0;
}
