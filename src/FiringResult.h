//
// Created by mfbut on 5/10/2026.
//

#ifndef ECS36BBATTLESHIPHUMANSONLY_FIRINGRESULT_H
#define ECS36BBATTLESHIPHUMANSONLY_FIRINGRESULT_H
#include <optional>

namespace BattleShip {
    class FiringResult {
    public:
        /**
         * Represents the results of firing at a cell on a board
         */
        FiringResult();

        //getters

        [[nodiscard]] bool is_hit() const;

        [[nodiscard]] bool was_ship_destroyed() const;

        [[nodiscard]] const std::optional<char>& get_ship_hit() const;

        //setters

        void set_ship_hit(const char ship_name);

        void set_ship_was_destroyed(const bool is_destroyed = true);

    private:
        std::optional<char> ship_hit_;
        bool ship_was_destroyed_;
    };
} // BattleShip

#endif //ECS36BBATTLESHIPHUMANSONLY_FIRINGRESULT_H
