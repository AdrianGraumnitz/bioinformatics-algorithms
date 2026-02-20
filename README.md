# Bioinformatics Algorithms (C++)

This repository contains C++ implementations of classic bioinformatics
algorithms, developed during my studies in Bioinformatics at Freie
Universität Berlin.

The focus is on **clear algorithmic structure**, **correctness**, and
**educational value**, rather than on external libraries or frameworks.

------------------------------------------------------------------------

## Implemented Algorithms

### 🔹 Q-Gram Index

An index structure for efficient exact string matching, implemented
using:

-   Rolling hash (2-bit encoding for DNA alphabet `{A, C, G, T}`)
-   Counting sort
-   Prefix sum (cumulative directory array)

**Features:** - Configurable q-gram length - Efficient bucket-based hit
retrieval - Clean separation of hashing, counting, and index
construction

**Location:**

    qgram-index/

------------------------------------------------------------------------

### 🔹 Sequence Alignment

Implementation of classical dynamic programming algorithms for pairwise
sequence alignment:

-   Needleman--Wunsch (global alignment)
-   Smith--Waterman (local alignment)

**Features:** - Configurable scoring (match, mismatch, gap) - Full DP
matrix construction - Traceback reconstruction - Alignment
visualization - Clean separation between interface and implementation

**Location:**

    alignment/

------------------------------------------------------------------------

## Project Structure

    bioinformatics-algorithms/
    ├── qgram-index/
    │   ├── QGramIndex.hpp
    │   ├── QGramIndex.cpp
    │   ├── QGramIndex_main.cpp
    │   └── a5_util.*
    ├── alignment/
    │   ├── Alignment.hpp
    │   ├── Alignment.cpp
    │   └── Alignment_main.cpp
    ├── README.md

Each algorithm is implemented independently in its own subdirectory.

------------------------------------------------------------------------

## Author

Adrian Graumnitz\
Bioinformatics student, Freie Universität Berlin

------------------------------------------------------------------------

## License

This repository is intended for academic and educational use.
