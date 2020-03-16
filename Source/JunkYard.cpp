/*
  ==============================================================================

    JunkYard.cpp
    Created: 13 Mar 2020 5:47:02pm
    Author:  Kristján Eldjárn

  ==============================================================================
*/

#include "JunkYard.h"

float dist(loc pos, float x, float y) {
    return std::hypot(pos.x-x, pos.y-y);
}

bool compare_dist_from_xy(int a, int b, std::vector<loc_buf> j, float x, float y) {
    return dist(j[a].first, x, y) < dist(j[b].first, x, y);
}

JunkYard::JunkYard() : next_elem(0) {
    gen = std::mt19937(rd());
    dis = std::uniform_real_distribution<>(-1., 1.);
    
    j_vec.reserve(MAX_N);
}

JunkYard::~JunkYard() {
    std::cout << "~JunkYard(): destructor" << std::endl;
}

void JunkYard::add(AudioBuffer<float> &buf) {
    // Generate random coordinates for new buffer
    loc l(dis(gen), dis(gen));
    loc_buf j(l, buf);
    // TODO:
    // If we have more than MAX_N buffers, we may want to start overwriting
    if (j_vec.size() >= MAX_N) return; //j_vec[next_elem] = j;
    else j_vec.push_back(j);
    std::cout << "JunkYard::add(): element added" << std::endl;
    std::cout << "JunkYard::add(): j_vec.size(): " << j_vec.size() << std::endl;
    next_elem = (next_elem + 1) % MAX_N;
}

void JunkYard::clear() {
    j_vec.clear();
    next_elem = 0;
}

void JunkYard::getNearest(float x, float y, int n,
                          std::vector<AudioBuffer<float> > &b_vec,
                          std::vector<float> &d_vec) const {
    std::cout << "JunkYard::getNearest(): address " << this << std::endl;
    std::cout << "JunkYard::getNearest(): n=" << n << std::endl;
    std::cout << "JunkYard::getNearest(): j_vec.size(): " << j_vec.size() << std::endl;
    // Generate indices and sort them in increasing distance from x, y
    std::vector<int> idx(j_vec.size());
    std::cout << "JunkYard::getNearest(): idx is " << idx.size() << " elements" << std::endl;
    std::iota(idx.begin(), idx.end(), 0);
    std::cout << "JunkYard::getNearest(): idx[";
    for (const auto i : idx) {
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
    std::sort(idx.begin(), idx.end(),
              std::bind(compare_dist_from_xy, std::placeholders::_1,
                        std::placeholders::_2, j_vec, x, y));
    
    std::cout << "JunkYard::getNearest(): idx[";
    for (const auto i : idx) {
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
    
    // Populate b_vec with pointers to the first min(n, j_vec.size()) buffers
    n = std::min(n, (int)j_vec.size());
    b_vec.clear();
    d_vec.clear();
    b_vec.reserve(n);
    d_vec.reserve(n);
    std::cout << "JunkYard::getNearest(): copying" << std::endl;
    for (int i = 0; i < n; ++i) {
        b_vec.push_back(j_vec[i].second);
        d_vec.push_back(dist(j_vec[i].first, x, y));
    }
    std::cout << "JunkYard::getNearest(): exiting" << std::endl;
}
