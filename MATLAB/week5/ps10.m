clear;
clc;
close all;

% # Problem Sets 5: Question 10
% # A county has 'n' towns.
% # A corporation wishes to build supermarkets to serve the people in the county.
% # For each town, the corporation can choose to or not to build a super market there.
% # No town can have more than one super-market.
% # We would like to minimize the total cost of super-markets built.
% # Table 'costs' shows the cost of built for each town.
% # Each town must have a super-market within a 'max_distance' minute driving time.
% # The table 'distance_matrix' shows the driving times between the towns.
% 
% param n;
% 
% param costs{j in 1..10};
% 
% param max_distance;
% 
% param distance_matrix {i in 1..n, j in 1..n};
% 
% param mask_matrix {i in 1..n, j in 1..n} :=
%     if distance_matrix[i, j] <= max_distance then 1 else 0;
% 
% var x {j in 1..n} binary;
% 
% minimize total_cost: sum {j in 1..n} x[j] * costs[j];
% c{i in 1..n}: sum {j in 1..n}  mask_matrix[i,j]*x[j] >= 1;
% 
% solve;
% 
% display total_cost;
% display x;
% end;
% 
% data;
% 
% # number of cities
% param n := 7;
% 
% param costs :=
% 1 12
% 2 8
% 3 12
% 4 10
% 5 9
% 6 10
% 7 7;
% 
% param max_distance := 20;
% 
% param distance_matrix :
%   1   2   3   4  5   6    7 :=
% 1 0 19 18 22 13 31 23
% 2 19 0 17 22 23 14 32
% 3 18 17 0 14 21 31 32
% 4 22 22 14 0 29 13 17
% 5 13 23 21 29 0 22 19
% 6 31 14 31 13 22 0 26
% 7 23 32 32 17 19 26 0;
% 
% end;


max_distance = 20;
distance_matrix = [0 19 18 22 13 31 23;
    19 0 17 22 23 14 32;
    18 17 0 14 21 31 32;
    22 22 14 0 29 13 17;
    13 23 21 29 0 22 19;
    31 14 31 13 22 0 26;
    23 32 32 17 19 26 0;];
n = length(distance_matrix);

f = [12; 8; 12; 10; 9; 10; 7];
b = ones(n, 1);
mask_matrix = distance_matrix <= max_distance;
intcon = [];
for i=1:n
    intcon(i) = i;
end

lb = zeros(n, 1);
ub = ones(n, 1);

[x, total_cost] = intlinprog(f, intcon, -mask_matrix, -b, [], [], lb, ub);
total_cost
x
