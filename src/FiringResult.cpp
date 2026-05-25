//
// Created by mfbut on 5/10/2026.
//

#include "FiringResult.h"

namespace BattleShip {
    FiringResult::FiringResult() : ship_hit_(), ship_was_destroyed_(false) {
    }

    /**
     * Check if the shot that was fired hit this ship
     * @return : whether the shot hit a ship or not
     */
    bool FiringResult::is_hit() const {
        return ship_hit_.has_value();
    }

    /**
     * Check if the shot that was fired destroyed a ship
     * @return : whether the shot destroyed a ship or not
     */
    bool FiringResult::was_ship_destroyed() const {
        return ship_was_destroyed_;
    }

    /**
     * Get the ship that was hit if there is one
     * @return : an optional containing the ship that was hit
     * or an empty optional if no ship was hit
     */
    const std::optional<char>& FiringResult::get_ship_hit() const {
        return ship_hit_;
    }


    /**
     * Set the name of the ship that was hit
     * @param ship_name : the name of the ship hit
     */
    void FiringResult::set_ship_hit(const char ship_name) {
        ship_hit_.emplace(ship_name);
    }

    /**
     * Set whether the ship was destroyed or not
     * @param is_destroyed : whether the ship was destroyed or not
     */
    void FiringResult::set_ship_was_destroyed(const bool is_destroyed) {
        ship_was_destroyed_ = is_destroyed;
    }
} // BattleShip
