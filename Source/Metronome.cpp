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
    juce::File myFile{ juce::File::getSpecialLocation(juce::File::SpecialLocationType::userDesktopDirectory) };
    auto mySample = myFile.findChildFiles(juce::File::TypesOfFileToFind::findFiles, true, "Perc (Rim).wav");
   //jassert(mySamples[0].exists());
    auto formatReader=mFormatManager.createReaderFor(mySample[0]);
    pMetronomeSample.reset(new juce::AudioFormatReaderSource(formatReader, true));
}
void Metronome::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    mTotalSamples += bufferToFill.numSamples;


    mSamplesRemaining = mTotalSamples % mInterval;


    if ((mSamplesRemaining + bufferToFill.numSamples) >= mInterval)
    {
        const auto timeToStartPlaying = mInterval - mSamplesRemaining;
        pMetronomeSample->setNextReadPosition(0);



        for (auto sample = 0; sample <= bufferToFill.numSamples; sample++)
        {
            if (sample == timeToStartPlaying)
            {
                pMetronomeSample->getNextAudioBlock(bufferToFill);
            }
        }
    }

    if (pMetronomeSample->getNextReadPosition() != 0) { pMetronomeSample->getNextAudioBlock(bufferToFill); }

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