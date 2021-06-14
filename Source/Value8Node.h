/*
  ==============================================================================

    Value8Node.h
    Created: 14 Jun 2021 11:49:03am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Connector.h"
#include "Node.h"
#include "Value.h"

class Value8Node : virtual public Node
{
public:
  Value8Node(juce::String nm);

  NodeType type {Value_8_Node};

  void process(int64_t ticks, int sample) override;

private:
  ScalarValue* v1 = new ScalarValue(7.0f);
  ScalarValue* v2 = new ScalarValue(0.75f);
  ScalarValue* v3 = new ScalarValue();
  ScalarValue* v4 = new ScalarValue();
  ScalarValue* v5 = new ScalarValue();
  ScalarValue* v6 = new ScalarValue();
  ScalarValue* v7 = new ScalarValue();
  ScalarValue* v8 = new ScalarValue();
};
