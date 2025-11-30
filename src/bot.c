#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "core.h"
#include "utils.h"

typedef enum { EASY, MEDIUM, HARD } Difficulty;

/**
 * Memeriksa jika sebuah posisi kosong
 *
 * @param board[] Array papan permainan
 * @param row Koordinat baris yang akan dicek
 * @param col Koordinat kolumn yang akan dicek
 */
bool isEmpty(char board[], int row, int col) {
    int idx = (row - 1) * 3 + (col - 1);
    return board[idx] != 'x' && board[idx] != 'o';
}

/**
 * Merubah index menjadi posisi berupa string
 *
 * @param idx index posisi pada board
 * @param pos pointer ke string yang akan di return
 */
void indexToPos(int idx, char *pos) {
    int row = idx / 3 + 1;
    int col = idx % 3 + 1;
    sprintf(pos, "%d%d", row, col);
}

int getBoardIndex(int row, int col) { return (row - 1) * 3 + (col - 1); }

/**
 * Algoritma random untuk memilih posisi (dipakai untuk mode Easy pada AI)
 *
 * @param board Papan permainan
 * @param aiPos Pointer posisi ai yang akan di return
 */
void findEasyMove(char board[], char *aiPos) {
    bool validMove = false;
    while (!validMove) {
        sprintf(aiPos, "%d%d", randint(3) + 1, randint(3) + 1);
        int row = aiPos[0] - '0';
        int col = aiPos[1] - '0';
        validMove = isEmpty(board, row, col);
    }
}

/**
 * Algoritma yang berusaha untuk mengalahkan dan menyusahkan pemain (dipakai
 * untuk mode Medium pada)
 * 
 * @param board Papan permainan
 * @param aiPos Pointer posisi ai yang akan di return
 * @param rSeed Random seed for setting if the algorithm will use random chance
 */
void findMediumMove(char board[], char *aiPos, int rSeed) {
    if (rSeed != NULL && rSeed > 100) rSeed = 100;
    
    if (rSeed != NULL) {
        int dSeed = randint(100);

        if (dSeed > 70) {
            findEasyMove(board, aiPos);
            return;
        }   
    }
    
    // Periksa jika ada posisi musuh yang bisa diblokir
    int winningEnemyPos[][3][2] = {
        {{1, 1}, {1, 2}, {1, 3}}, {{2, 1}, {2, 2}, {2, 3}},
        {{3, 1}, {3, 2}, {3, 3}}, {{1, 1}, {2, 1}, {3, 1}},
        {{1, 2}, {2, 2}, {3, 2}}, {{1, 3}, {2, 3}, {3, 3}},
        {{1, 1}, {2, 2}, {3, 3}}, {{1, 3}, {2, 2}, {3, 1}},
    };

    int xAmount = 0;
    int oAmount = 0;
    int emptyRow = 0;
    int emptyCol = 0;

    int tempIdx = 0;

    for (int i = 0; i < 8; i++) {
        xAmount = 0;
        oAmount = 0;
        emptyRow = -1;
        emptyCol = -1;

        for (int j = 0; j < 3; j++) {
            tempIdx = getBoardIndex(winningEnemyPos[i][j][0],
                                    winningEnemyPos[i][j][1]);

            if (board[tempIdx] == 'x') {
                xAmount++;
            } else if (board[tempIdx] == 'o') {
                oAmount++;
            } else {
                emptyRow = winningEnemyPos[i][j][0];
                emptyCol = winningEnemyPos[i][j][1];
            }
        }

        if (xAmount == 2 && oAmount <= 0 && emptyRow != -1) {
            indexToPos(getBoardIndex(emptyRow, emptyCol), aiPos);
            return;
        }
    }

    // Ambil posisi yang strategis
    int singlePos[][2] = {{2, 2}, {1, 1}, {1, 3}, {3, 1}, {3, 3}};

    for (int i = 0; i < 5; i++) {
        if (isEmpty(board, singlePos[i][0], singlePos[i][1])) {
            sprintf(aiPos, "%d%d", singlePos[i][0], singlePos[i][1]);
            return;
        }
    }

    findEasyMove(board, aiPos);
}

/**
 * Algoritma yang berusaha mengalahkan lawan dengan prediksi
 * menggunakan algoritma minimax (digunakan untuk mode HARD)
 * 
 * @param board Papan permainan
 * @param aiPos Pointer posisi ai yang akan di return
 */
void findHardMove(char board[], char *aiPos) {
    findMediumMove(board, aiPos, 90); // TODO! CHANGE TO USE MINIMAX
}

/**
 * Dapatkan posisi dari komputer (AI) berdasarkan tingkatan kesusahan
 *
 * @param board Papan permainan
 * @param Pointer posisi ai yang akan di return
 * @param difficulty Tingkat kesusahan AI
 */
void makeAIMove(char board[], char *aiPos, Difficulty difficulty) {
    switch (difficulty) {
    case EASY:
        findEasyMove(board, aiPos);
        break;
    case MEDIUM:
        findMediumMove(board, aiPos, 75);
        break;
    case HARD:
        findHardMove(board, aiPos);
        break;
    }
}
