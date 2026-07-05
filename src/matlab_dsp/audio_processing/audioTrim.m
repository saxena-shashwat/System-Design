[source, samplingFreq] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramFull.wav");

out = source((samplingFreq*1):(samplingFreq*10), 1);

audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramTrimmed.wav", out, samplingFreq);