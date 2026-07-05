clc, clear

w = pi/60;
A = [cos(w) -sin(w); sin(w) cos(w)];
B = [0; 1];
C = [1 0];

s = zeros(1000, 2);

s(1, :) = [0 1];

for i=1:999
    s(i+1, :) = s(i, :)*A;
end

disp(s);

scatter(s(:, 1), s(:, 2), 'filled')
axis([-1.5 1.5 -1.5 1.5]);