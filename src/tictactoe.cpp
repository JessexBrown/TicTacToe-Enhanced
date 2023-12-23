
#include "../includes/tictactoe.h"

TicTacToe::TicTacToe() {
    // Initialize empty board with ' '
    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            board_[i][j] = ' ';
        }
    }

    // Initialize move map 
    move_map_["1"] = std::pair<unsigned int, unsigned int>(0,0);
    move_map_["2"] = std::pair<unsigned int, unsigned int>(0,1);
    move_map_["3"] = std::pair<unsigned int, unsigned int>(0,2);
    move_map_["4"] = std::pair<unsigned int, unsigned int>(1,0);
    move_map_["5"] = std::pair<unsigned int, unsigned int>(1,1);
    move_map_["6"] = std::pair<unsigned int, unsigned int>(1,2);
    move_map_["7"] = std::pair<unsigned int, unsigned int>(2,0);
    move_map_["8"] = std::pair<unsigned int, unsigned int>(2,1);
    move_map_["9"] = std::pair<unsigned int, unsigned int>(2,2);

    // Initialize starting valid moves
    valid_moves_ = {"1", "2", "3",
                    "4", "5", "6",
                    "7", "8", "9"};

}



// TicTacToe instruction print
void TicTacToe::PrintInstructions() const {
    std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << "                                                Welcome to TicTacToe!                                   " << std::endl;
    std::cout << "        Guide                                                                                           " << std::endl;
    std::cout << "    ━━━━━━━━━━━━━       A board has been given to the left to guide inputs into the terminal for each   " << std::endl;
    std::cout << "    ┃ 1 ┃ 2 ┃ 3 ┃     player's move choice. Your game will end with a stalemate (board is filled with   " << std::endl;
    std::cout << "    ━━━━━━━━━━━━━     no winner or player has gotten three of their pieces in a row.                    " << std::endl;
    std::cout << "    ┃ 4 ┃ 5 ┃ 6 ┃                                                                                       " << std::endl;
    std::cout << "    ━━━━━━━━━━━━━     Player 1 = X                                                                      " << std::endl;
    std::cout << "    ┃ 7 ┃ 8 ┃ 9 ┃     Player 2 = O                                                                      " << std::endl;
    std::cout << "    ━━━━━━━━━━━━━                                                                                       " << std::endl;
    std::cout << "                        Invalid inputs are any inputs that are not a number on the given \"Guide\" board  " << std::endl;
    std::cout << "                      or numbers from the \"Guide Board\" that have already been used by any player.      " << std::endl;
    std::cout << "                                                                                                        " << std::endl;
    std::cout << "                                                        Enjoy!                                          " << std::endl;
    std::cout << "                                                                                    coded by Jesse Brown" << std::endl;
    std::cout << "--------------------------------------------------------------------------------------------------------" << std::endl;

}


// Standard board print that includes visual of the current board
void TicTacToe::PrintBoard() const {
    std::cout << "━━━━━━━━━━━━━" << std::endl;

    for (unsigned int i = 0; i < 3; ++i) {
        for (unsigned j = 0; j < 3; ++j) {
            if (j == 0)
                std::cout << "┃";
            std::cout << ' ' << board_[i][j] << ' ';
            std::cout << "┃";
        }
        std::cout << std::endl;
        std::cout << "━━━━━━━━━━━━━" << std::endl;
    }
}

// Printing error message function (Invalid move / Already occupied space)
void TicTacToe::PrintErrorMessage(const std::string& msg_type) {
    if (msg_type == "INVALID") {
        std::cout << RED << "------INVALID MOVE RECIEVED------" << RESET << std::endl;
        return;
    }

    if (msg_type == "OCCUPIED") {
        std::cout << RED << "------SPACE ALREADY OCCUPIED------" << RESET << std::endl;
        return; 
    }
}




bool TicTacToe::UseTurn(const std::string& move, char curr_player_char) {                   // TODO
    /*
        Check which position is the desired move
        to make sure it is available
            - if not available we throw 
    */

    // Invalid string
    if (move_map_.find(move) == move_map_.end()) {
        PrintErrorMessage("INVALID");
        return false;
    }

    
    unsigned int move_row = move_map_[move].first;
    unsigned int move_col = move_map_[move].second;

    // Check for the space occupation
    if (board_[move_row][move_col] != ' ') {
        PrintErrorMessage("OCCUPIED");
        return false; 
    }

    // Set character at position
    board_[move_row][move_col] = curr_player_char;

    // Remove from valid spaces to for next turns
    valid_moves_.erase(std::remove(valid_moves_.begin(), valid_moves_.end(), move), valid_moves_.end());


    // Board has been filled up
    if (valid_moves_.empty())
        valid_game_flag_ = false;

    // Eventually call a function like check for winner here
    // CheckForWinner(); 

    return true;

}


char TicTacToe::NextPlayerCharacter() {
    if (next_player_) {
        // Player 2 case
        next_player_ = false;       // Switch
        return 'O';
    }
    // PLayer 1 case
    next_player_ = true;            // Switch
    return 'X';  
}


bool TicTacToe::GameValid() const {
    return valid_game_flag_;
}

std::vector<std::string> TicTacToe::GetValidMoves() const {
    return valid_moves_;
}


