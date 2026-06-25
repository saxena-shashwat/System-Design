% Communication Channel Simulator

freq = 50;

sineWave = @(t, w, p) sin(w*t + p);
squareWave = @(t, w, p) (sineWave(t, w, p)>0);

[signal, fs] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\test.wav");
signal = signal(:, 1);

len = length(signal);
time = (0:len-1)/fs;

carrierFrequency = 4000;
cw = 2*pi*carrierFrequency;
carrierWave = sineWave(time, cw, 0);
carrierWave = carrierWave';

m = 2;

ampModulatedWave = (1 + m.*signal).*carrierWave;
ampModulatedWave = ampModulatedWave ./ max(ampModulatedWave);

toplot = 0.5*fs + 0.1 * fs;
toplot = round(toplot);
subplot(2, 1, 1);
plot(time, ampModulatedWave);
xlabel('Time');
ylabel('Amplitude');
title('Amplitude Modulated Wave')
ylim([-1 1]);
subplot(2, 1, 2);
plot(time, signal, Color = '#FAA500');
xlabel('Time');
ylabel('Amplitude');
title('Source Signal')
ylim([-1 1]);

%audiowrite("amModulated.wav", ampModulatedWave, fs)