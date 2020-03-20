/*
  ==============================================================================

    JunkCollection.h
    Created: 13 Mar 2020 3:31:00pm
    Author:  Kristján Eldjárn

  ==============================================================================
*/

#include <vector>       // std::vector
#include <cmath>        // std::hypot, std::round, std::min
#include <random>       // std::random_device, std::mt19937,
                        // std::chi_squared_distribution,
                        // std::uniform_real_distribution
#include <algorithm>    // std::generate

#include <JuceHeader.h>

#include "JunkYard.h" // JunkYard, loc_buf

#pragma once
class Junk {
public:
    Junk(JunkYard *junkyard=nullptr, float x=0., float y=0., int size=1);

    ~Junk();
    Junk(const Junk &other);
    Junk(Junk &&other);
    Junk& operator=(const Junk &other);
    Junk& operator=(Junk &&other);

    void setSize(int size);
    // (x, y) \in [-1, 1]
    void move(float x, float y);

    void setSlop(float slop);
    void setGain();
    void setGainMultiplier(float gain);
    void setOffset();

    void populate(JunkYard &junkyard);

    void trigger();
    void triggerAt(int time);

    void processBlock(AudioBuffer<float> &buffer);
private:
    int x, y, size;
    float gainMultiplier;
    JunkYard *junkyard;

    std::vector<AudioBuffer<float> > b_vec;
    std::vector<float> d_vec;

    std::vector<int> offset;
    std::vector<int> elapsed;
    std::vector<bool> triggered;

    float slop;
    std::random_device rd;
    std::mt19937 gen;
    std::chi_squared_distribution<> c_dis;
    // Maybe we want this to be a Gaussian
    std::uniform_real_distribution<> u_dis;
};
