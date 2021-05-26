/*
  ==============================================================================

    Metronome.cpp
    Created: 1 May 2021 4:34:01pm
    Author:  Sourav

  ==============================================================================
*/

#include "Metronome.h"
Metronome::Metronome()
{
    mFormatManager.registerBasicFormats();
    fileChooser();
    
    
    
    
   //jassert(mySamples[0].exists());
    
    

    
}
void Metronome::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    mTotalSamples += bufferToFill.numSamples;


    mSamplesRemaining = mTotalSamples % mInterval;


    if ((mSamplesRemaining + bufferToFill.numSamples) >= mInterval)
    {
        const auto timeToStartPlaying = mInterval - mSamplesRemaining;//Making it sample Accurate
        pMetronomeSample->setNextReadPosition(2);



        for (auto sample = 0; sample <= bufferToFill.numSamples; sample++)
        {
            if (sample == timeToStartPlaying)
            {
                pMetronomeSample->getNextAudioBlock(bufferToFill);
                break;
            }
        }
    }

    if (pMetronomeSample->getNextReadPosition() < pMetronomeSample->getTotalLength()) { pMetronomeSample->getNextAudioBlock(bufferToFill); }

}
void Metronome::reset()
{
    mTotalSamples = 0;
}
void Metronome::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{

    juce::HighResolutionTimer::startTimer(60.0);
    mSampleRate = sampleRate;
    if(pMetronomeSample!=nullptr)
        pMetronomeSample->prepareToPlay(samplesPerBlockExpected, sampleRate);
    

    
}
void Metronome::hiResTimerCallback()
{
    mInterval = 60.0 / mBpm * mSampleRate;
}
void Metronome::setBpm(int bpm)
{
    mBpm = bpm;
}

void Metronome::fileChooser()
{
    juce::FileChooser chooser{ "Choose A File For the Metronome Click",{},"*.wav;*.mp3" };
    if (chooser.browseForFileToOpen())
    {
        auto myFile = chooser.getResult();

        auto formatReader = mFormatManager.createReaderFor(myFile);
        if (formatReader != nullptr)
        {
            pMetronomeSample.reset(new juce::AudioFormatReaderSource(formatReader, true));
        }

    }
    else
        fileChooser();
}