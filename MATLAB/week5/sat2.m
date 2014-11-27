clear;
clc;
close all;

% # infeasible SAT problem

% var x{j in 1..4} binary;

% maximize obj: 0;
% c1: x[1] + (1-x[4]) +x[2] >= 1;
% c2: (1-x[1]) + (1-x[4]) +x[2] >= 1;
% c3: x[4] + x[2] >= 1;
% c4: (1-x[2]) >= 1;

% solve;
% display x;
% end;

A = -[1 1 0 -1;
    -1 1 0 -1;
    0 1 0 1;
    0 -1 0 0];
[m, n] = size(A);
f = zeros(n, 1);
% b = -([1; 1; 1; 1] - [1; 2; 0; 1]);
b = -(ones(m, 1) - sum (A < 0, 2));
intcon = [1:n]';
lb = zeros(n, 1);
ub = ones(n, 1);

x = intlinprog(f, intcon, A, b, [], [], lb, ub)
