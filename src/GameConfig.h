//
// Created by mfbut on 4/24/2026.
//

#ifndef ECS36B_03_BATTLESHIP_HUMANSONLY_SOLUTION_GAMECONFIG_H
#define ECS36B_03_BATTLESHIP_HUMANSONLY_SOLUTION_GAMECONFIG_H

#include <map>
#include <istream>

namespace BattleShip {
    /**
     * Represents the configuration of the game
     */
    class GameConfig {
    public:
        GameConfig(int board_nums_rows, int board_num_cols, const std::map<char, int>& ship_healths);

        explicit GameConfig(std::istream& in);

        //getters

        [[nodiscard]] int board_num_rows() const;

        [[nodiscard]] int board_num_cols() const;

        [[nodiscard]] std::map<char, int> ship_healths() const;

    private:
        int board_num_rows_, board_num_cols_;
        std::map<char, int> ship_healths_;
    };
} // BattleShip

#endif //ECS36B_03_BATTLESHIP_HUMANSONLY_SOLUTION_GAMECONFIG_H
