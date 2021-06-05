/*
  ==============================================================================

    SynthSound.h
    Created: 5 Jun 2021 9:49:23am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
  public:
    bool appliesToNote(int midiNoteNumber) override {return true;}
    bool appliesToChannel(int midiChannel) override {return true;}
};
