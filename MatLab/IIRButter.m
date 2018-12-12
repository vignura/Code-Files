function Hd = IIRButter
%IIRBUTTER Returns a discrete-time filter object.

% MATLAB Code
% Generated by MATLAB(R) 8.6 and the Signal Processing Toolbox 7.1.
% Generated on: 12-Dec-2018 12:15:27

% Butterworth Lowpass filter designed using FDESIGN.LOWPASS.

% All frequency values are in Hz.
Fs = 15625;  % Sampling Frequency

Fpass = 150;         % Passband Frequency
Fstop = 180;         % Stopband Frequency
Apass = 1;           % Passband Ripple (dB)
Astop = 18;          % Stopband Attenuation (dB)
match = 'passband';  % Band to match exactly

% Construct an FDESIGN object and call its BUTTER method.
h  = fdesign.lowpass(Fpass, Fstop, Apass, Astop, Fs);
Hd = design(h, 'butter', 'MatchExactly', match);

% [EOF]