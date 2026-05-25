//
// Created by mfbut on 5/10/2026.
//

#ifndef ECS36BBATTLESHIPHUMANSONLY_BOARDCELL_H
#define ECS36BBATTLESHIPHUMANSONLY_BOARDCELL_H
#include <optional>

namespace BattleShip {
    /**
     * Represents a single spot on a battleship board
     */
    class BoardCell {
    public:

        BoardCell();

        virtual ~BoardCell() = default;

        //getters

        [[nodiscard]] bool has_been_fired_at() const;

        [[nodiscard]] bool has_ship() const;

        [[nodiscard]] std::optional<char> ship() const;

        //setters

        void add_ship(char ship);

        void mark_as_fired_at();

    private:

        std::optional<char> ship_;
        bool has_been_fired_at_;

    };
} // BattleShip

#endif //ECS36BBATTLESHIPHUMANSONLY_BOARDCELL_H
