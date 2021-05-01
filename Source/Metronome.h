/*
  ==============================================================================

    Metronome.h
    Created: 1 May 2021 4:34:01pm
    Author:  Sourav

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
class Metronome
{
public:

    void countSamples(int bufferSize);
    void prepareToPlay(double sampleRate);
    void reset();
private:
    int mTotalSamples{ 0 };

    double mSampleRate;
};
