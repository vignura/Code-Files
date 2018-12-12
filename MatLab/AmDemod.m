fc = 1000;               % carrier frequency
fm = 2;               % Message frequency
fs = 15.625e3;              % sampling frequency
ts = 1/fs;              % sample period
T = 5;                  % simulation time         
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

% AM signal source
AM = [AM_DSBFC zeros(size(AM_DSBFC)) AM_DSBFC];
SP_AM = 20 * log(abs(fft(AM, W)) / (2 ^ 12));

% AM demodulation
ABS_AM = abs(AM);
SP_ABS_AM = 20 * log(abs(fft(ABS_AM, W))/ (2 ^ 12));

%IIR
FT_ABS_AM = filter(IIRChebyT1, ABS_AM);
SP_FT_ABS_AM = 20 * log(abs(fft(FT_ABS_AM, W))/ (2 ^ 12));

% decimation 
DecFact = 4;
DMOD_AM = decimate(FT_ABS_AM, DecFact);

% DC removal
% IIR
FT_DMOD_AM = filter(IIRChebyT1HPF, DMOD_AM);
SP_FT2_DMOD_AM = 20 * log(abs(fft(FT_DMOD_AM, W))/ (2 ^ 12));
% FIR
FIR_FT_DMOD_AM = filter(FIREqHPF, DMOD_AM);
FIR_SP_FT2_DMOD_AM = 20 * log(abs(fft(FIR_FT_DMOD_AM, W))/ (2 ^ 12));


%figure(1);
%plot(AM);
%figure(2);
%plot(ABS_AM);

%figure(3)
%plot(f, SP_AM);
%figure(4)
%plot(f, SP_ABS_AM);

figure(5)
plot(FT_DMOD_AM);
figure(6)
plot((f / DecFact), SP_FT2_DMOD_AM);

figure(7)
plot(FIR_FT_DMOD_AM);
figure(8)
plot((f / DecFact), FIR_SP_FT2_DMOD_AM);
