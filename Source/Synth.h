/*
  ==============================================================================

    Synth.h
    Created: 6 Jun 2021 12:04:19pm
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Node.h"

class Synth : virtual public juce::Synthesiser
{
public:
    Synth() : juce::Synthesiser() {}
    NodeTree nodeTree;
};