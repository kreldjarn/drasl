/*
  ==============================================================================

    Slicer.cpp
    Created: 18 Mar 2020 10:47:33am
    Author:  Kristján Eldjárn

  ==============================================================================
*/

#include "Slicer.h"

Slicer::Slicer() : last_peak(0) {}

void Slicer::slice(AudioBuffer<float> &buffer,
                   std::vector<AudioBuffer<float> > &slices) {
    // TODO:
    // Handle case where b_len < window
    
    int b_len = buffer.getNumSamples();
    
    float rms = last_peak;
    
    for (int i = 0; i < b_len; i += window) {
        // Use max RMS across both channels
        rms = std::max(buffer.getRMSLevel(0, i, window),
                       buffer.getRMSLevel(1, i, window));
    }
}
