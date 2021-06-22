/*
  ==============================================================================

    SynthVoice.h
    Created: 5 Jun 2021 9:52:57am
    Author:  rhall

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Synth.h"
#include "SynthSound.h"
#include "MidiInputNode.h"
#include "AudioOutputNode.h"
#include "PluginProcessor.h"

class SynthVoice : public juce::SynthesiserVoice
{

  public:
    SynthVoice(Synth* s);
    bool canPlaySound(juce::SynthesiserSound *sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannel);
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    void update(const float attack, const float decay, const float sustain, const float release);
    NodeTree nodeTree;
    void nodeInit();


  private:

    Synth* synth;
    juce::AudioBuffer<float> synthBuffer;

    juce::dsp::Gain<float> gain;

    bool isPrepared {false };

};