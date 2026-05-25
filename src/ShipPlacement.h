//
// Created by mfbut on 5/7/2026.
//

#ifndef ECS36BBATTLESHIPHUMANSONLY_SHIPPLACEMENT_H
#define ECS36BBATTLESHIPHUMANSONLY_SHIPPLACEMENT_H

#include <utility>

#include "Orientation.h"

namespace BattleShip {
    /**
     * Represents where a ship will be placed on a board
     */
    class ShipPlacement {
    public:
        ShipPlacement(char ship_name, int start_row, int start_col, int end_row, int end_col);

        ShipPlacement(char ship_name, int ship_length, int start_row, int start_col, Orientation orientation);

        [[nodiscard]] Orientation orientation() const;

        [[nodiscard]] bool is_vertical() const;

        [[nodiscard]] bool is_horizontal() const;

        char ship_name;
        std::pair<int, int> start, stop;
    };
} // BattleShip

#endif //ECS36BBATTLESHIPHUMANSONLY_SHIPPLACEMENT_H
