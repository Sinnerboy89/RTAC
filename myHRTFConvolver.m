function cnvOut = myHRTFConvolver(signal1, signal2, signal3, signal4, ...
                  signal5, signal6, hFR, hC, hFL, hRL, hRR)
%% This function takes in input as the 5.1 audio buffers and their corresponding hrtfs
%  Performs convolution for all the channels and downmixes it to binaural
              
              
%% Create the FIR filters as persistent variables so they are only
%  initialized the first time the function is called
 
    persistent cnvFR_L cnvFR_R cnvFL_L cnvFL_R cnvC_L cnvC_R cnvRR_L cnvRR_R cnvRL_L cnvRL_R
    
    if(isempty(cnvFR_L))
             
        % Creating the convolution objects each for left/right FIR filters for each of the five different locations
        cnvFR_L = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hFR(:,1)','PartitionForReducedLatency',true);
        cnvFR_R = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hFR(:,2)','PartitionForReducedLatency',true);
        cnvFL_L = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hFL(:,1)','PartitionForReducedLatency',true);
        cnvFL_R = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hFL(:,2)','PartitionForReducedLatency',true);
        cnvC_L = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hC(:,1)','PartitionForReducedLatency',true);
        cnvC_R = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hC(:,2)','PartitionForReducedLatency',true);
        cnvRR_L = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hRR(:,1)','PartitionForReducedLatency',true);
        cnvRR_R = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hRR(:,2)','PartitionForReducedLatency',true);
        cnvRL_L = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hRL(:,1)','PartitionForReducedLatency',true);
        cnvRL_R = dsp.FrequencyDomainFIRFilter('Method','Overlap-save','Numerator',hRL(:,2)','PartitionForReducedLatency',true);
        
        partitionLength = 1024;

        cnvFR_L.PartitionLength = partitionLength;
        cnvFR_R.PartitionLength = partitionLength;
        cnvFL_L.PartitionLength = partitionLength;
        cnvFL_R.PartitionLength = partitionLength;
        cnvC_L.PartitionLength = partitionLength;
        cnvC_R.PartitionLength = partitionLength;
        cnvRR_L.PartitionLength = partitionLength;
        cnvRR_R.PartitionLength = partitionLength;
        cnvRL_L.PartitionLength = partitionLength;
        cnvRL_R.PartitionLength = partitionLength;

    end
    
    %% Applying convolution for Front Left locations
    cnvFLOutL = cnvFL_L(signal1);
    cnvFLOutR = cnvFL_R(signal1);
    
    
    %% Applying convolution for Front Right locations 
    cnvFROutL = cnvFR_L(signal2);
    cnvFROutR = cnvFR_R(signal2);
   
    %% Applying convolution for Center locations
     cnvCOutL = cnvC_L(signal3);
     cnvCOutR = cnvC_R(signal3);
    
     
   %% Applying convolution for Rear Left locations
     cnvRLOutL = cnvRL_L(signal5);
     cnvRLOutR = cnvRL_R(signal5);     
     
   %% Applying convolution for Rear Right locations
     cnvRROutL = cnvRR_L(signal6);
     cnvRROutR = cnvRR_R(signal6);
   
    %% Summing all the outputs including LFE (signal4)
    cnvOutL = cnvFROutL + cnvFLOutL + cnvCOutL + cnvRROutL + cnvRLOutL + signal4;
    cnvOutR = cnvFROutR + cnvFLOutR + cnvCOutR + cnvRROutR + cnvRLOutR + signal4;
    
    %% creating the binaural stereo file for playback
    cnvOut = [cnvOutL cnvOutR];

end