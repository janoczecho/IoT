#include <stdio.h>

#define SIZE 3

char board[SIZE][SIZE]; // plansza do gry

// Funkcja do inicjalizacji planszy
void initBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

// Funkcja do wyświetlania planszy
void printBoard() {
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

// Funkcja sprawdzająca, czy ktoś wygrał
char checkWin() {
    // Sprawdzenie wierszy i kolumn
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0]; // Zwycięzca w wierszu
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i]; // Zwycięzca w kolumnie
    }

    // Sprawdzenie przekątnych
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0]; // Zwycięzca na przekątnej
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2]; // Zwycięzca na przekątnej

    return ' '; // Brak zwycięzcy
}

// Funkcja sprawdzająca, czy plansza jest pełna (remis)
int checkDraw() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                return 0; // Gra nadal trwa
            }
        }
    }
    return 1; // Remis
}

// Funkcja do wykonania ruchu gracza
int makeMove(int row, int col, char player) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ') {
        board[row][col] = player;
        return 1; // Ruch wykonany poprawnie
    }
    return 0; // Nieprawidłowy ruch
}

int main() {
    int row, col;
    char currentPlayer = 'X'; // Zaczyna gracz X
    char winner = ' ';

    initBoard();

    printf("Gra w Kółko i Krzyżyk!\n");

    // Główna pętla gry
    while (winner == ' ' && !checkDraw()) {
        printBoard();
        printf("Gracz %c, podaj wiersz i kolumnę (0-2): ", currentPlayer);
        scanf("%d %d", &row, &col);

        if (makeMove(row, col, currentPlayer)) {
            winner = checkWin();
            if (winner == ' ') {
                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X'; // Zmiana gracza
            }
        } else {
            printf("Nieprawidłowy ruch. Spróbuj ponownie.\n");
        }
    }

    printBoard();

    if (winner != ' ') {
        printf("Gracz %c wygrywa!\n", winner);
    } else {
        printf("Remis!\n");
    }

    return 0;
}
