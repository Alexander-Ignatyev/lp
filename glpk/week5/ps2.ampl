# Problem Sets 5: Question 2
# first approach to MAX-SAT problem
# see in ps3.ampl completed MAX-SAT problem

var x{j in 1..3} binary;
var z binary;
maximize obj: z;
C1: x[1] + x[2] + (1-x[3]) >= z;
C2: x[1] + x[2] + x[3] >= 1;
C3: x[1] + (1-x[2]) + (1-x[3]) >= 1;
C4: x[1] + (1-x[2]) + x[3] >= 1;
C5: (1-x[1]) >= 1;

solve;
display z;
end;
