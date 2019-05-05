clear all;

% extract test samples from original 5.1 inputs

Fs = 44100; % expected input sample rate
start_t = 60; % test start (seconds)
dur = 10; % test length (seconds)

% Read
file01_test = audioread('../io/file-01.wav', [start_t*Fs (start_t+dur)*Fs]);
file02_test = audioread('../io/file-02.wav', [start_t*Fs (start_t+dur)*Fs]);
file03_test = audioread('../io/file-03.wav', [start_t*Fs (start_t+dur)*Fs]);
file04_test = audioread('../io/file-04.wav', [start_t*Fs (start_t+dur)*Fs]);
file05_test = audioread('../io/file-05.wav', [start_t*Fs (start_t+dur)*Fs]);
file06_test = audioread('../io/file-06.wav', [start_t*Fs (start_t+dur)*Fs]);

% Write
audiowrite('../io/file-01_test.wav', file01_test, Fs);
audiowrite('../io/file-02_test.wav', file02_test, Fs);
audiowrite('../io/file-03_test.wav', file03_test, Fs);
audiowrite('../io/file-04_test.wav', file04_test, Fs);
audiowrite('../io/file-05_test.wav', file05_test, Fs);
audiowrite('../io/file-06_test.wav', file06_test, Fs);