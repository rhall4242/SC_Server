/*
  ==============================================================================

    MidiInputNode.h
    Created: 4 Jun 2021 10:05:27am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Node.h"

class MidiInputNode : public Node
{
public:
  NodeType type {MIDI_Input_Node};

  void process(int64_t ticks);
};
