rng(42);
[source, fs] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramTrimmed.wav");

noise = 0.5 * randn(size(source));

N = length(noise);
X = fft(noise);
f = (0:N-1)*(fs/N);
fc = 15000;

mask = (f > fc & f < fs-fc);
X = X .* mask';

high_freq_noise = real(ifft(X));
noisy_signal = source + high_freq_noise;
noisy_signal = noisy_signal ./ max(noisy_signal);


subplot(2, 1, 1);
plot(abs(fft(source)));
title("source signal");
subplot(2, 1, 2);
plot(abs(fft(noisy_signal)));
title("signal with noise");


audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramStableNoise.wav", noisy_signal, fs);