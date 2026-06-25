rng(42)
[source, fs] = audioread(
    
);
source = source(:, 1);

N = 3.4 * fs / 1000;
N = 2 * floor(N/2) + 1;
n = 0:N-1;
M = (N-1) / 2;
fc = 10000;
win = 0.54 - 0.46*cos(2*pi*n/(N-1));

sinc = @(x) (x==0) + (x~=0) .* sin(pi*x) ./ (pi*x + (x==0));

hpfIR = (2 * fc/fs) .* sinc(2 * fc * (n-M) / fs);
hpfIR = hpfIR .* win;
hpfIR = hpfIR / sum(hpfIR);
hpfIR = -hpfIR;
hpfIR(M+1) = hpfIR(M+1) + 1;

output = conv(source, hpfIR, 'same');

audiowrite("C:\Users\g3sha\Documents\Electronics\Communication-Systems\audio-samples\testHPFhamming.wav", output, fs);