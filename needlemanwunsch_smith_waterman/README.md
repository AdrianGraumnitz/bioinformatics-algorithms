# Sequence Alignment (Needleman--Wunsch & Smith--Waterman)

This project implements classical dynamic programming algorithms for
pairwise sequence alignment:

-   Needleman--Wunsch (global alignment)
-   Smith--Waterman (local alignment)

The implementation focuses on clarity, correctness, and clean separation
between interface and implementation.

------------------------------------------------------------------------

## Files

    Alignment.hpp      → Class definition
    Alignment.cpp      → Algorithm implementation
    main.cpp           → Example usage / test driver

------------------------------------------------------------------------

## Features

-   Configurable scoring:
    -   match
    -   mismatch
    -   gap penalty
-   Global alignment (Needleman--Wunsch)
-   Local alignment (Smith--Waterman)
-   Traceback reconstruction
-   Alignment visualization

Output format:

    SEQ1_WITH_GAPS
    MATCH_MARKERS
    SEQ2_WITH_GAPS

Where: - `|` indicates a match - space indicates mismatch or gap

------------------------------------------------------------------------

## Build & Usage

### Compile

Example using `g++`:

``` bash
g++ -std=c++17 Alignment.cpp main.cpp -o Alignment
```

------------------------------------------------------------------------

### Run

``` bash
./Alignment
```

Parameters (match, mismatch, gap, local/global mode) are defined inside
`main.cpp`.

Example:

``` cpp
align.compute(match, mismatch, gap, local);
```

-   `local = false` → Needleman--Wunsch
-   `local = true` → Smith--Waterman

------------------------------------------------------------------------

## Algorithm Overview

### Needleman--Wunsch (Global)

-   Full matrix initialization with cumulative gap penalties
-   Traceback from bottom-right corner
-   Produces alignment over entire sequences

------------------------------------------------------------------------

### Smith--Waterman (Local)

-   Matrix initialized with zeros
-   Negative scores clipped to zero
-   Traceback starts at highest scoring cell
-   Stops at score 0 (HOME)

------------------------------------------------------------------------

## Notes

-   Ties in scoring are resolved deterministically.
-   If multiple local maxima exist, the first encountered maximum is
    used.
-   `getScore()` and `getAlignment()` require `compute()` to be called
    first.
-   Implementation prioritizes readability over memory optimization.
