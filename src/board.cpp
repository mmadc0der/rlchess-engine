#include "rlchess/board.h"

#include <sstream>
#include <stdexcept>
#include <vector>
#include <cctype>

namespace rlchess {

namespace {
constexpr const char *STARTPOS_FEN =
    "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

// Helper to convert algebraic square (e.g. "e4") to 0-63 index (a1=0).
inline int square_index(const std::string &alg) {
    if (alg.size() != 2) return -1;
    char file = alg[0];
    char rank = alg[1];
    if (file < 'a' || file > 'h' || rank < '1' || rank > '8') return -1;
    int f = file - 'a';
    int r = rank - '1';
    return r * 8 + f;
}
} // namespace

Board::Board() { from_fen(STARTPOS_FEN); }

Board::Board(const std::string &fen) { from_fen(fen); }

const std::string &Board::fen() const { return fen_string_; }

std::string Board::to_string() const { return fen_string_; }

void Board::from_fen(const std::string &fen) {
    // Reset state
    squares_.fill('\0');
    castling_rights_ = 0;
    enpassant_file_ = -1;
    halfmove_clock_ = 0;
    fullmove_number_ = 1;
    white_to_move_ = true;

    std::istringstream ss(fen);
    std::string placement, active, castling, enpassant, halfmove, fullmove;
    if (!(ss >> placement >> active >> castling >> enpassant >> halfmove >> fullmove)) {
        throw std::invalid_argument("Invalid FEN: " + fen);
    }

    // 1) Piece placement
    int rank = 7, file = 0;
    for (char c : placement) {
        if (c == '/') {
            if (file != 8) throw std::invalid_argument("Invalid FEN rank length");
            rank--; file = 0;
            continue;
        }
        if (std::isdigit(static_cast<unsigned char>(c))) {
            file += c - '0';
        } else {
            if (file >= 8 || rank < 0) throw std::invalid_argument("Invalid FEN square index");
            int idx = rank * 8 + file;
            squares_[idx] = c;
            ++file;
        }
    }
    if (rank != 0 || file != 8) throw std::invalid_argument("Invalid FEN final rank");

    // 2) Active color
    white_to_move_ = (active == "w");

    // 3) Castling rights
    if (castling != "-") {
        for (char c : castling) {
            switch (c) {
            case 'K': castling_rights_ |= 1; break;
            case 'Q': castling_rights_ |= 2; break;
            case 'k': castling_rights_ |= 4; break;
            case 'q': castling_rights_ |= 8; break;
            default: throw std::invalid_argument("Invalid castling flag");
            }
        }
    }

    // 4) En-passant square
    if (enpassant != "-") {
        int idx = square_index(enpassant);
        if (idx == -1) throw std::invalid_argument("Invalid enpassant square");
        enpassant_file_ = idx % 8;
    }

    // 5) Halfmove clock
    halfmove_clock_ = static_cast<uint16_t>(std::stoi(halfmove));

    // 6) Fullmove number
    fullmove_number_ = static_cast<uint32_t>(std::stoul(fullmove));

    fen_string_ = placement + " " + active + " " + castling + " " + enpassant + " " + halfmove + " " + fullmove;
}

} // namespace rlchess
