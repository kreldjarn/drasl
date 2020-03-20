/*
  ==============================================================================

    JunkCollection.cpp
    Created: 13 Mar 2020 3:31:00pm
    Author:  Kristján Eldjárn

  ==============================================================================
*/

#include "Junk.h"

Junk::Junk(JunkYard *junkyard, float x, float y, int size) : x(x), y(y), size(size), gainMultiplier(1.), slop(1000.) {
    std::cout << "Junk::Junk(): Junkyard pointer: " << junkyard << std::endl;
    if (junkyard) std::cout << "Junk::Junk(): j_vec.size(): " << junkyard->j_vec.size() << std::endl;
    gen = std::mt19937(rd());
    c_dis = std::chi_squared_distribution<>(4);
    u_dis = std::uniform_real_distribution<>(0, 1.);
    triggered.assign(size, 0);
    if (junkyard) setSize(size);
}

Junk::~Junk() {
    std::cout << "Junk::~Junk(): Destructor" << std::endl;
}

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
    this->size = size;
    std::cout << "Junk::setSize(): size=" << this->size << std::endl;
    b_vec.reserve(size);
    std::cout << "Junk::setSize(): exiting" << std::endl;
}

// (x, y) \in [-1, 1]
void Junk::move(float x, float y) {
    std::cout << "Junk::move()" << std::endl;
    x = x;
    y = y;
    std::cout << "Junk::move(): exiting" << std::endl;
}

void Junk::setSlop(float slop) {
    std::cout << "Junk::setSlop()" << std::endl;
    slop = slop;
    setOffset();
    std::cout << "slop: " << std::endl;
    std::cout << "Junk::setSlop(): exiting" << std::endl;
}

void Junk::setGain() {
    std::cout << "Junk::setGain()" << std::endl;
    auto b_gen = std::bind(std::uniform_int_distribution<>(0,1), gen);
    for (auto buf : b_vec) {
        int channel = b_gen();
        buf.applyGain(channel, 0, buf.getNumSamples(), u_dis(gen)*gainMultiplier);
        buf.applyGain(std::abs(channel - 1), 0, buf.getNumSamples(), gainMultiplier);
    }
    std::cout << "Junk::setGain(): exiting" << std::endl;
}

void Junk::setGainMultiplier(float gain) {
    gainMultiplier = gain;
    setGain();
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

void Junk::populate(JunkYard &junkyard) {
    std::cout << "Junk::populate()" << std::endl;
    std::cout << "Junk::populate(): size=" << size << std::endl;
    junkyard.getNearest(x, y, size, b_vec, d_vec);
    size = (int)b_vec.size();
    std::cout << "Junk::populate(): size=" << size << std::endl;
    // If there were fewer than size elements in junkyard
    std::cout << "Junk::populate(): b_vec is " << size << " elements" << std::endl;
    setGain();
    setOffset();
    std::cout << "Junk::populate(): exiting" << std::endl;
}

void Junk::trigger() {
    std::cout << "Junk::trigger()" << std::endl;
    triggered.assign(size, 1);
    std::cout << "triggered: ";
    for (const auto tr : triggered) {
        std::cout << tr << " ";
    }
    std::cout << std::endl;
    elapsed.assign(offset.begin(), offset.end());
    std::cout << "Junk::trigger(): exiting" << std::endl;
}

void Junk::triggerAt(int time) {
    std::cout << "Junk::triggerAt()" << std::endl;
    std::cout << "Junk::triggerAt(): size=" << size << std::endl;
    trigger();
    for (auto el : elapsed) el -= time;
    std::cout << "Junk::triggerAt(): elapsed:";
    for (auto el : elapsed) std::cout << el << " ";
    std::cout << std::endl;
    std::cout << "Junk::triggerAt(): exiting" << std::endl;
}

void Junk::processBlock(AudioBuffer<float> &buffer) {
    int d_len = buffer.getNumSamples();
    for (int i = 0; i < size; ++i) {
        int len = d_len;
        
        if (!triggered[i]) {
            // Sample has finished playing
            // =================================================
            continue;
        } else if (elapsed[i] < 0 && -elapsed[i] <= d_len) {
            std::cout << "Junk::processBlock(): " << i << " starting" << std::endl;
            std::cout << -elapsed[i] << " " << d_len << std::endl;
            // Sample starts playing in the current buffer frame
            // =================================================
            len = std::min(std::min(d_len, b_vec[i].getNumSamples()), d_len+elapsed[i]);
            
            // Assume both buffer and sample have at least two channels
            buffer.addFrom(0, -elapsed[i], b_vec[i], 0, 0, len);
            buffer.addFrom(1, -elapsed[i], b_vec[i], 1, 0, len);
        } else if (elapsed[i] >= 0) {
            std::cout << "Junk::processBlock(): " << i << " playing" << std::endl;
            // Sample has already started
            // =================================================
            len = std::min(b_vec[i].getNumSamples() - elapsed[i], buffer.getNumSamples());
            
            // Assume both buffer and sample have at least two channels
            buffer.addFrom(0, 0, b_vec[i], 0, elapsed[i], len);
            buffer.addFrom(1, 0, b_vec[i], 1, elapsed[i], len);
        }
        
        elapsed[i] += len;
        if (elapsed[i] >= b_vec[i].getNumSamples()) {
            std::cout << "Junk::processBlock(): " << i << " stopping" << std::endl;
            // Stop sample once it's played through once
            triggered[i] = 0;
        }
    }
}
