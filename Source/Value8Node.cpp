/*
  ==============================================================================

    Value8Node.cpp
    Created: 14 Jun 2021 11:49:03am
    Author:  rhall

  ==============================================================================
*/

#include "Value8Node.h"

Value8Node::Value8Node(juce::String nm)
{
  name = juce::String(nm);
  MonoControlOutputConnector* v1out = new MonoControlOutputConnector("V1Output", this);
  outputs[v1out->getName()] = v1out;
  MonoControlOutputConnector* v2out = new MonoControlOutputConnector("V2Output", this);
  outputs[v2out->getName()] = v2out;
  MonoControlOutputConnector* v3out = new MonoControlOutputConnector("V3Output", this);
  outputs[v3out->getName()] = v3out;
  MonoControlOutputConnector* v4out = new MonoControlOutputConnector("V4Output", this);
  outputs[v4out->getName()] = v4out;
  MonoControlOutputConnector* v5out = new MonoControlOutputConnector("V5Output", this);
  outputs[v5out->getName()] = v5out;
  MonoControlOutputConnector* v6out = new MonoControlOutputConnector("V6Output", this);
  outputs[v6out->getName()] = v6out;
  MonoControlOutputConnector* v7out = new MonoControlOutputConnector("V7Output", this);
  outputs[v7out->getName()] = v7out;
  MonoControlOutputConnector* v8out = new MonoControlOutputConnector("V8Output", this);
  outputs[v8out->getName()] = v8out;
}

void Value8Node::process(int64_t ticks, int sample)
{
  MonoControlOutputConnector* v1out = dynamic_cast<MonoControlOutputConnector*>(outputs["V1Output"]);
  v1out->value = v1;
  MonoControlOutputConnector* v2out = dynamic_cast<MonoControlOutputConnector*>(outputs["V2Output"]);
  v2out->value = v2;
  MonoControlOutputConnector* v3out = dynamic_cast<MonoControlOutputConnector*>(outputs["V3Output"]);
  v3out->value = v3;
  MonoControlOutputConnector* v4out = dynamic_cast<MonoControlOutputConnector*>(outputs["V4Output"]);
  v4out->value = v4;
  MonoControlOutputConnector* v5out = dynamic_cast<MonoControlOutputConnector*>(outputs["V5Output"]);
  v5out->value = v5;
  MonoControlOutputConnector* v6out = dynamic_cast<MonoControlOutputConnector*>(outputs["V6Output"]);
  v6out->value = v6;
  MonoControlOutputConnector* v7out = dynamic_cast<MonoControlOutputConnector*>(outputs["V7Output"]);
  v7out->value = v7;
  MonoControlOutputConnector* v8out = dynamic_cast<MonoControlOutputConnector*>(outputs["V8Output"]);
  v8out->value = v8;
  ready = true;
}