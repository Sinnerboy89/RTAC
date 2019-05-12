clear all;

Fs = 44100;

% load HRIRs in MATLAB format
fl_hrir = load('FL_30deg_Trial1_44_1_norm.mat');
fr_hrir = load('FR_30deg_Trial1_44_1_norm.mat');
c_hrir = load('C_0deg_Trial1_44_1_norm.mat');
rl_hrir = load('RL_120deg_Trial1_44_1_norm.mat');
rr_hrir = load('RR_120deg_Trial1_44_1_norm.mat');

% % Save in WAV format
audiowrite('../io/FL_30deg_Trial1_44_1_norm.wav', fl_hrir.Res, Fs);
audiowrite('../io/FR_30deg_Trial1_44_1_norm.wav', fr_hrir.Res, Fs);
audiowrite('../io/C_0deg_Trial1_44_1_norm.wav', c_hrir.Res, Fs);
audiowrite('../io/RL_120deg_Trial1_44_1_norm.wav', rl_hrir.Res, Fs);
audiowrite('../io/RR_120deg_Trial1_44_1_norm.wav', rr_hrir.Res, Fs);