#pragma once

#include <cstdint>
#include <array>

namespace rlchess::bb {

using Bitboard = uint64_t;

constexpr Bitboard kFileA = 0x0101010101010101ULL;
constexpr Bitboard kFileH = 0x8080808080808080ULL;
constexpr Bitboard kNotFileA = ~kFileA;
constexpr Bitboard kNotFileH = ~kFileH;

constexpr Bitboard north(Bitboard b) noexcept { return b << 8; }
constexpr Bitboard south(Bitboard b) noexcept { return b >> 8; }
constexpr Bitboard east(Bitboard b) noexcept { return (b & kNotFileH) << 1; }
constexpr Bitboard west(Bitboard b) noexcept { return (b & kNotFileA) >> 1; }

constexpr Bitboard north_east(Bitboard b) noexcept { return (b & kNotFileH) << 9; }
constexpr Bitboard north_west(Bitboard b) noexcept { return (b & kNotFileA) << 7; }
constexpr Bitboard south_east(Bitboard b) noexcept { return (b & kNotFileH) >> 7; }
constexpr Bitboard south_west(Bitboard b) noexcept { return (b & kNotFileA) >> 9; }

// Pre-computed knight attacks for each square.
class KnightTable {
public:
    constexpr KnightTable() : table{} {
        for (int sq = 0; sq < 64; ++sq) {
            Bitboard b = Bitboard(1) << sq;
            Bitboard moves = 0;
            moves |= north(north_east(b));
            moves |= north(north_west(b));
            moves |= south(south_east(b));
            moves |= south(south_west(b));
            moves |= east(north_east(b));
            moves |= east(south_east(b));
            moves |= west(north_west(b));
            moves |= west(south_west(b));
            table[sq] = moves;
        }
    }
    constexpr Bitboard operator[](int sq) const noexcept { return table[sq]; }
private:
    Bitboard table[64];
};

inline constexpr KnightTable kKnightAttacks{};

} // namespace rlchess::bb
