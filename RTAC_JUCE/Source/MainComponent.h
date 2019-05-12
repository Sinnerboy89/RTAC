/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <juce_dsp/juce_dsp.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

	// rtac_basic
	void load_wav(AudioBuffer<float>* ab, String prompt);
	AudioBuffer<float>* MainComponent::myHRTFConvolver(AudioBuffer<float>* s1, AudioBuffer<float>* s2, AudioBuffer<float>* s3, AudioBuffer<float>* s4, AudioBuffer<float>* s5, AudioBuffer<float>* s6, AudioBuffer<float>* hFL, AudioBuffer<float>* hFR, AudioBuffer<float>* hC, AudioBuffer<float>* hRL, AudioBuffer<float>* hRR);

private:
    //==============================================================================
    // Your private member variables go here...


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
