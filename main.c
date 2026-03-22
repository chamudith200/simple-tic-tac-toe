#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Structure that holds the board, each players bitmasks
typedef struct{
    int board[9];
    uint16_t player_bitmask[2];
    int player;
}Game;

enum{
    BOARD_EMPTY,
    BOARD_P1,
    BOARD_P2,
}PlayerSigns;

void game_init(Game *game);
void print_board(Game *game);
int mark_player_move(Game *game, int cell, int player);
int get_user_inputs();


int main() {
    Game game;
    game_init(&game);

    print_board(&game);
    
    int usr_cell = get_user_inputs();
    printf("%d\n", usr_cell);

    mark_player_move(&game, usr_cell, 1);
    print_board(&game);



}

// Initalize the game
void game_init(Game *game) {
    memset(game->board, 0, sizeof(game->board));
    game->player_bitmask[0] = 0b000000000;
    game->player_bitmask[1] = 0b000000000;
    game->player = BOARD_P1;
}

void print_board(Game *game) {
    // Loop through the board row - col
    for (int i = 0; i < 9; i++) {
        if (i != 0 && i % 3 == 0) printf("\n");

        if (game->board[i] == BOARD_P1) printf("X ");
        else if (game->board[i] == BOARD_P2) printf("O ");
        else printf(". ");
    }
    printf("\n\n");
}

int mark_player_move(Game *game, int cell, int player) {
    int cell_bin = 8 - cell;
    // Check if the cell is alrady occupied
    if (game->board[cell] != BOARD_EMPTY) return 0;
    // If not register that move
    game->board[cell] = (player == 1) ? BOARD_P1 : BOARD_P2;
    game->player_bitmask[player - 1] = game->player_bitmask[player - 1] |(1 << cell_bin);
    return 1; 
}

int get_user_inputs() {
    int is_valid_input = 0;
    int cell;
    printf("Enter: row col\n");
    while (is_valid_input == 0) {
        int row, col;
        printf("Enter: ");
        scanf("%i %i", &row, &col);
        row--;
        col--;
        // Check the boundaries of entered row and col values
        if (row < 0 || row > 2 || col < 0 || col > 2) {
            printf("Wrong row or col.\nEnter them againi correctly..\n");
            continue;
        }
        cell = (row * 3) + col;
        is_valid_input = 1;
    }
    return cell;
}