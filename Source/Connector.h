/*
  ==============================================================================

    Connector.h
    Created: 31 May 2021 9:43:31am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "Value.h"

class Node;

///
/// Connector - base class of connectors
///

class Connector 
{
public:
  Connector() {}
  Connector(juce::String nm, Node* o) {name = nm; owner = o;}
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
  juce::String name {"{unnamed}"};
  SCValue *value;
  Node* owner;
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
  InputConnector(juce::String nm, Node* o) : Connector(nm, o)  {}
  bool isInput() override {return true;}
  bool isOutput() override {return false;}
  virtual bool isMono() override = 0;
  virtual bool isPoly() override = 0;
  virtual bool isMidi() override = 0;
  virtual bool isOsc() override = 0;
  virtual bool isAudio() override = 0;
  virtual bool isControl() override = 0;
  OutputConnector* from;
};

///
/// OutputConnector - base class of output connectors
///

class OutputConnector : virtual public Connector
{
public:
  OutputConnector() {}
  OutputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isInput() override {return false;}
  bool isOutput() override {return true;}
  virtual bool isMono() override = 0;
  virtual bool isPoly() override = 0;
  virtual bool isMidi() override = 0;
  virtual bool isOsc() override = 0;
  virtual bool isAudio() override = 0;
  virtual bool isControl() override = 0; 
  std::map<juce::String, InputConnector*> to;
};

///
/// MidiInputConnector - base class of MIDI input connectors
///

class MidiInputConnector : virtual public InputConnector
{
public:
  MidiInputConnector() {}
  MidiInputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
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
  OscInputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  virtual bool isMono() override = 0;
  virtual bool isPoly() override = 0;
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
  AudioInputConnector(juce::String nm, Node* o) : Connector(nm, o)  {}
  virtual bool isMono() override = 0;
  virtual bool isPoly() override = 0;
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
  ControlInputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  virtual bool isMono() override = 0;
  virtual bool isPoly() override = 0; 
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
  MidiOutputConnector(juce::String nm, Node* o)  : Connector(nm, o)  {}
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
  OscOutputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() override {return true;}
  bool isPoly() override {return false;}
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
  AudioOutputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() override {return true;}
  bool isPoly() override {return false;}
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
  ControlOutputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() override {return true;}
  bool isPoly() override {return false;}
  bool isMidi() override {return false;}
  bool isOsc() override {return false;}
  bool isAudio() override {return false;}
  bool isControl() override {return true;} 
};

class MonoAudioInputConnector : virtual public AudioInputConnector
{
public:
  MonoAudioInputConnector() {}
  MonoAudioInputConnector(juce::String nm, Node* o) : Connector(nm, o) {}
  bool isMono() {return true;}
  bool isPoly() {return false;}
};

class MonoControlInputConnector : virtual public ControlInputConnector
{
public:
  MonoControlInputConnector() {}
  MonoControlInputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() {return true;}
  bool isPoly() {return false;}
};

class MonoAudioOutputConnector : virtual public AudioOutputConnector
{
public:
  MonoAudioOutputConnector() {}
  MonoAudioOutputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() {return true;}
  bool isPoly() {return false;}
};

class MonoControlOutputConnector : virtual public ControlOutputConnector
{
public:
  MonoControlOutputConnector() {}
  MonoControlOutputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() {return true;}
  bool isPoly() {return false;}
};

class PolyAudioInputConnector : virtual public AudioInputConnector
{
public:
  PolyAudioInputConnector() {}
  PolyAudioInputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() {return false;}
  bool isPoly() {return true;}
};

class PolyControlInputConnector : virtual public ControlInputConnector
{
public:
  PolyControlInputConnector() {}
  PolyControlInputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() {return false;}
  bool isPoly() {return true;}
};

class PolyAudioOutputConnector : virtual public AudioOutputConnector
{
public:
  PolyAudioOutputConnector() {}
  PolyAudioOutputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() {return false;}
  bool isPoly() {return true;}
};

class PolyControlOutputConnector : virtual public ControlOutputConnector
{
public:
  PolyControlOutputConnector() {}
  PolyControlOutputConnector(juce::String nm, Node* o) : Connector(nm, o)   {}
  bool isMono() {return false;}
  bool isPoly() {return true;}
};

class Connection
{
public:
  Connection(juce::String name="");
  OutputConnector* from;
  InputConnector* to;
  void connect(OutputConnector* f, InputConnector* t);

  void transfer() {to->value = from->value;}

  juce::String name;
};

class ConnectionTree : virtual public std::map<juce::String, Connection*>
{
public:
  void addConnection(Connection *conn);
  Connection *getByName(juce::String name);
};