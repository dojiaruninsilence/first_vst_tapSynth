/*
  ==============================================================================

    SynthSound.h
    Created: 27 Apr 2024 2:47:25pm
    Author:  Zubin

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};