#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    playButton.setToggleState(false,juce::NotificationType::dontSendNotification);
    addAndMakeVisible(playButton);
    playButton.setRadioGroupId(1);
    playButton.onClick = [this] {playButtonClicked(); };

    stopButton.setToggleState(true, juce::NotificationType::dontSendNotification);
    addAndMakeVisible(stopButton);
    stopButton.setRadioGroupId(1);
    stopButton.onClick = [this] {stopButtonClicked(); };

    setSize (200, 300);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
    metronome.prepareToPlay(samplesPerBlockExpected,sampleRate);
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
    auto buffer = bufferToFill.numSamples;
    if (playState == PlayState::Playing)
        metronome.getNextAudioBlock(bufferToFill);
    
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    juce::Rectangle<int> bounds = getLocalBounds();
    juce::FlexBox flexBox;
    flexBox.items.add(juce::FlexItem(90, 90, playButton));
    flexBox.items.add(juce::FlexItem(90, 90, stopButton));
    flexBox.performLayout(bounds.reduced(10));
}
void MainComponent::playButtonClicked()
{
    playState = PlayState::Playing;
}
void MainComponent::stopButtonClicked()
{
    playState = PlayState::Stopped;
    metronome.reset();
}
