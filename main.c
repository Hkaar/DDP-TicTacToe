#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3

// Menampilkan papan permainan beserta nomor baris dan kolom
void draw_board(char board[])
{
    system("cls"); // Membersihkan layar (Windows)
    printf("\e[0;37m-----------------------------\n");
    printf("Pilih antara 1 dan 3, contoh: 11, 12, 13, 21, 22, 23, 31, 32, 33\n");
    printf("# 1 2 3\n");

    // Baris
    for (int i = 0, n = 0; i < SIZE; i++)
    {
        // Kolom
        printf("%d ", i + 1);
        for (int j = 0; j < SIZE; j++)
        {
            printf("%c ", board[n]);
            n++;
        }
        printf("\n");
    }
}

// Menginisialisasi papan dengan karakter '-'
void init_board(char board[])
{
    for (int i = 0; i < SIZE * SIZE; i++)
    {
        board[i] = '-';
    }
}

// Menempatkan tanda pemain ke papan
// Mengembalikan true jika berhasil, false jika posisi tidak valid atau sudah terisi
bool place(char board[], char player, char *namapemain)
{
    char posinput[64];

    printf("%s, masukkan posisi kamu (xy, contoh: 11): ", namapemain);
    scanf("%s", posinput);

    int row = (posinput[0] - '0') - 1;
    int col = (posinput[1] - '0') - 1;

    int pos = col + row * SIZE;

    if (pos >= 0 && pos < SIZE * SIZE)
    {
        if (board[pos] == 'x' || board[pos] == 'o')
            return false;

        board[pos] = player;
        return true;
    }

    return false;
}

// Mengecek apakah ada tiga tanda yang sama dalam satu garis
bool check(char b[], char p)
{
    // Mengecek baris
    if (b[0] == p && b[1] == p && b[2] == p)
        return true;
    if (b[3] == p && b[4] == p && b[5] == p)
        return true;
    if (b[6] == p && b[7] == p && b[8] == p)
        return true;

    // Mengecek kolom
    if (b[0] == p && b[3] == p && b[6] == p)
        return true;
    if (b[1] == p && b[4] == p && b[7] == p)
        return true;
    if (b[2] == p && b[5] == p && b[8] == p)
        return true;

    // Mengecek diagonal
    if (b[0] == p && b[4] == p && b[8] == p)
        return true;
    if (b[2] == p && b[4] == p && b[6] == p)
        return true;

    // Jika belum ada pemenang
    return false;
}

int main()
{
    char board[SIZE * SIZE];
    char player = 'x';
    char nama_pemain[2][50]; // Menyimpan nama dua pemain
    int poin[2] = {0, 0};    // Array untuk menyimpan poin kedua pemain

    printf("\e[1;32mMasukkan nama Player 1 (X): ");
    scanf("%s", nama_pemain[0]);
    printf("\e[1;31mMasukkan nama Player 2 (O): ");
    scanf("%s", nama_pemain[1]);

    bool lanjut = true;
    char ulang;

    while (lanjut)
    {
        init_board(board);
        player = 'x';

        while (true)
        {
            draw_board(board);
            printf("Skor saat ini: \e[1;32m(X) %s = \e[0;37m%d | \e[1;31m(O) %s = \e[0;37m%d\n",
                   nama_pemain[0], poin[0], nama_pemain[1], poin[1]);

            char namapemain[50];
            sprintf(namapemain, "%s", (player == 'x') ? nama_pemain[0] : nama_pemain[1]);

            if (place(board, player, namapemain))
            {
                if (check(board, player))
                {
                    draw_board(board);
                    printf("-----------------------------\n");
                    if (player == 'x')
                    {
                        printf("%s menang!\n", nama_pemain[0]);
                        poin[0]++;
                    }
                    else
                    {
                        printf("%s menang!\n", nama_pemain[1]);
                        poin[1]++;
                    }
                    printf("-----------------------------\n");
                    break;
                }

                // Ganti pemain
                player = (player == 'x') ? 'o' : 'x';
            }
            else
            {
                printf("Posisi tidak valid atau sudah terisi, coba lagi!\n");
                system("pause");
            }
        }

        // Tanya apakah ingin bermain lagi
        printf("Ingin bermain lagi? (y/n): ");
        scanf(" %c", &ulang);

        if (ulang != 'y' && ulang != 'Y')
        {
            lanjut = false;
            printf("\n-----------------------------\n");
            printf("Permainan selesai!\n");
            printf("Skor akhir:\n");
            printf("%s: %d poin\n", nama_pemain[0], poin[0]);
            printf("%s: %d poin\n", nama_pemain[1], poin[1]);
            if (poin[0] > poin[1])
            {
                printf("Pemenang keseluruhan: %s!\n", nama_pemain[0]);
            }
            else if (poin[1] > poin[0])
            {
                printf("Pemenang keseluruhan: %s!\n", nama_pemain[1]);
            }
            else
            {
                printf("\e[1;32mPermainan berakhir seri!\n");
            }
            printf("-----------------------------\n");
        }
    }

    return 0;
}
