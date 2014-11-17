# Problem Sets 5: Question 1
# Consider the following 3-SAT instance with 3 Boolean variables x1,x2,x3 and 5 clauses C1,…,C5:
# (x1 OR x2 OR ¬x3)
# (x1 OR x2 OR x3)
# (x1 OR ¬x2 OR ¬x3)
# (x1 OR ¬x2 OR x3)
# (¬x1)
# Use an ILP solver to check if the constraints are satisfiable. Type "SAT" if you find that they are satisfiable and type "UNSAT" otherwise.

var x{j in 1..3} binary;
maximize obj: 0;
C1: x[1] + x[2] + (1-x[3]) >= 1;
C2: x[1] + x[2] + x[3] >= 1;
C3: x[1] + (1-x[2]) + (1-x[3]) >= 1;
C4: x[1] + (1-x[2]) + x[3] >= 1;
C5: (1-x[1]) >= 1;

solve;
display x;
end;
