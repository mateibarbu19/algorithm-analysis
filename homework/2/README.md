# Homework 2 - Algorithm Analysis

Disclaimer: The initial infrastructure of this code is the intellectual property
of the Algorithm Analysis Team.

## Polynomial reduction

The project contains the following classes:

* Task1
  * Reduces k-Coloring problem to SAT
  * It uses n * k variables X {i, j} = node i has the color j? which make up the
    formula F
  * We know that each node has at least one color => \/ after j from X {i, j}
  * But each node cannot have two colors => For j, t !X {i, j} /\ !X {i, t}
  * The nodes at the ends of the edges cannot have the same color => (u, v) in E
    !X{u, j} /\ !X{v, j} for any color j
  * Thus, if k-Color(G, k) = 1 <=> SAT(F) = 1
  * The complexity of the reduction is Theta(N * K ^ 2 + K * M), so O (N ^ 3),
    because K can be of the order of N, and M is of the order of M ^ 2.
* Task2
  * I reduced the problem of k-Clique to SAT using the pergament in the
    homework, exactly.
  * The complexity of the reduction is Theta(N ^ 2 * K ^ 2), in the case most
    unfavorable O(N ^ 4), because K can be of the order of N.
* Task3
  * I reduced the problem k-Cover to k-Clique using lemma 3.4 from Introducere
    in Algoritmi, C. Giumale, page 118. It says that a graph has a k-Cover if
    and only if the complementary graph has a (n-k)-clique.
  * The complexity of the reduction is Theta(N ^ 2 + log(N) * (M_compl ^ 2 +
    C_Task2)), where C_Task2 is the complexity of a solve call for task 2, so
    the most unfavorable O(log(N) * (N ^ 2 + C_Task2)) because the number of
    edges in the complementary graph is of the order of N ^ 2.
* Bonus
  * I used in variables of the form X{i} = family i and should be arrested?
    (Will the node be part of the cover?)
  * Thus we use m clauses that say that at least one family belonging to an edge
  must be arrested => X {i} \/ X {j} with (i, j) in E
  * Then I assigned a cost of 1 for each family not to be arrested, to maximize
    the number of families released
  * The complexity of the reduction is Theta(N + M), in the case of the most
  unfavorable O(N ^ 2).