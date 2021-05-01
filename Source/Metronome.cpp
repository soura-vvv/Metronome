/*
  ==============================================================================

    Metronome.cpp
    Created: 1 May 2021 4:34:01pm
    Author:  Sourav

  ==============================================================================
*/

#include "Metronome.h"
void Metronome::countSamples(int bufferSize)
{
    mTotalSamples += bufferSize;
    
}
void Metronome::reset()
{
    mTotalSamples = 0;
}
void Metronome::prepareToPlay(double sampleRate)
{
    mSampleRate = sampleRate;
}