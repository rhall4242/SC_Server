/*
  ==============================================================================

    Connector.h
    Created: 31 May 2021 9:43:31am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

///
/// Connector - base class of connectors
///

class Connector 
{
public:
  Connector() {}
  Connector(juce::String nm) {name = nm;}
  virtual bool isInput() = 0;
  virtual bool isOutput() = 0;
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  virtual bool isMidi() = 0;
  virtual bool isOsc() = 0;
  virtual bool isAudio() = 0;
  virtual bool isControl() = 0; 
  bool isConnected() {return connected;}
  virtual void setConnected(bool v) {connected = v;}
  juce::String getName() {return name;}
// protected:
  juce::String name {"{unnamed}"};
private:
  bool connected {false};
};

class OutputConnector;

///
/// InputConnector - base class of input connectors
///

class InputConnector : virtual public Connector
{
public:
  InputConnector() {}
  InputConnector(juce::String nm) : Connector(nm)  {}
  bool isInput() override {return true;}
  bool isOutput() override {return false;}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  virtual bool isMidi() = 0;
  virtual bool isOsc() = 0;
  virtual bool isAudio() = 0;
  virtual bool isControl() = 0;
  OutputConnector* from;
};

///
/// OutputConnector - base class of output connectors
///

class OutputConnector : virtual public Connector
{
public:
  OutputConnector() {}
  OutputConnector(juce::String nm) : Connector(nm)   {}
  bool isInput() override {return false;}
  bool isOutput() override {return true;}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  virtual bool isMidi() = 0;
  virtual bool isOsc() = 0;
  virtual bool isAudio() = 0;
  virtual bool isControl() = 0; 
  std::map<juce::String, InputConnector*> to;
};

///
/// MidiInputConnector - base class of MIDI input connectors
///

class MidiInputConnector : virtual public InputConnector
{
public:
  MidiInputConnector() {}
  MidiInputConnector(juce::String nm) : Connector(nm)   {}
  bool isMono() override {return true;}
  bool isPoly() override {return false;}
  bool isMidi() override {return true;}
  bool isOsc() override {return false;}
  bool isAudio() override {return false;}
  bool isControl() override {return false;} 
};

///
/// OscInputConnector - base class of OSC input connectors
///

class OscInputConnector : virtual public InputConnector
{
public:
  OscInputConnector() {}
  OscInputConnector(juce::String nm) : Connector(nm)   {}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return true;}
  bool isAudio() override {return false;}
  bool isControl() override {return false;} 
};

///
/// AudioInputConnector - base class of audio input connectors
///

class AudioInputConnector : virtual public InputConnector
{
public:
  AudioInputConnector() {}
  AudioInputConnector(juce::String nm) : Connector(nm)  {}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return false;}
  bool isAudio() override {return true;}
  bool isControl() override {return false;} 
};

///
/// ControlConnector - base class of control input connectors
///

class ControlInputConnector : virtual public InputConnector
{
public:
  ControlInputConnector() {}
  ControlInputConnector(juce::String nm) : Connector(nm)   {}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0; 
  bool isMidi() override {return false;}
  bool isOsc() override {return false;}
  bool isAudio() override {return false;}
  bool isControl() override {return true;} 
};

///
/// MidiOutputConnector - base class of MIDI output connectors
///

class MidiOutputConnector : virtual public OutputConnector
{
public:
  MidiOutputConnector() {}
  MidiOutputConnector(juce::String nm)  : Connector(nm)  {}
  bool isMono() override {return true;}
  bool isPoly() override {return false;}
  bool isMidi() override {return true;}
  bool isOsc() override {return false;}
  bool isAudio() override {return false;}
  bool isControl() override {return false;} 
};

///
/// OscOutputConnector - base class of OSC output connectors
///

class OscOutputConnector : virtual public OutputConnector
{
public:
  OscOutputConnector() {}
  OscOutputConnector(juce::String nm) : Connector(nm)   {}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return true;}
  bool isAudio() override {return false;}
  bool isControl() override {return false;} 
};

///
/// AudioOutputConnector - base class of audio output connectors
///

class AudioOutputConnector : virtual public OutputConnector
{
public:
  AudioOutputConnector() {}
  AudioOutputConnector(juce::String nm) : Connector(nm)   {}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return false;}
  bool isAudio() override {return true;}
  bool isControl() override {return false;} 
};

///
/// ControlOutputConnector - base class of control output connectors
///

class ControlOutputConnector : virtual public OutputConnector
{
public:
  ControlOutputConnector() {}
  ControlOutputConnector(juce::String nm) : Connector(nm)   {}
  virtual bool isMono() = 0;
  virtual bool isPoly() = 0;
  bool isMidi() override {return false;}
  bool isOsc() override {return false;}
  bool isAudio() override {return false;}
  bool isControl() override {return true;} 
};

class MonoAudioInputConnector : virtual public AudioInputConnector
{
public:
  MonoAudioInputConnector() {}
  MonoAudioInputConnector(juce::String nm) : Connector(nm) {}
  bool isMono() {return true;}
  bool isPoly() {return false;}
};

class MonoControlInputConnector : virtual public ControlInputConnector
{
public:
  MonoControlInputConnector() {}
  MonoControlInputConnector(juce::String nm) : Connector(nm)   {}
  bool isMono() {return true;}
  bool isPoly() {return false;}
};

class MonoAudioOutputConnector : virtual public AudioOutputConnector
{
public:
  MonoAudioOutputConnector() {}
  MonoAudioOutputConnector(juce::String nm) : Connector(nm)   {}
  bool isMono() {return true;}
  bool isPoly() {return false;}
};

class MonoControlOutputConnector : virtual public ControlOutputConnector
{
public:
  MonoControlOutputConnector() {}
  MonoControlOutputConnector(juce::String nm) : Connector(nm)   {}
  bool isMono() {return true;}
  bool isPoly() {return false;}
};

class PolyAudioInputConnector : virtual public AudioInputConnector
{
public:
  PolyAudioInputConnector() {}
  PolyAudioInputConnector(juce::String nm) : Connector(nm)   {}
  bool isMono() {return false;}
  bool isPoly() {return true;}
};

class PolyControlInputConnector : virtual public ControlInputConnector
{
public:
  PolyControlInputConnector() {}
  PolyControlInputConnector(juce::String nm) : Connector(nm)   {}
  bool isMono() {return false;}
  bool isPoly() {return true;}
};

class PolyAudioOutputConnector : virtual public AudioOutputConnector
{
public:
  PolyAudioOutputConnector() {}
  PolyAudioOutputConnector(juce::String nm) : Connector(nm)   {}
  bool isMono() {return false;}
  bool isPoly() {return true;}
};

class PolyControlOutputConnector : virtual public ControlOutputConnector
{
public:
  PolyControlOutputConnector() {}
  PolyControlOutputConnector(juce::String nm) : Connector(nm)   {}
  bool isMono() {return false;}
  bool isPoly() {return true;}
};

class Connection
{
public:
  OutputConnector* from;
  InputConnector* to;
  void connect(OutputConnector* f, InputConnector* t);
};
