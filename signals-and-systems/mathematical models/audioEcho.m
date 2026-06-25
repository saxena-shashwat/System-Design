[source, samplingFreq] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\a1.wav");
source = source(:, 1);

delay = round(0.8 * samplingFreq);

implsResp = [1 zeros(1, delay) 0.7];

out = conv(source, implsResp);
out = out ./ max(out);

audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\a1Echo.wav", out, samplingFreq);