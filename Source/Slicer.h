/*
  ==============================================================================

    Slicer.h
    Created: 18 Mar 2020 10:47:33am
    Author:  Kristján Eldjárn

  ==============================================================================
*/

#pragma once

#include <vector>   // std::vector
#include <cmath>    // std::max

#include <JuceHeader.h>

const int window = 0;

class Slicer {
public:
    Slicer();
    void slice(AudioBuffer<float> &buffer,
               std::vector<AudioBuffer<float> > &slices);
private:
    float last_peak;
    bool trigger;
};
