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

  void process(int64_t ticks, int sample) override;
  void updateConnections() override;

  void setValue(juce::String key, float val);

private:
  ScalarValue* v1 = new ScalarValue(3.0f);
  ScalarValue* v2 = new ScalarValue(0.75f);
  ScalarValue* v3 = new ScalarValue(0.0f);
  ScalarValue* v4 = new ScalarValue(6.0f);
  ScalarValue* v5 = new ScalarValue();
  ScalarValue* v6 = new ScalarValue();
  ScalarValue* v7 = new ScalarValue();
  ScalarValue* v8 = new ScalarValue();
  SwitchValue* t = new SwitchValue(true);
  SwitchValue* f = new SwitchValue(false);

  MonoControlOutputConnector* v1out;
  MonoControlOutputConnector* v2out;
  MonoControlOutputConnector* v3out;
  MonoControlOutputConnector* v4out;
  MonoControlOutputConnector* v5out;
  MonoControlOutputConnector* v6out;
  MonoControlOutputConnector* v7out;
  MonoControlOutputConnector* v8out;
  MonoControlOutputConnector* tout;
  MonoControlOutputConnector* fout;
};
