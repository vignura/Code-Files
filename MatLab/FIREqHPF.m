function Hd = FIREqHPF
%FIREQHPF Returns a discrete-time filter object.

% MATLAB Code
% Generated by MATLAB(R) 8.6 and the Signal Processing Toolbox 7.1.
% Generated on: 12-Dec-2018 12:44:10

% Equiripple Highpass filter designed using the FIRPM function.

% All frequency values are in Hz.
Fs = 3906.25;  % Sampling Frequency

N     = 150;    % Order
Fstop = 0.01;   % Stopband Frequency
Fpass = 5;     % Passband Frequency
Wstop = 10000;  % Stopband Weight
Wpass = 1;      % Passband Weight
dens  = 20;     % Density Factor

% Calculate the coefficients using the FIRPM function.
b  = firpm(N, [0 Fstop Fpass Fs/2]/(Fs/2), [0 0 1 1], [Wstop Wpass], ...
           {dens});
Hd = dfilt.dffir(b);

% [EOF]