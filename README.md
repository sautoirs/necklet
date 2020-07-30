# Necklet

![C/C++ CI](https://github.com/sautoirs/necklet/workflows/C/C++%20CI/badge.svg)

A bunch of code kata to practice TDD in C.

## Usage

```bash
# Build the test runner
cmake -S . -B build -G Ninja
cmake build -DBUILD_TESTING=ON
cmake --build build

# Run the tests
./build/tests/unit/Runner
```

