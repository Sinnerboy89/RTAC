function [h_left,h_right,normflag] = Normalize_MultichannelRendering(Nfft,dbnorm,h_left,h_right)

% This function normalizes the hrirs for multichannel rendering 
% The sum of the hrirs is checked to see if max of sum is above 0 dB. If it is
% above 0 dB, normalization is carried out such that max of sum is 0 dB. 
% If max sum is less than 0 dB,then no normalization is done

% number of fft points
N1 = Nfft;

% fft of left and right
h_leftf = fft(h_left,N1);
h_rightf = fft(h_right,N1);

% Sum of ffts for all the channels
h_left_sum = sum(h_leftf,2);
h_right_sum = sum(h_rightf,2);

h_left_sumabsdb = 20*log10(abs(h_left_sum(1:N1/2,:)));
h_right_sumabsdb = 20*log10(abs(h_right_sum(1:N1/2,:)));

% Maximum dB of left and right
ml = max(h_left_sumabsdb);
mr = max(h_right_sumabsdb);
mmaxdb = max(ml,mr);

% Normalize the hrirs such that the max dB is equal to dbnorm
if (mmaxdb >= 0)
    normfactor = 10^(dbnorm/20);
    mmax = 10^(mmaxdb/20);
    gainNorm = normfactor/mmax;
    normflag = 1;
elseif(mmaxdb < 0)
    gainNorm = 1;
    normflag = 0;
end

% Nornalize 
h_left = h_left*gainNorm;
h_right = h_right*gainNorm;


end

