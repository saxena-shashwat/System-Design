%% Simulation parameters
Ts = 0.01;          % Sampling time (s)
Tend = 60;          % Total simulation time (s)
t = (0:Ts:Tend)';
u = zeros(size(t)); % Initialize altitude array

%% Phase 1: Smooth Takeoff (0 to 5s)
idx1 = (t >= 0 & t < 5);
u(idx1) = 1 - cos(pi * t(idx1) / 5); 

%% Phase 2: Aggressive Step Up (5 to 10s)
idx2 = (t >= 5 & t < 10);
u(idx2) = 6;

%% Phase 3: Aggressive Step Down (10 to 15s)
idx3 = (t >= 10 & t < 15);
u(idx3) = 3;

%% Phase 4: Steady Climb / Ramp (15 to 25s)
idx4 = (t >= 15 & t < 25);
u(idx4) = 3 + 0.5 * (t(idx4) - 15);

%% Phase 5: Smooth Tracking (25 to 40s)
idx5 = (t >= 25 & t < 40);
u(idx5) = 8 + 2 * sin(0.5 * pi * (t(idx5) - 25));

%% Phase 6: High-Frequency Disturbance / Agility (40 to 50s)
idx6 = (t >= 40 & t < 50);
u(idx6) = 8 + 1.5 * sin(1.0 * pi * (t(idx6) - 40)) + 0.5 * sin(3.0 * pi * (t(idx6) - 40));

%% Phase 7: Landing (50 to 60s)
idx7 = (t >= 50 & t <= 60);
u(idx7) = max(0, 8 - 0.8 * (t(idx7) - 50)); % 'max' prevents going underground


inputSignal = timeseries(u, t);