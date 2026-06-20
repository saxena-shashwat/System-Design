[source, samplingFreq] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramTrimmed.wav");

delay = round(1.5 * samplingFreq / 5);

implsResp = [1 zeros(1, delay) 0.7 zeros(1, delay) 0.5 zeros(1, delay) 0.3];

out = conv(source, implsResp);
out = out ./ max(out);

audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramReverb.wav", out, samplingFreq);