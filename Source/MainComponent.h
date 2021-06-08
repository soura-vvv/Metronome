#pragma once

#include <JuceHeader.h>
#include "Metronome.h"
//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent, public juce::Slider::Listener,public juce::HighResolutionTimer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;
    void playButtonClicked();
    void stopButtonClicked();
    void sliderValueChanged(juce::Slider* slider) override;
    void loadButtonClicked();
    enum class PlayState
    {
        Playing,
        Stopped
    };
    void juce::HighResolutionTimer::hiResTimerCallback() override;
private:

    juce::TextButton playButton{ "Play" };
    juce::TextButton stopButton{ "Stop" };
    juce::Slider bpmSlider;
    PlayState playState{PlayState::Stopped};
    Metronome metronome;
    
    
    
   // juce::Label bpmLabel{ "BPM" };
    //juce::Slider::Listener listener;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
