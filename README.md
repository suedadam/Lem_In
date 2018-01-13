# Lem_In
The following is my attempt at documenting my progress through this project. 

***

### Bhandari's algorithm:
- [Disjoint paths paper](https://fernandokuipers.nl/papers/Wiley.pdf)
- [My notes on finding 2 optimal routes](Notes/BellmanFordMoore.pdf)
	- 2nd page of the PDF on my notes demonstrates Bhandri's algorithm finding 2 optimal routes for the ants to traverse on. 
	- The first graph demonstrates Bellman-Ford-Moore's algorithm being utilized (under the pre-established shortest path of _A->E->D->H_ from Dijkstra's algorithm) from which we find the optimal path to H is _A ~> G -> H_ which expands to _A->B->C->D->E->F->G->H_. 
	- The 2nd graph demonstrates how to use the result we found in Bhandri's algorithm which simply restores the direction of the shortest path and adds the shortest paths found. In turn we find that E -> D in our shortest path (Dijkstra's) cancels out the path D -> E which we found from Bellman-Ford-Moore's algorithm. From this we then have 2 optimal paths with no bottlenecks. _A -> B -> C -> D -> H_ and _A -> E -> F -> G -> H_.
### Bellman-Ford(-Moore) algorithm:
- [MIT lecture presentation](https://courses.csail.mit.edu/6.006/spring11/lectures/lec15.pdf)

#### Relaxation
- [My notes for Relaxation Condition/Algorithm](Notes/relaxation_condition.pdf)
- [Resource on Relaxation Equation](https://brilliant.org/wiki/bellman-ford-algorithm/#relaxation-equation)

#### Negative Cycles 
- [Negative Cycles Lecture (Not very informative)](http://eniac.cs.qc.cuny.edu/andrew/csci700/lecture18.pdf)
=======
### Bellman-Ford(-Moore) algorithm:
#### Relaxation
- ![My notes for Relaxation Condition/Algorithm](relaxation_condition.pdf "Relaxation Condition/Algorithm Notes")
- ![Resource on Relaxation Equation](https://brilliant.org/wiki/bellman-ford-algorithm/#relaxation-equation)
