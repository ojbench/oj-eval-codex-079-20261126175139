# Implementation

Each dynamically allocated node stores one integer and a pointer to its immediate
successor. A sentinel simplifies changes at the front, including insertion at
position zero. Erased nodes are deleted immediately; the destructor frees all
remaining nodes.

Pair swapping reconnects two adjacent nodes and advances to the next pair.
Prefix movement splits the list conceptually into a prefix A of length i,
a following block B of length x, and the remaining suffix C. Three pointer
updates turn A-B-C into B-A-C. Both operations use constant extra space.

Initialization takes O(n) time. Insertion, deletion, and queries take O(i) time;
pair swapping and printing take O(L) for current length L; prefix movement takes
O(i+x). Node storage is O(L), with O(1) auxiliary space for every operation.

# Validation

- Build: `cmake . && make`
- Randomized reference comparison: `python3 tests/check.py ./code`
- 200 deterministic random cases, each with 1,000 operations, passed both the
  normal build and an AddressSanitizer/UndefinedBehaviorSanitizer build.
- Cases include empty lists, odd/even lengths, zero-length moves, moves to the
  end, front insertion, and minimum/maximum signed integer values.
- The README sample output matched exactly.
- The advertised `/workspace/data/079/data_test/` directory was unavailable.
