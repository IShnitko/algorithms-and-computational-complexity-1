# Algorithms and Computational Complexity - Project 1

[![C++](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)

This repository contains the implementation and analysis of sorting algorithms as part of the *Algorithms and Computational Complexity* course project. The goal is to study the efficiency of different algorithms (Insertion Sort, Heap Sort, Quick Sort) under varying conditions, such as input size, data types, and initial data distribution.

## 📋 Project Overview

### Key Features:
- **Implemented Algorithms**:
  - **Insertion Sort** (Standard and Binary variants)
  - **Heap Sort**
  - **Quick Sort** (with configurable pivot selection strategies)
- **Data Types Support**: `int`, `float`, `char` (using C++ templates).
- **Input Scenarios**:
  - Randomly generated arrays
  - Already sorted (ascending/descending)
  - Partially sorted (33% and 66% pre-sorted)
- **Performance Metrics**:
  - Average execution time over 100 trials
  - Detailed analysis of time complexity trends

### Requirements:
- **C++17** compatible compiler (tested with GCC 10+, Clang 12+)
- **CMake 3.12+** (for building)

## 🚀 Getting Started

### Build Instructions:
1. Clone the repository:
   ```bash
   git clone https://github.com/IShnitko/algorithms-and-computational-complexity-1.git
   cd algorithms-and-computational-complexity-1
   ```
2. Build with CMake:
```bash
  mkdir build && cd build
  cmake ..
  make
```

### Usage:
To run the program with desired parameters update the existing config/config.txt file.

## 📊 Experiment Design

### Methodology:
1. **Data Generation**:
   - Arrays are dynamically allocated.
   - Input distributions are regenerated for each trial to avoid bias.
2. **Time Measurement**:
   - Uses `std::chrono::high_resolution_clock`.
   - Excludes data generation and validation steps.
3. **Validation**:
   - Post-sort checks ensure correct ordering.
   - Debug mode allows visualization of small arrays.

For detailed results, see the [project report](AiZO-P1-IShnitko.pdf).

## 📂 Repository Structure
```
├── CMakeLists.txt          # Build configuration
├── src/                    # Source code
│   ├── algorithms/         # Sorting algorithm implementations
│   ├── utils/              # Data generation and validation
│   └── main.cpp            # Entry point
├── data/                   # Sample input files
├── docs/                   # Report and visualizations
└── tests/                  # Validation tests
```

## 🤝 Contributing
Contributions are welcome! Please open an issue or submit a pull request for:
- Bug fixes
- Additional algorithms (e.g., Shell Sort)
- Optimization suggestions

## 📜 License
This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.


