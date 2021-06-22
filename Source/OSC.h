/*
  ==============================================================================

    OSC.h
    Created: 22 Jun 2021 11:30:13am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>


class OscListener : public juce::OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>
{
  public:
    void oscMessageReceived(const juce::OSCMessage& msg) override;
    void processNodeMsg(const juce::OSCMessage& msg);
    juce::AudioProcessor* processor;
};

class OscData 
{
  public:
    juce::OSCReceiver oscReceiver;
    OscListener listener;
    void startServer(int port, juce::AudioProcessor* p);

  private:
};
