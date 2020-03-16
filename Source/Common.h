/*
  ==============================================================================

    Common.h
    Created: 13 Mar 2020 9:07:43pm
    Author:  Kristján Eldjárn

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct loc {
    float x, y;
    loc(float x, float y) : x(x), y(y) {}
};

typedef std::pair<loc, AudioBuffer<float> > loc_buf;
