[source, fs] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramStableNoise.wav");

implsResp = 0.25 .* ones(fs/1000, 1);

out = conv(source, implsResp);
out = out ./ max(abs(out));

plot(abs(fft(source)), "Color", 'r');
hold on;
plot(abs(fft(out)), "Color", 'g');
hold off

audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramDenoised.wav", out, fs);