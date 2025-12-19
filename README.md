# Graph Analyzer

C++ tool for calculating structural properties and coloring parameters of undirected graphs.

## 📋 Features

The program computes the following for  graphs:

1. **Degree Sequence**: Sorted list of vertex degrees.
2. **Connectivity**: Number of connected components (via DFS).
3. **Bipartiteness**: T/F check for 2-colorability.
4. **Coloring Algorithms**:
* **Greedy**: By vertex ID.
* **LF (Largest First)**: By degree (descending).
5. **Complement Edges**: Number of edges in the complement graph.

## 🛠 Implementation Details

* ** Calculation**: Uses common neighbor counting between pairs: .
* **SLF Logic**: Prioritizes vertices with the highest number of unique neighbor colors, then highest degree, then lowest ID.
* **Performance**: Uses custom `Vector` and `Stack` classes for efficiency. Sorting is handled via **Merge Sort** ().

## 📥 Input/Output

* **Input**: Number of graphs , followed by  and adjacency lists.
* **Output**: Values for all 8 parameters in order (sequences or T/F).

## 🚀 Usage

```bash
g++ -O3 main.cpp -o analyzer
./analyzer < input.txt

```

---
