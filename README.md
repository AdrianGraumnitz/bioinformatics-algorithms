# Bioinformatics Algorithms (C++)

This repository contains C++ implementations of classic bioinformatics algorithms,
developed during my studies in Bioinformatics at Freie Universität Berlin.

The focus is on **clear algorithmic structure**, **correctness**, and **educational value**,
rather than on external libraries or frameworks.

---

## Implemented Algorithms

### 🔹 Q-Gram Index
An index structure for efficient exact string matching, implemented using:

- Rolling hash (2-bit encoding for DNA alphabet `{A, C, G, T}`)
- Counting sort
- Prefix sum (cumulative directory array)

**Features:**
- Configurable q-gram length
- Efficient bucket-based hit retrieval
- Clean separation of hashing, counting, and index construction

**Location:**
/qgramindex
