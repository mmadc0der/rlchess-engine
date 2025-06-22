#pragma once

#include <string>
#include <string_view>
#include <array>
#include <cstdint>

namespace rlchess {

// Simple board representation using 64-square array.
// Parsing FEN is enough for initial experiments; bitboards/search will come later.
class Board {
public:
    Board();                                     // "startpos"
    explicit Board(std::string_view fen);        // parse custom FEN

    // Return the original (normalised) FEN string
    [[nodiscard]] std::string_view fen() const noexcept;

    // ASCII representation for easy debugging / __str__ in Python
    std::string to_string() const;

    // Equality for tests
    bool operator==(const Board &) const = default;

private:
    void from_fen(std::string_view fen);

    // Cached FEN (normalised). Keeps things simple for now.
    std::string fen_string_{};

    // 0-based square indexing: a1 = 0, h8 = 63. Empty squares contain '\0'.
    std::array<char, 64> squares_{};

    bool white_to_move_{};
    uint8_t castling_rights_{}; // bitmask: 1=K, 2=Q, 4=k, 8=q
    int8_t enpassant_file_{-1}; // file 0-7 or -1 if none
    uint16_t halfmove_clock_{};
    uint32_t fullmove_number_{};
};

} // namespace rlchess
