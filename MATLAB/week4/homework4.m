close all
clc 
close all

% l_2
Data = dlmread('Data_Corr.txt');
m = length(Data);
n = 5;
A = [ones(m, 1), Data(:,1), Data(:,1).^2, Data(:,1).^3, Data(:,1).^4];
b = Data(:,2);
x_ls = A\b

% x_ls = [3.1052; 6.8643; 3.9999; -0.9754; -0.0047]
