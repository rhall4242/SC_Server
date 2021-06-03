/*
  ==============================================================================

    Node.h
    Created: 3 Jun 2021 2:30:54pm
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Connector.h"
#include "Value.h"

class Node
{
  std::map<juce::String, InputConnector*> inputs;
  std::map<juce::String, OutputConnector*> outputs;

};