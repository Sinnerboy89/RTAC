#include "MainComponent.h"

void MainComponent::load_wav(AudioBuffer<float> *ab, String prompt) {

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

AudioBuffer<float>* MainComponent::myHRTFConvolver(AudioBuffer<float> *s1, AudioBuffer<float> *s2, AudioBuffer<float> *s3, AudioBuffer<float> *s4, AudioBuffer<float> *s5, AudioBuffer<float> *s6, AudioBuffer<float> *hFL, AudioBuffer<float> *hFR, AudioBuffer<float> *hC, AudioBuffer<float> *hRL, AudioBuffer<float> *hRR) {

	/*  %% This function takes in input as the 5.1 audio buffers and their corresponding hrtfs
		%  Performs convolution for all the channels and downmixes it to binaural */

	AudioBuffer<float> *y;
	AudioBuffer<float> cnvFR_out_buf;
	dsp::AudioBlock<float> cnvFR_out_block (cnvFR_out_buf);
	dsp::ProcessSpec PS;
	dsp::Convolution cnvFR;
	juce::dsp::ProcessContextReplacing<float> PC (cnvFR_out_block);

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

	// Sum outputs (including LFE)
	y->copyFrom(0, 0, cnvFR_out_buf.getReadPointer(0), cnvFR_out_buf.getNumSamples());

	return y;
}