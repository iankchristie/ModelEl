//
//  stdp_classic.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/19/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "stdp_classic.h"

stdp_classic::stdp_classic() {
    tau_plus = 0.020;
    tau_minus = 0.020;
    A_plus = 0.005;
    A_minus = 0.005250;
    
    T0 = 0.0;
}

stdp_classic::stdp_classic(vector<string> fields, vector<string> data):plasticity_methods(fields, data) {
    string temp;
    for (int k = 0; k < fields.size(); k++) {
        temp = fields.at(k);
        if (temp=="tau_plus") {
            tau_plus = atof(data.at(k).c_str());
        }
        if (temp=="tau_minus") {
            tau_minus= atof(data.at(k).c_str());
        }
        if (temp=="A_plus") {
            A_plus= atof(data.at(k).c_str());
        }
        if (temp=="A_minus") {
            A_minus= atof(data.at(k).c_str());
        }
        if (temp=="T0") {
            T0= atof(data.at(k).c_str());
        }
    }
}

stdp_classic::stdp_classic(map<string,string> data):plasticity_methods(data) {
    tau_plus = atof(data["tau_plus"].c_str());
    tau_minus= atof(data["tau_minus"].c_str());
    A_plus= atof(data["A_plus"].c_str());
    A_minus= atof(data["A_minus"].c_str());
    T0= atof(data["T0"].c_str());
}

float stdp_classic::updateGmax() {
    //create whats necessary
    float weight = 0.0;
    set<float> s;
    vector<float> temp;
    set<float> vPre = *pre->getSpikeTimes();
    set<float> vPost = *post->getSpikeTimes();
    set<float>::reverse_iterator rit;
    
    //load spiketimes into set
    for (rit = vPre.rbegin(); rit != vPre.rend(); ++rit) {
        if(*rit>=T0) {
            s.insert(*rit);
        }
        else {
            break;
        }
    }
    for (rit = vPost.rbegin(); rit != vPost.rend(); ++rit) {
        if(*rit>=T0) {
            s.insert(*rit);
        }
        else {
            break;
        }
    }
    
    //DO actual algorithm
    for (float f: s) {
        if (pre->contains(f)) {
            for (float k: vPost) {
                if(k <= f) {
                    temp.push_back(f-k);
                }
                else {
                    break;
                }
            }
            for(float k: temp) {
                weight += (-1*A_minus*exp((-1*k)/tau_minus));
            }
            temp.clear();
        }
        if (post->contains(f)) {
            for (float k: vPre) {
                if(k <= f) {
                    temp.push_back(k-f);
                }
                else {
                    break;
                }
            }
            for(float k: temp) {
                weight += (A_plus*exp(k/tau_plus));
            }
            temp.clear();
        }
    }
    return weight;
}


#pragma mark getters and setters
float stdp_classic::getTau_plus() {
    return tau_plus;
}
void stdp_classic::setTau_plus(float f) {
    tau_plus = f;
}
float stdp_classic::getTau_minus() {
    return tau_minus;
}
void stdp_classic::setTau_minus(float f) {
    tau_minus = f;
}
float stdp_classic::getA_plus() {
    return A_plus;
}
void stdp_classic::setA_plus(float f) {
    A_plus = f;
}
float stdp_classic::getA_minus() {
    return A_minus;
}
void stdp_classic::setA_minus(float f) {
    A_minus = f;
}
float stdp_classic::getT0() {
    return T0;
}
void stdp_classic::setT0(float f) {
    T0 = f;
}

string stdp_classic::getName() {
    return "stdp_classic";
}

void stdp_classic::print() {
    cout << "tau_plus:\t" << tau_plus << endl;
    cout << "tau_minus:\t" << tau_minus << endl;
    cout << "A_plus:\t" << A_plus << endl;
    cout << "A_minus:\t" << A_minus << endl;
    cout << "T0:\t" << T0 << endl;
    plasticity_methods::print();
}
