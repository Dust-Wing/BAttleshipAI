//
// Created by mfbut on 4/24/2026.
//

#include "GameConfig.h"

#include <string>

namespace BattleShip {
    /**
     *
     * @param board_nums_rows : The number of rows on the board
     * @param board_num_cols : The number of columns on the board
     * @param ship_healths : a map from ship name to health/length
     */
    GameConfig::GameConfig(const int board_nums_rows, const int board_num_cols,
                           const std::map<char, int>& ship_healths) : board_num_rows_(board_nums_rows),
                                                                      board_num_cols_(board_num_cols),
                                                                      ship_healths_(ship_healths) {
    }

    /**
     * Create a game configuration from the istream. The values in the
     * istream should have the following structure
     * 1. Number of rows on the board
     * 2. Number of columns on the board
     * 3. Number of ships to be placed
     * 4. Ship1_Character Ship1_Size
     * 5. Ship2_Character Ship2_Size
     * 6. ...
     * @param in : the stream to read from
     */
    GameConfig::GameConfig(std::istream& in) : GameConfig(0, 0, {}) {
        in >> board_num_rows_;
        in >> board_num_cols_;
        int num_ships;
        in >> num_ships;

        std::string ship_name; // need to do a string to handle whitespace
        int ship_health;
        for (int i = 0; i < num_ships; ++i) {
            in >> ship_name;
            in >> ship_health;
            ship_healths_.insert({ship_name.front(), ship_health});
        }
    }

    /**
     * Get the number of rows the board should have
     * @return : the number of rows the board should have
     */
    int GameConfig::board_num_rows() const {
        return board_num_rows_;
    }

    /**
     * Get the number of columns the board should have
     * @return : the number of columns the board should have
     */
    int GameConfig::board_num_cols() const {
        return board_num_cols_;
    }

    /**
     * Get a mapping from ship name to length/health
     * @return : a map from ship name to length/health
     */
    std::map<char, int> GameConfig::ship_healths() const {
        return ship_healths_;
    }
} // BattleShip
