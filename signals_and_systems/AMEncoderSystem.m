% Communication Channel Simulator

freq = 50;

sineWave = @(t, w, p) sin(w*t + p);
squareWave = @(t, w, p) (sineWave(t, w, p)>0);

time = linspace(0, 100, 1000);
signal = sineWave(time, 2*pi*freq, 0);

carrierFrequency = 220;
cw = 2*pi*carrierFrequency;
carrierWave = sineWave(time, cw, 0);

m = 0.7;

ampModulatedWave = (1+m.*signal).*carrierWave;

plot(time, ampModulatedWave);