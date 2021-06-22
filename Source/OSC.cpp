/*
  ==============================================================================

    OSC.cpp
    Created: 22 Jun 2021 11:30:13am
    Author:  rhall

  ==============================================================================
*/

#include "OSC.h"
#include "PluginProcessor.h"

void OscData::startServer(int port, juce::AudioProcessor* p)
{
  listener.processor = p;
  oscReceiver.addListener(&listener);
  oscReceiver.connect(port);
}

void OscListener::oscMessageReceived(const juce::OSCMessage& msg)
{
  if (msg.getAddressPattern().toString().startsWith("/node/"))
  {
    processNodeMsg(msg);    
  }
}
juce::StringArray split(juce::String s, juce::String sep)
{
  juce::StringArray ret;
  juce::String rest = s;
  while (rest.indexOf(sep) != -1)
  {
    ret.add(rest.upToFirstOccurrenceOf(sep, false, false));
    rest = rest.fromFirstOccurrenceOf(sep, false, false);
  }
  return ret;
}

void OscListener::processNodeMsg(const juce::OSCMessage& msg)
{
  juce::String addr = msg.getAddressPattern().toString() + "/";
  juce::StringArray parsedMsg = split(addr, "/");

  juce::OSCArgument arg = msg[0];
  float floatVal;
  if (arg.isFloat32())
  {
    floatVal = arg.getFloat32();
    auto proc = dynamic_cast<SC_ServerAudioProcessor*>(processor);
    for (int i = 0; i < proc->maxPolyphony; i++)
    {
      SynthVoice *v = dynamic_cast<SynthVoice*>(proc->synth.getVoice(i));
      auto nodeName = parsedMsg[2];
      auto key = parsedMsg[3];
      Node *node = v->nodeTree[nodeName];
      if (node->type == Value_8_Node)
      {
        Value8Node* v8node = dynamic_cast<Value8Node*>(node);
        v8node->setValue(key, floatVal);
      }
    }
  }
    std::cout << "Operator Msg: " << msg.getAddressPattern().toString() << std::endl;
  for (auto s : parsedMsg)
  {
    std::cout << s << std::endl;
  }
}

