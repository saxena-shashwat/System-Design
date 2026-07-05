clc, clear

x = randi([0 1], 10, 1)
s = zeros(11, 1)

for i = 1:10
    s(i+1) = (x(i) == 1);
end

disp(x);
disp(s);
hold on
scatter(1:1:10, x);
scatter(1:1:11, s, "filled");
axis([-0.5 12 -0.5 1.5]);