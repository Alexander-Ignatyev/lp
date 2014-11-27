clear;
clc;
close all;


% # Problem Sets 5: Question 3
% # MAX-SAT problem
% 
% param m := 5;
% param n := 3;
% 
% var x{j in 1..n} binary;
% var y{i in 1..m} binary;
% maximize obj: sum{i in 1..m} y[i];
% C1: x[1] + x[2] + (1-x[3]) >= y[1];
% C2: x[1] + x[2] + x[3] >= y[2];
% C3: x[1] + (1-x[2]) + (1-x[3]) >= y[3];
% C4: x[1] + (1-x[2]) + x[3] >= y[4];
% C5: (1-x[1]) >= y[5];
% 
% solve;
% display obj;
% display y;
% display x;
% end;

A = [1 1 -1;
    1 1 1;
    1 -1 -1;
    1 -1 1;
    -1 0 0];
[m, n] = size(A);

A_big = -[A -eye(m)];

f = [zeros(n, 1); ones(m, 1)];
b = -(zeros(m, 1) - sum (A < 0, 2));
intcon = [1:(m+n)]';
lb = zeros(m+n, 1);
ub = ones(m+n, 1);

[x, fval] = intlinprog(-f, intcon, A_big, b, [], [], lb, ub);
fval = -fval
x = x(n+1:n+m)
