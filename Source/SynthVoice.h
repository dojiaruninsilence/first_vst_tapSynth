/*
  ==============================================================================

    SynthVoice.h
    Created: 27 Apr 2024 2:46:52pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPichWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer< float > &outputBuffer, int startSample, int numSamples) override;
private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;
    juce::AudioBuffer<float> synthBuffer;

    // sine wave
    //juce::dsp::Oscillator<float> osc{ [](float x) { return std::sin(x);} };

    // saw wave
    //juce::dsp::Oscillator<float> osc{ [](float x) { return x / juce::MathConstants<float>::pi;} };

    // square wave
    juce::dsp::Oscillator<float> osc{ [](float x) { return x < 0.0f ? -1.0f : 1.0f;} };
    juce::dsp::Gain<float> gain;

    bool isPrepared{ false };
};

