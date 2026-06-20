rng(42)

[source, fs] = audioread("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramStableNoise.wav");

out_audio = zeros(size(source));
for channel = 1:size(source, 2)
    out_audio(:, channel) = adaptiveSpectralSubtract(source(:, channel), fs);
end

peak = max(abs(out_audio(:)));
if peak > 0
    out_audio = out_audio ./ peak;
end

audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\vandeMataramD12e.wav", out_audio, fs);

function cleanSignal = adaptiveSpectralSubtract(signal, fs)
signal = signal(:);
numSamples = length(signal);

frameLen = round(0.032 * fs); % 32 ms analysis window
if mod(frameLen, 2) ~= 0
    frameLen = frameLen + 1;
end

hopLen = max(1, round(frameLen / 4)); % 75% overlap
nfft = 2^nextpow2(frameLen);
window = 0.5 - 0.5 * cos(2 * pi * (0:frameLen - 1)' / (frameLen - 1));

if numSamples <= frameLen
    numFrames = 1;
else
    numFrames = ceil((numSamples - frameLen) / hopLen) + 1;
end

paddedLen = (numFrames - 1) * hopLen + frameLen;
paddedSignal = [signal; zeros(paddedLen - numSamples, 1)];

% Use the first second only to bootstrap the tracker, then adapt per frame.
noiseInitSamples = min(fs, numSamples);
if noiseInitSamples <= frameLen
    initFrames = 1;
else
    initFrames = floor((noiseInitSamples - frameLen) / hopLen) + 1;
end

noiseFrames = zeros(nfft, initFrames);
for frameIndex = 1:initFrames
    startIdx = 1 + (frameIndex - 1) * hopLen;
    frame = paddedSignal(startIdx:startIdx + frameLen - 1) .* window;
    spectrum = fft(frame, nfft);
    noiseFrames(:, frameIndex) = abs(spectrum).^2;
end

noisePsd = median(noiseFrames, 2);
smoothedPower = noisePsd;
prevGain = ones(nfft, 1);

powerSmoothing = 0.7;
fastNoiseAdapt = 0.8;
slowNoiseAdapt = 0.995;
snrThreshold = 2.0;
oversubtract = 1.4;
spectralFloor = 0.05;
gainSmoothing = 0.7;

output = zeros(paddedLen, 1);
weight = zeros(paddedLen, 1);

for frameIndex = 1:numFrames
    startIdx = 1 + (frameIndex - 1) * hopLen;
    frame = paddedSignal(startIdx:startIdx + frameLen - 1) .* window;
    spectrum = fft(frame, nfft);
    powerSpectrum = abs(spectrum).^2;

    smoothedPower = powerSmoothing * smoothedPower + (1 - powerSmoothing) * powerSpectrum;
    posteriorSnr = smoothedPower ./ max(noisePsd, eps);
    likelyNoiseBins = posteriorSnr < snrThreshold;

    noiseAdapt = slowNoiseAdapt * ones(nfft, 1);
    noiseAdapt(likelyNoiseBins) = fastNoiseAdapt;
    noisePsd = noiseAdapt .* noisePsd + (1 - noiseAdapt) .* smoothedPower;

    cleanPower = powerSpectrum - oversubtract * noisePsd;
    cleanPower = max(cleanPower, spectralFloor * noisePsd);

    rawGain = sqrt(cleanPower ./ max(powerSpectrum, eps));
    gain = gainSmoothing * prevGain + (1 - gainSmoothing) * rawGain;
    prevGain = gain;

    cleanSpectrum = gain .* spectrum;
    cleanFrame = real(ifft(cleanSpectrum, nfft));
    cleanFrame = cleanFrame(1:frameLen) .* window;

    output(startIdx:startIdx + frameLen - 1) = output(startIdx:startIdx + frameLen - 1) + cleanFrame;
    weight(startIdx:startIdx + frameLen - 1) = weight(startIdx:startIdx + frameLen - 1) + window.^2;
end

weight(weight < eps) = 1;
cleanSignal = output ./ weight;
cleanSignal = cleanSignal(1:numSamples);
end
