## Build & Usage (Q-Gram Index)

### Compile

Example using `g++`:

```bash
g++ -std=c++17 QGramIndex.cpp QGramIndex_main.cpp a5_util.cpp -o QGramIndex_main
```

### Run

```bash
./QGramIndex_main <GENOME_FILE> <QUERY>
```

Example:

```bash
./QGramIndex_main mini.text GATTACA
```

Output:

```text
GATTACA: 7 0
```

---

## Notes

- The order of reported hit positions is undefined.
- The input alphabet is assumed to be `{A, C, G, T}`.
- Implementations prioritize clarity and correctness.
