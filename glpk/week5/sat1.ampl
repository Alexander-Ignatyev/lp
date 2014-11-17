# feasible SAT example

var x{j in 1..4} binary;

maximize obj: 0;
c1: x[1] + x[2] + (1-x[3]) >= 1;
c2: (1-x[2]) + (1-x[4]) + x[1] >= 1;
c3: x[1] + x[2] + (1-x[4]) >= 1;

solve;
display x;
end;
