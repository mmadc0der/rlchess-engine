# RLChess Engine

Experimental C++ chess engine intended for reinforcement-learning research. Provides a minimal pybind11 module (`rlchess_engine`) exposing core engine classes to Python for rapid experimentation.

## Building (stand-alone)
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

## Installing into Python
```bash
pip install -e .
```

This uses [scikit-build-core](https://github.com/scikit-build/scikit-build-core) to invoke CMake and produce an editable install.
