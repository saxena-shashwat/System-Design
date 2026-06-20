rng(42);
[source, fs] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramTrimmed.wav");

noise = 0.1 .* randn(size(source));


N = round(0.9 * fs / 1000, TieBreaker = "odd");
n = 1:N-1;
M = (N-1) / 2;
fc = 10000;

lpfIR = (2 * fc/fs) .* sinc(2 * fc * (n-M) / fs);

noise = conv(noise, lpfIR);


noisy_signal = source + noise;
noisy_signal = noisy_signal ./ max(noisy_signal);


subplot(2, 1, 1);
plot(abs(fft(source)));
subplot(2, 1, 2);
plot(abs(fft(noisy_signal)));


audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramStableNoise.wav", noisy_signal, fs);