//
// Created by mfbut on 4/24/2026.
//

#ifndef ECS36BBATTLESHIPHUMANSONLY_BOARD_H
#define ECS36BBATTLESHIPHUMANSONLY_BOARD_H

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "ShipPlacement.h"
#include "BoardCell.h"

namespace BattleShip {

    /**
     * A representation of a player's board
     */
    class Board {
    public:
        Board(const int num_rows, const int num_cols,
              const char blank_char = '*',
              const char hit_marker = 'X',
              const char miss_marker = 'O');

        virtual ~Board() = default;

        //checks and accesses to the board at a specific location

        [[nodiscard]] const BoardCell& at(int row, int col) const;

        [[nodiscard]] BoardCell& at(int row, int col);

        [[nodiscard]] bool has_been_fired_at(int row, int col) const;

        void mark_as_fired_at(int row, int col);

        [[nodiscard]] bool is_on(const int row, const int col) const;

        [[nodiscard]] bool has_ship_at(int row, int col) const;

        [[nodiscard]] std::optional<char> get_ship_at(int row, int col) const;

        void add_ship_at(char ship, int row, int col);

        [[nodiscard]] bool are_no_ships_between(const std::pair<int, int> start,
                                                const std::pair<int, int> stop) const;
        //placing ships

        [[nodiscard]] bool can_ship_be_placed(const ShipPlacement& placement) const;

        void place_ship(const ShipPlacement& placement);

        // board dimensions

        [[nodiscard]] size_t num_rows() const;

        [[nodiscard]] size_t num_cols() const;

        //displaying a board

        [[nodiscard]] std::string view_as_hidden() const;

        [[nodiscard]] std::string view_as_visible() const;

    private:
        std::vector<std::vector<BoardCell> > contents;
        char blank_, hit_marker_, miss_marker_;
    };
} // BattleShip


#endif //ECS36BBATTLESHIPHUMANSONLY_BOARD_H
