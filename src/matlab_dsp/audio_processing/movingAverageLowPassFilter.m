time = linspace(0,1, 1000);
signal = sin(2*pi*time);

hf_noise = sin(2*pi*400*time);
noisy_signal = signal + 0.5 * hf_noise;

%{
moving average, states s, inputs x, output y, [0 1 0.5 0.5]
%}

s = zeros(length(time)+1, 1);
x = noisy_signal;
y = zeros(length(time), 1);

A = 0;
B = 1;
C = 0.5;
D = 0.5;

for n = 1:length(time)
    s(n+1) = A * s(n) + B * x(n);
    y(n) = C * s(n) + D * x(n);
end

hold on;
plot(time, noisy_signal);
plot(time, y);
xlabel('Time');
ylabel('Amplitude');
title('Moving Average Low Pass Filter')

hold off