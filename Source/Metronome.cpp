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
        pMetronomeSample->setNextReadPosition(0);
        pMetronomeSample2->setNextReadPosition(0);


        for (auto sample = 0; sample <= bufferToFill.numSamples; sample++)
        {
            if (sample == timeToStartPlaying)
            {
                counter = (counter + 1) % 4;
                if (counter == 0)
                {
                    pMetronomeSample->getNextAudioBlock(bufferToFill);
                   if (pMetronomeSample->getNextReadPosition() < pMetronomeSample->getTotalLength()) { pMetronomeSample->getNextAudioBlock(bufferToFill); }
                }
                    
                else
                {
                    pMetronomeSample2->getNextAudioBlock(bufferToFill);
                    if (pMetronomeSample2->getNextReadPosition() < pMetronomeSample2->getTotalLength()) { pMetronomeSample2->getNextAudioBlock(bufferToFill); }
                }
                    
                
                DBG(counter);
                break;
            }
        }
    }

    

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
    if (pMetronomeSample != nullptr)
        pMetronomeSample2->prepareToPlay(samplesPerBlockExpected, sampleRate);

    
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
    auto myFile = juce::File::getCurrentWorkingDirectory().getChildFile("Metronome_Sound_2.wav");
    
    DBG(myFile.getFullPathName());
    
    
    auto formatReader = mFormatManager.createReaderFor(myFile);
    if (formatReader != nullptr)
    {
        pMetronomeSample2.reset(new juce::AudioFormatReaderSource(formatReader, true));
    }
    else
    {
        myFile = juce::File::getCurrentWorkingDirectory().getChildFile("../../../../../Metronome_Sound_2.wav");
        formatReader = mFormatManager.createReaderFor(myFile);
        
        if (formatReader != nullptr)
        {
            pMetronomeSample2.reset(new juce::AudioFormatReaderSource(formatReader, true));
            
        }
            
       
    }
     myFile = juce::File::getCurrentWorkingDirectory().getChildFile("Metronome_sound_1.wav");


    DBG(myFile.getFullPathName());


    formatReader = mFormatManager.createReaderFor(myFile);
    if (formatReader != nullptr)
    {
        pMetronomeSample.reset(new juce::AudioFormatReaderSource(formatReader, true));
    }
    else
    {
        myFile = juce::File::getCurrentWorkingDirectory().getChildFile("../../../../../Metronome_Sound_1.wav");
        formatReader = mFormatManager.createReaderFor(myFile);
        if (formatReader != nullptr)
            pMetronomeSample.reset(new juce::AudioFormatReaderSource(formatReader, true));
        
    }   
   
    
}