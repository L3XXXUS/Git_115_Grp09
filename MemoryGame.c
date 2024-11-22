#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

// Initializes the game board with random pairs of numbers
void initializeBoard(int board[SIZE][SIZE], int revealed[SIZE][SIZE]) {
    // Create an array of numbers to be shuffled
    int numbers[SIZE * SIZE] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8};

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Shuffle the numbers randomly
    for (int i = 0; i < SIZE * SIZE; i++) {
        int randomIndex = rand() % (SIZE * SIZE);
        int temp = numbers[i];
        numbers[i] = numbers[randomIndex];
        numbers[randomIndex] = temp;
    }

    // Fill the board with shuffled numbers and initialize the revealed state
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = numbers[index++];
            revealed[i][j] = 0;
        }
    }
}

// Displays the current state of the game board
void displayBoard(int board[SIZE][SIZE], int revealed[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (revealed[i][j]) {
                printf(" %d ", board[i][j]); // Display the number
            } else {
                printf(" * "); // Hide the number
            }
        }
        printf("\n");
    }
}

// Checks if all pairs have been matched
int isGameOver(int revealed[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (revealed[i][j] == 0) {
                return 0; // Game is not over
            }
        }
    }
    return 1; // All pairs have been matched
}

// Gets valid input from the user
int getValidInput() {
    int input;
    while (scanf("%d", &input) != 1 || input < 1 || input > SIZE) {
        while (getchar() != '\n'); // Clear the input buffer
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

        // Check if the selected card is already revealed
        if (revealed[x1][y1]) {
            printf("This card is already revealed! Try again.\n");
            continue;
        }

        revealed[x1][y1] = 1;
        displayBoard(board, revealed);

        printf("\nEnter the coordinates of the second card (row column): ");
        x2 = getValidInput() - 1;
        y2 = getValidInput() - 1;

        // Check if the same card is selected twice
        if (x1 == x2 && y1 == y2) {
            printf("You selected the same card twice! Try again.\n");
            revealed[x1][y1] = 0;
            continue;
        }

        // Check if the second card is already revealed
        if (revealed[x2][y2]) {
            printf("This card is already revealed! Try again.\n");
            revealed[x1][y1] = 0;
            continue;
        }

        revealed[x2][y2] = 1;
        displayBoard(board, revealed);

        // Check if the two cards match
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
