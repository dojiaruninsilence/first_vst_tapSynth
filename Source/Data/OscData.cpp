/*
  ==============================================================================

    OscData.cpp
    Created: 28 Apr 2024 1:09:23pm
    Author:  Zubin

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    prepare(spec);
    gain.prepare(spec);
}

void OscData::setType(const int oscSelection) {
    switch (oscSelection) {
    // sine
    case 0:
        initialise([](float x) {return std::sin(x);});
        break;

    //saw
    case 1:
        initialise([](float x) {return x / juce::MathConstants<float>::pi;});
        break;

    // square
    case 2:
        initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f;});
        break;

    default:
        // you shouldnt be here
        jassertfalse;
        break;
    }
}

void OscData::setGain(const float levelInDecibels) {
    gain.setGainDecibels(levelInDecibels);
}

void OscData::setPitchVal(const int pitch) {
    pitchVal = pitch;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote + pitchVal));
}

void OscData::setFreq(const int midiNoteNumber) {
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber + pitchVal));
    lastMidiNote = midiNoteNumber;
}

void OscData::renderNextBlock(juce::dsp::AudioBlock<float>& audioBlock) {
    jassert(audioBlock.getNumChannels() > 0);
    process (juce::dsp::ProcessContextReplacing<float> (audioBlock));
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
}