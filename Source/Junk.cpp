/*
  ==============================================================================

    JunkCollection.cpp
    Created: 13 Mar 2020 3:31:00pm
    Author:  Kristján Eldjárn

  ==============================================================================
*/

#include "Junk.h"

Junk::Junk(JunkYard *junkyard, float x, float y, int size) : x(x), y(y), slop(2.) {
    std::cout << "Junkyard pointer: " << junkyard << std::endl;
    gen = std::mt19937(rd());
    c_dis = std::chi_squared_distribution<>(4);
    u_dis = std::uniform_real_distribution<>(0, 1.);
    if (junkyard) setSize(size);
}

Junk::~Junk() {}

Junk::Junk(const Junk &other) {
    x = other.x; y = other.y; size = other.size;
    junkyard = other.junkyard;
    b_vec = other.b_vec;
    d_vec = other.d_vec;
    
    offset = other.offset;
    elapsed = other.elapsed;
    triggered = other.triggered;
    
    slop = other.slop;
    gen = other.gen;
    c_dis = other.c_dis;
    u_dis = other.u_dis;
}

Junk::Junk(Junk &&other) {
    x = other.x; y = other.y; size = other.size;
    junkyard = other.junkyard;
    other.junkyard = nullptr;
    
    b_vec = std::move(other.b_vec);
    d_vec = std::move(other.d_vec);
    
    offset = std::move(other.offset);
    elapsed = std::move(other.elapsed);
    triggered = std::move(other.triggered);
    
    slop = other.slop;
    gen = std::move(other.gen);
    c_dis = std::move(other.c_dis);
    u_dis = std::move(other.u_dis);
}

Junk& Junk::operator=(const Junk &other) {
    if (&other == this) return *this;
    
    x = other.x; y = other.y; size = other.size;
    junkyard = other.junkyard;
    b_vec = other.b_vec;
    d_vec = other.d_vec;
    
    offset = other.offset;
    elapsed = other.elapsed;
    triggered = other.triggered;
    
    slop = other.slop;
    gen = other.gen;
    c_dis = other.c_dis;
    u_dis = other.u_dis;
    
    return *this;
}

Junk& Junk::operator=(Junk &&other) {
    if (&other == this) return *this;
    
    x = other.x; y = other.y; size = other.size;
    junkyard = other.junkyard;
    other.junkyard = nullptr;
    
    b_vec = std::move(other.b_vec);
    d_vec = std::move(other.d_vec);
    
    offset = std::move(other.offset);
    elapsed = std::move(other.elapsed);
    triggered = std::move(other.triggered);
    
    slop = other.slop;
    gen = std::move(other.gen);
    c_dis = std::move(other.c_dis);
    u_dis = std::move(other.u_dis);
    
    return *this;
}

void Junk::setSize(int size) {
    std::cout << "Junk::setSize()" << std::endl;
    size = size;
    b_vec.reserve(size);
    move(x, y);
    std::cout << "Junk::setSize(): exiting" << std::endl;
}

// (x, y) \in [-1, 1]
void Junk::move(float x, float y) {
    std::cout << "Junk::move()" << std::endl;
    x = x;
    y = y;
    junkyard->getNearest(x, y, size, b_vec, d_vec);
    // If there were fewer than size elements in junkyard
    size = (int)b_vec.size();
    std::cout << "Junk::move(): b_vec is " << size << " elements" << std::endl;
    setGain();
    setOffset();
    std::cout << "Junk::move(): exiting" << std::endl;
}

void Junk::setSlop(float slop) {
    std::cout << "Junk::setSlop()" << std::endl;
    slop = slop;
    setOffset();
    std::cout << "Junk::setSlop(): exiting" << std::endl;
}

void Junk::setGain() {
    std::cout << "Junk::setGain()" << std::endl;
    auto b_gen = std::bind(std::uniform_int_distribution<>(0,1), gen);
    for (auto buf : b_vec) {
        buf.applyGain(b_gen(), 0, buf.getNumSamples(), u_dis(gen));
    }
    std::cout << "Junk::setGain(): exiting" << std::endl;
}

void Junk::setOffset() {
    std::cout << "Junk::setOffset()" << std::endl;
    offset.clear();
    offset.reserve(size);
    elapsed.clear();
    elapsed.reserve(size);
    for (int i = 0; i < size; ++i) {
        int start = -std::round(c_dis(gen) * slop);
        offset.push_back(start);
        elapsed.push_back(start);
    }
    std::cout << "Junk::setOffset(): exiting" << std::endl;
}

void Junk::trigger() {
    std::cout << "Junk::trigger()" << std::endl;
    triggered.assign(size, 1);
    elapsed.assign(offset.begin(), offset.end());
    std::cout << "Junk::trigger(): exiting" << std::endl;
}

void Junk::triggerAt(int time) {
    std::cout << "Junk::triggerAt()" << std::endl;
    trigger();
    for (auto el : elapsed) el -= time;
    std::cout << "Junk::triggerAt(): exiting" << std::endl;
}

void Junk::processBlock(AudioBuffer<float> &buffer) {
    int d_len = buffer.getNumSamples();
    for (int i = 0; i < size; ++i) {
        int len = buffer.getNumSamples();
        
        if (!triggered[i]) {
            // Sample has finished playing
            // =================================================
            continue;
        } else if (elapsed[i] < 0 && -elapsed[i] <= d_len) {
            // Sample starts playing in the current buffer frame
            // =================================================
            len = std::min(std::min(d_len, b_vec[i].getNumSamples()), d_len+elapsed[i]);
            
            // Assume both buffer and sample have at least two channels
            buffer.addFrom(0, -elapsed[i], b_vec[i], 0, 0, len);
            buffer.addFrom(1, -elapsed[i], b_vec[i], 1, 0, len);
        } else {
            // Sample has already started
            // =================================================
            len = std::min(b_vec[i].getNumSamples() - elapsed[i], buffer.getNumSamples());
            
            // Assume both buffer and sample have at least two channels
            buffer.addFrom(0, 0, b_vec[i], 0, elapsed[i], len);
            buffer.addFrom(1, 0, b_vec[i], 1, elapsed[i], len);
        }
        
        elapsed[i] += len;
        if (elapsed[i] >= b_vec[i].getNumSamples()) {
            // Stop sample once it's played through once
            triggered[i] = 0;
        }
    }
}
