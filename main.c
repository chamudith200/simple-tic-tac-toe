#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Structure that holds the board, each players bitmasks
typedef struct{
    int board[9];
    uint16_t player_bitmask[2];
    int current_player;
    uint16_t wining_masks[8];
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
int check_winner(Game *game, int player);


int main() {
    Game game;
    game_init(&game);

    mark_player_move(&game, 0, 1);
    mark_player_move(&game, 4, 1);
    mark_player_move(&game, 8, 1);
    print_board(&game);
    check_winner(&game, 1);

    return 0;
}

// Initalize the game
void game_init(Game *game) {
    memset(game->board, 0, sizeof(game->board));
    game->player_bitmask[0] = 0b000000000;
    game->player_bitmask[1] = 0b000000000;
    game->current_player = BOARD_P1;

    // Wining masks
    game->wining_masks[0] = 0b111000000;
    game->wining_masks[1] = 0b000111000;
    game->wining_masks[2] = 0b000000111;

    game->wining_masks[3] = 0b100100100;
    game->wining_masks[4] = 0b010010010;
    game->wining_masks[5] = 0b001001001;

    game->wining_masks[6] = 0b100010001;
    game->wining_masks[7] = 0b001010100;
}

// Game loop
int game_loop(Game *game) {

}

// Print the entire boards
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

// Move according to player input
int mark_player_move(Game *game, int cell, int player) {
    int cell_bin = 8 - cell;
    // Check if the cell is alrady occupied
    if (game->board[cell] != BOARD_EMPTY) return 0;
    // If not register that move
    game->board[cell] = (player == 1) ? BOARD_P1 : BOARD_P2;
    game->player_bitmask[player - 1] = game->player_bitmask[player - 1] |(1 << cell_bin);
    return 1; 
}

// Get user inputs about which cell to play
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

// Check if the provivded usser have won
int check_winner(Game *game, int player) {
    for (int i = 0; i < 8; i++) {
        if ((game->player_bitmask[player-1] & game->wining_masks[i]) == game->wining_masks[i]) {
            printf("%d won\n", player);
            return 1;
        }
    }
    printf("%i not won\n", player);
    return 0;
}