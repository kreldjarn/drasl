/*
  ==============================================================================

    JunkYard.h
    Created: 13 Mar 2020 5:47:02pm
    Author:  Kristján Eldjárn

  ==============================================================================
*/
#include <vector>       // std::vector
#include <random>       // std::random_device, std::mt19937,
                        // std::uniform_real_distribution
#include <numeric>      // std::iota
#include <algorithm>    // std::sort, std::min
#include <functional>   // std::bind, std::placeholders
#include <cmath>        // std::hypot

#include <JuceHeader.h>

#include "Common.h"     // loc_buf

const int MAX_N = 500;

#pragma once
class JunkYard {
public:
    JunkYard();
    ~JunkYard();
    void add(AudioBuffer<float> &buf);
    void clear();
    void getNearest(float x, float y, int n,
                    std::vector<AudioBuffer<float> > &b_vec,
                    std::vector<float> &dist) const;
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;
    
    std::vector<loc_buf> j_vec;
    size_t next_elem;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JunkYard)
};
