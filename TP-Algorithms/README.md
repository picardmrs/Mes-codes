# Advanced Algorithms — Lab Work (TP)

My lab work (TPs) for the Advanced Algorithms course at ENSICAEN (1st year), written in C.

## Contents

| Folder | Topic |
|---|---|
| `utils/` | Shared helper functions |
| `list/` | Linked list |
| `queue/` | Queue |
| `stack/` | Stack |
| `heap/` | Binary heap / priority queue |
| `hashtable/` | Hash table |
| `bst/` | Binary search tree |
| `rBST/` | Randomized binary search tree |
| `redBlackBST/` | Red-black tree |
| `graph/` | Graphs |
| `spanningtree/` | Minimum spanning tree (Prim) — *work in progress, does not compile yet* |
| `dag/` | Topological sort on a DAG — *work in progress, does not compile yet* |
| `unit_tests/` | Unit tests for `list`, `heap` and `hashtable` |

## Build and run

Requirements: `gcc` and `make` (Linux or macOS).

Build everything from the root folder:

```bash
make          # cleans, then builds every lab
make clean    # removes object files and executables
```

Or build a single lab, e.g. the heap:

```bash
cd heap
make
./testHeap
```

Each folder produces a `test...` executable (`testList`, `testqueue`, `teststack`, `testHeap`, `testHashtable`, `testbst`, `testrbst`, `testrbbst`, `testgraph`, ...).

## Unit tests

The unit tests also check for memory leaks, so they need `valgrind` (Linux).

```bash
cd unit_tests/heap        # or unit_tests/list, unit_tests/hashtable
make
./unittest
```

`make clean` removes the executable and the generated `log-*` / `score-*` files.
