[source, samplingFreq] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramTrimmed.wav");

delay = round(1.5 * samplingFreq);

implsResp = [1 zeros(1, round(delay/2)) 1 zeros(1, round(delay/2)) 1];

out = conv(source, implsResp);
out = out ./ max(out);

audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramEcho.wav", out, samplingFreq);