% different signals and how to use them in matlab

% unit step (@ x = 0)
x = linspace(-10, 10);
u = (x>=0);

figure(1)
plot(x,u);
title('unit step');
axis([-10, 10, -1, 1.5]);

% unit impulse (@ x = 0)
x = linspace(-10, 10);
u = (x == 0);

figure(2)
plot(x, u);
title('unit impulse');
axis([-10 10 -1 1.5]);

% ramp (by a factor of a = 5) (@ x = 0)
x = linspace(-10, 10);
a = 5;
u = a .* (x >= 0);

figure(3)
plot(x, u);
title('ramp');
axis([-10 10 -1 6]);

% exponential (a = 0.8)
x = linspace(0, 20);
a = 0.8;
f = a.^x;

figure(4)
plot(x, f);
title('exponential');
axis([0 20 0 1]);



% square wave
x = linspace(0, 10, 1000);
a = double((sin(pi*x)>=0));

figure(5)
plot(x, a);
title('square wave');
axis([0 10 -0.5 1.5]);


% square pulse
x = linspace(0, 10, 1000);
p = (x>2) & (x<5);

figure(6);
plot(x, p);
title('square pulse');
axis([0 10 -0.5 1.5]);