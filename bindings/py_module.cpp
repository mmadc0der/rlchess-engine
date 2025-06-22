#include <pybind11/pybind11.h>
#include "rlchess/board.hpp"

namespace py = pybind11;
using rlchess::Board;

PYBIND11_MODULE(rlchess_engine, m) {
    m.doc() = "RLChess C++ engine bindings";

    py::class_<Board>(m, "Board")
        .def(py::init<>())
        .def(py::init<const std::string &>(), py::arg("fen"))
        .def("fen", &Board::fen, "Returns FEN representation of the position")
        .def("to_string", &Board::to_string)
        .def("__str__", &Board::to_string);
}
