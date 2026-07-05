[source, fs] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\test.wav");
source = source(:, 1);

implsResp = 0.5 .* ones(round(fs/1000), 1);
implsResp = implsResp ./ sum(implsResp);

out = conv(source, implsResp);
out = out ./ max(abs(out));

plot(abs(fft(source)), "Color", 'r');
hold on;
title('Fourier Analysis');
xlabel('Frequency');
ylabel('Magnitude');
plot(abs(fft(out)), "Color", 'g');
hold off

audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\testMovingAvg.wav", out, fs);