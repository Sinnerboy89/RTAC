/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }

	// load 5.1 signal
	AudioBuffer<float> *fl_buf, *fr_buf, *c_buf, *lfe_buf, *rl_buf, *rr_buf;
	load_wav(fl_buf, String("Load FL"));
	load_wav(fr_buf, String("Load FR"));
	load_wav(c_buf, String("Load C"));
	load_wav(lfe_buf, String("Load LFE"));
	load_wav(rl_buf, String("Load RL"));
	load_wav(rr_buf, String("Load RR"));

	// load HRIRs
	AudioBuffer<float> *fl_hrir, *fr_hrir, *c_hrir, *rl_hrir, *rr_hrir;
	load_wav(fl_hrir, String("Load FL HRIR"));
	load_wav(fr_hrir, String("Load FR HRIR"));
	load_wav(c_hrir, String("Load C HRIR"));
	load_wav(rl_hrir, String("Load RL HRIR"));
	load_wav(rr_hrir, String("Load RR HRIR"));

	// Do the thing
	AudioBuffer<float> *y;
	y = myHRTFConvolver(fl_buf, fr_buf, c_buf, lfe_buf, rl_buf, rr_buf, fl_hrir, fr_hrir, c_hrir, rl_hrir, rr_hrir);

	// save output to disk for QC
	auto file = File("C:/Projects/RTAC/test.wav");
	WavAudioFormat format;
	std::unique_ptr<AudioFormatWriter> writer;
	writer.reset(format.createWriterFor(new FileOutputStream (file),
		48000.0,
		y->getNumChannels(),
		24,
		{},
		0));
	if (writer != nullptr)
		writer->writeFromAudioSampleBuffer(*y, 0, y->getNumSamples());
	
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate) // WHY ISN'T THIS BEING CALLED
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()

}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
