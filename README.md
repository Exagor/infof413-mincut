# INFOF413 Assignment 2: Karger's Algorithm

Alexandre Achten, December 2024

## Introduction

While the best deterministic algorithm to solve the minimum cut problem runs in $\mathcal{O}(nm+n^2\log{n})$ \cite{stoer-wagner}, the use of randomized methods can speed things up and find a minimum cut with high probability in only $\mathcal{O}(n^2 \log{n})$.The algorithms will be tested over different graph families\\
The goal of this project is to experimentally verify the success probability of the Contraction Algorithm and the FastCut Algorithm. Then the theoretical time complexity of both algorithms will be verified.

## Mincut

Let $G( V, E)$ be an undirected multigraph with $n$ vertices and $m$ edges. A multigraph is permitted more than one edge between any given pair of vertices. A cut in $G$ is a partition of the vertices $V = (C, \bar{C})$ into two non-empty sets ; we refer to this as the cut $C$ with the understanding that $\bar{C}$ is $V$\textbackslash$C$.
The value or size of a cut C is the number of edges crossing the cut, i.e.,
edges with one end-point in each of the two sets $C$ and $\bar{C}$. A multiple edge will contribute its multiplicity to the value of the cut. A min-cut is a cut of minimum value; the min-cut problem is that of finding a min-cut in an input graph $G$

## How to use ?

Type in your terminal at the root of the project:

```bash
make
```
To compile and run every tests.

Then use the python files in the `analyze` folder to generate the plots.
