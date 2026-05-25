//
// Created by mfbut on 5/7/2026.
//

#include "ShipPlacement.h"

namespace BattleShip {
    /**
     *
     * @param ship_name : the name of the ship to place
     * @param start_row : the row the ship starts in
     * @param start_col : the column the ship starts in
     * @param end_row : the row the ship ends in (inclusive)
     * @param end_col : the column the ship ends in (inclusive)
     */
    ShipPlacement::ShipPlacement(char ship_name, int start_row, int start_col, int end_row,
                                 int end_col) : ship_name(ship_name), start{start_row, start_col},
                                                stop{end_row, end_col} {
    }

    /**
     *
     * @param ship_name : the name of the ship to place
     * @param ship_length : how long the ship is
     * @param start_row : the row the ship starts in
     * @param start_col : the column the ship starts in
     * @param orientation : the orientation of the ship
     */
    ShipPlacement::ShipPlacement(const char ship_name, const int ship_length, int start_row, int start_col,
        const Orientation orientation) :ship_name(ship_name), start{start_row, start_col}, stop{start_row, start_col} {
        if (orientation == Orientation::HORIZONTAL) {
            stop.second = start.second + ship_length - 1;
        }else if (orientation == Orientation::VERTICAL) {
            stop.first = start.first + ship_length - 1;
        }
    }

    /**
     * Get the orientation of this ship
     * @return : the orientation of this ship
     */
    Orientation ShipPlacement::orientation() const {
        return start.first == stop.first ? Orientation::HORIZONTAL : Orientation::VERTICAL;
    }

    /**
     * Check if this ship is placed vertically or not
     * @return : if this ship is placed vertically or not
     */
    bool ShipPlacement::is_vertical() const {
        return orientation() == Orientation::VERTICAL;
    }

    /**
     * Check if this ship is placed horizontally or not
     * @return : if this ship is placed horizontally or not
     */
    bool ShipPlacement::is_horizontal() const {
        return orientation() == Orientation::HORIZONTAL;
    }
} // BattleShip
