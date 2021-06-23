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
  type = Value_8_Node;
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
  MonoControlOutputConnector* tout = new MonoControlOutputConnector("TrueOutput", this);
  outputs[tout->getName()] = tout;
  MonoControlOutputConnector* fout = new MonoControlOutputConnector("FalseOutput", this);
  outputs[fout->getName()] = fout;
}

void Value8Node::updateConnections()
{
  v1out = dynamic_cast<MonoControlOutputConnector*>(outputs["V1Output"]);
  v2out = dynamic_cast<MonoControlOutputConnector*>(outputs["V2Output"]);
  v3out = dynamic_cast<MonoControlOutputConnector*>(outputs["V3Output"]);
  v4out = dynamic_cast<MonoControlOutputConnector*>(outputs["V4Output"]);
  v5out = dynamic_cast<MonoControlOutputConnector*>(outputs["V5Output"]);
  v6out = dynamic_cast<MonoControlOutputConnector*>(outputs["V6Output"]);
  v7out = dynamic_cast<MonoControlOutputConnector*>(outputs["V7Output"]);
  v8out = dynamic_cast<MonoControlOutputConnector*>(outputs["V8Output"]);
  tout = dynamic_cast<MonoControlOutputConnector*>(outputs["TrueOutput"]);
  fout = dynamic_cast<MonoControlOutputConnector*>(outputs["FalseOutput"]);
}

void Value8Node::process(int64_t ticks, int sample)
{
  v1out->value = v1;
  v2out->value = v2;
  v3out->value = v3;
  v4out->value = v4;
  v5out->value = v5;
  v6out->value = v6;
  v7out->value = v7;
  v8out->value = v8;
  tout->value = t;
  fout->value = f;
  ready = true;
}

void Value8Node::setValue(juce::String key, float val)
{
  if (key == "V1")
  {
    v1->val = val;
  }
  else if (key == "V2")
  {
    v2->val = val;
  }
  else if (key == "V3")
  {
    v3->val = val;
  }
  else if (key == "V4")
  {
    v4->val = val;
  }
  else if (key == "V5")
  {
    v5->val = val;
  }
  else if (key == "V6")
  {
    v6->val = val;
  }
  else if (key == "V7")
  {
    v7->val = val;
  }
  else if (key == "V8")
  {
    v8->val = val;
  }
}
