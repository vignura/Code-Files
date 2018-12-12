fc = 4000;               % carrier frequency
fm = 100;               % Message frequency
fs = 15.625e3;              % sampling frequency
ts = 1/fs;              % sample period
T = 1;                  % simulation time         
W = (8192);               % FFT window size

% time vector 
t = 0:ts:T;
% frequency vector
f = 0:(fs/W):(fs - (fs / W));

ac = 1;                 % carrier amplitude
M = 0.9;                % Modulation Index

% AM components
C = ac * sin(2 * pi * fc * t);
LSB = (M /2) * sin(2 * pi * (fc - fm) *t);
USB = (M /2) * sin(2 * pi * (fc + fm) *t);

% AM signal Types
AM_DSBFC = C + LSB + USB;
AM_USBFC = C + USB;
AM_LSBFC = C + LSB;
AM_DSB = LSB + USB;

% AM demodulation
% choose the AM signal to be demodulated
AM = AM_DSBFC; 
ABS_AM = abs(AM);

SP_AM = 20 * log(abs(fft(AM, W)) / (2 ^ 12));
SP_ABS_AM = 20 * log(abs(fft(ABS_AM, W))/ (2 ^ 12));

%figure(1);
%plot(AM);
%figure(2);
%plot(ABS_AM);

figure(3)
plot(f, SP_AM);
figure(4)
plot(f, SP_ABS_AM);

