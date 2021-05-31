/*
  ==============================================================================

    Connector.h
    Created: 31 May 2021 9:43:31am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Connector 
{
public:
  virtual bool isInput() = 0;
  virtual bool isOutput() = 0;
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  virtual bool isMidi() = 0;
  virtual bool isOsc() = 0;
  virtual bool isAudio() = 0;
  virtual bool isControl() = 0; 
  bool isConnected() {return connected;}
protected:
  void setConnected(bool val) {connected = val;}
private:
  bool connected {false};
};

class OutputConnector;

class InputConnector : public Connector
{
public:
  bool isInput() override {return true;}
  bool isOutput() override {return false;}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  virtual bool isMidi() = 0;
  virtual bool isOsc() = 0;
  virtual bool isAudio() = 0;
  virtual bool isControl() = 0;
  OutputConnector &from;
};

class OutputConnector : public Connector
{
public:
  bool isInput() override {return false;}
  bool isOutput() override {return true;}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  virtual bool isMidi() = 0;
  virtual bool isOsc() = 0;
  virtual bool isAudio() = 0;
  virtual bool isControl() = 0; 
  std::map<juce::String, InputConnector&> to;
};

class MidiInputConnector : public InputConnector
{
public:
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return true;}
  bool isOsc() override {return false;}
  bool isAudio() override {return false;}
  bool isControl() override {return false;} 
};

class OscInputConnector : public InputConnector
{
public:
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return true;}
  bool isAudio() override {return false;}
  bool isControl() override {return false;} 
};

class AudioInputConnector : public InputConnector
{
public:
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return false;}
  bool isAudio() override {return true;}
  bool isControl() override {return false;} 
};

class ControlInputConnector : public InputConnector
{
public:
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return false;}
  bool isAudio() override {return false;}
  bool isControl() override {return true;} 
};

class MidiOutputConnector : public OutputConnector
{
public:
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return true;}
  bool isOsc() override {return false;}
  bool isAudio() override {return false;}
  bool isControl() override {return false;} 
};

class OscOutputConnector : public OutputConnector
{
public:
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return true;}
  bool isAudio() override {return false;}
  bool isControl() override {return false;} 
};

class AudioOutputConnector : public OutputConnector
{
public:
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return false;}
  bool isAudio() override {return true;}
  bool isControl() override {return false;} 
};

class ControlOutputConnector : public OutputConnector
{
public:
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return false;}
  bool isAudio() override {return false;}
  bool isControl() override {return true;} 
};


