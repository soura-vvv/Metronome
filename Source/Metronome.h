/*
  ==============================================================================

    Metronome.h
    Created: 1 May 2021 4:34:01pm
    Author:  Sourav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class Metronome: public juce::HighResolutionTimer
{
public:
    Metronome();
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void reset();
    void juce::HighResolutionTimer::hiResTimerCallback() override;
    void setBpm(int bpm);
    void fileChooser();
private:
    int mTotalSamples{ 0 };
    int mInterval{ 0 };
    int mBpm{ 140 };
    double mSampleRate;
    
    int mSamplesRemaining;
    juce::AudioFormatManager mFormatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> pMetronomeSample{ nullptr };
};
