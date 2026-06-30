Iy = 0.03125;
d_theta = 0.010;

A = [0, -1;
     0, -(d_theta/Iy)];
B = [0;
     (1/Iy)];


Q = [50,  0; 
      0,  1]; 

R = [1];

k_pitch = lqr(A, B, Q, R);