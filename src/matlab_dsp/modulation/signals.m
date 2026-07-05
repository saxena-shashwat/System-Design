uImplsIn = linspace(0, 10, 1000);
uImplsOut = (uImplsIn > 4.99) & (uImplsIn < 5.001);

expIn = linspace(0, 10, 1000);
expConst = 0.8;
expOut = expConst .^ expIn;

sqImplsIn = linspace(0, 10, 1000);
sqImplsOut = (sqImplsIn > 4) & (sqImplsIn < 5);

rampIn = linspace(0, 10, 1000);
rampConst = 5;
rampOut = rampIn;

figure(1)
subplot(2, 2, 1);
plot(uImplsIn, uImplsOut);
axis([-0.5 10.5 -0.5 1.5]);
title('Unit Imulse');
xlabel('Time');
ylabel('Amplitude');

subplot(2, 2, 2);
plot(sqImplsIn, sqImplsOut);
axis([-0.5 10.5 -0.5 1.5]);
title('Square Pulse');
xlabel('Time');
ylabel('Amplitude');

subplot(2, 2, 3);
plot(rampIn, rampOut);
axis([-0.5 10.5 -0.5 11]);
title('Unit Ramp');
xlabel('Time');
ylabel('Amplitude');

subplot(2, 2, 4);
plot(expIn, expOut);
axis([-0.5 10.5 -0.5 1.5]);
title('Exponential Decay');
xlabel('Time');
ylabel('Amplitude');