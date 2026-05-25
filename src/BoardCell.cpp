//
// Created by mfbut on 5/10/2026.
//

#include "BoardCell.h"

namespace BattleShip {
    /**
     * Create an empty board cell
     */
    BoardCell::BoardCell() : ship_(), has_been_fired_at_(false) {
    }

    /**
     * Check if this cell has been fired at
     * @return : whether this cell has been fired at or not
     */
    bool BoardCell::has_been_fired_at() const {
        return has_been_fired_at_;
    }

    /**
     * Check if ship occupies this cell
     * @return : whether a ship occupies this cell or not
     */
    bool BoardCell::has_ship() const {
        return ship_.has_value();
    }

    /**
     * Get the ship that occupies this cell if there is one
     * @return : an optional containing the ship if there is
     * a ship on this cell, otherwise an empty optional
     */
    std::optional<char> BoardCell::ship() const {
        return ship_;
    }

    /**
     * Add a ship to this cell
     * @param ship : the character used to represent this ship
     */
    void BoardCell::add_ship(char ship) {
        ship_.emplace(ship);
    }

    /**
     * Mark this cell as having been fired at
     */
    void BoardCell::mark_as_fired_at() {
        has_been_fired_at_ = true;
    }
} // BattleShip
