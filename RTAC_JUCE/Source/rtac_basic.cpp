#include "MainComponent.h"

void MainComponent::load_wav(AudioBuffer<float>* ab, String prompt) {

	AudioFormatManager formatManager;

	FileChooser chooser(prompt,
	{},
		"*.wav");
	if (chooser.browseForFileToOpen())
	{
		auto file = chooser.getResult();
		auto* reader = formatManager.createReaderFor(file);
		if (reader != nullptr)
		{
			reader->read(ab, 0, 441000, 0, true, false);
		}
	}
}

AudioBuffer<float>* MainComponent::myHRTFConvolver(AudioBuffer<float>* s1, AudioBuffer<float>* s2, AudioBuffer<float>* s3, AudioBuffer<float>* s4, AudioBuffer<float>* s5, AudioBuffer<float>* s6, AudioBuffer<float>* hFR, AudioBuffer<float>* hC, AudioBuffer<float>* hFL, AudioBuffer<float>* hRL, AudioBuffer<float>* hRR) {

	/*  %% This function takes in input as the 5.1 audio buffers and their corresponding hrtfs
		%  Performs convolution for all the channels and downmixes it to binaural */

	AudioBuffer<float> y_buf;
	dsp::AudioBlock<float> y_block (y_buf);
	dsp::ProcessSpec PS;
	dsp::Convolution cnvFR;
	juce::dsp::ProcessContextReplacing<float> PC (y_block);

	double Fs = 44100;
	double partitionLength = 1024;

	// setup ProcessSpec for Convolution objects
	PS.maximumBlockSize = partitionLength;
	PS.numChannels = 2;
	PS.sampleRate = Fs;

	// prepare Convolution objects
	cnvFR.prepare(PS);

	// load IRs
	cnvFR.copyAndLoadImpulseResponseFromBuffer(*hFR, Fs, true, true, true, 0);

	// Apply convolutions
	cnvFR.process(PC);

	//	%% Applying convolution for Front Left locations
	//	cnvFLOutL = cnvFL_L(signal1);
	//cnvFLOutR = cnvFL_R(signal1);


	//%% Applying convolution for Front Right locations
	//	cnvFROutL = cnvFR_L(signal2);
	//cnvFROutR = cnvFR_R(signal2);

	//%% Applying convolution for Center locations
	//	cnvCOutL = cnvC_L(signal3);
	//cnvCOutR = cnvC_R(signal3);


	//%% Applying convolution for Rear Left locations
	//	cnvRLOutL = cnvRL_L(signal5);
	//cnvRLOutR = cnvRL_R(signal5);

	//%% Applying convolution for Rear Right locations
	//	cnvRROutL = cnvRR_L(signal6);
	//cnvRROutR = cnvRR_R(signal6);

	//%% Summing all the outputs including LFE(signal4)
	//	cnvOutL = cnvFROutL + cnvFLOutL + cnvCOutL + cnvRROutL + cnvRLOutL + signal4;
	//cnvOutR = cnvFROutR + cnvFLOutR + cnvCOutR + cnvRROutR + cnvRLOutR + signal4;

	//%% creating the binaural stereo file for playback
	//	cnvOut = [cnvOutL cnvOutR];

	//end

	// dummy return
	return s1;
}