//
//  stdp_triplet.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/24/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "stdp_triplet.h"

#pragma mark constuctor
stdp_triplet::stdp_triplet() {
    tau_plus = 0.01668;
    tau_minus = 0.0337;
    tau_x = 0.101;
    tau_y = 0.125;
    A2_plus = 5e-5;
    A2_minus = 7e-3;
    
    A3_plus = 6.2e-3;
    A3_minus = 2.3e-4;
    
    T0 = 0;
}

stdp_triplet::stdp_triplet(vector<string> fields, vector<string> data):plasticity_methods(fields, data) {
    string temp;
    for (int k = 0; k < fields.size(); k++) {
        temp = fields.at(k);
        if (temp=="tau_plus") {
            tau_plus = atof(data.at(k).c_str());
        }
        if (temp=="tau_minus") {
            tau_minus= atof(data.at(k).c_str());
        }
        if (temp=="tau_x") {
            tau_x = atof(data.at(k).c_str());
        }
        if (temp=="tau_y") {
            tau_y= atof(data.at(k).c_str());
        }
        if (temp=="A2_plus") {
            A2_plus= atof(data.at(k).c_str());
        }
        if (temp=="A2_minus") {
            A2_minus= atof(data.at(k).c_str());
        }
        if (temp=="A3_plus") {
            A3_plus= atof(data.at(k).c_str());
        }
        if (temp=="A3_minus") {
            A3_minus= atof(data.at(k).c_str());
        }
        if (temp=="T0") {
            T0= atof(data.at(k).c_str());
        }
    }
}

stdp_triplet::stdp_triplet(map<string,string> data):plasticity_methods(data) {
    tau_plus = atof(data["tau_plus"].c_str());
    tau_minus = atof(data["tau_minus"].c_str());
    tau_x = atof(data["tau_x"].c_str());
    tau_y = atof(data["tau_y"].c_str());
    A2_plus = atof(data["A2_plus"].c_str());
    A2_minus = atof(data["A2_minus"].c_str());
    A3_plus = atof(data["A3_plus"].c_str());
    A3_minus = atof(data["A3_minus"].c_str());
    T0 = atof(data["T0"].c_str());
}

#pragma mark fire method
float stdp_triplet::updateGmax() {
    //create whats necessary
    float weight = 0.0;
    set<float> s;
    vector<float> dT;
    vector<float> triplet_dT;
    set<float> vPre = *pre->getSpikeTimes();
    set<float> vPost = *post->getSpikeTimes();
    set<float>::reverse_iterator rit;
    
    vector<float> post_times;
    vector<float> pre_times;
    
    float doublet = 0.0;
    float triplet = 0.0;
    
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
    
    //start algorithm
    for(float f: s) {
        //post before pre
        if (pre->contains(f)) {
            for(float k: vPost) {
                if(k <= f) {
                    dT.push_back(f-k);
                }
            }
            for(float k: vPre) {
                if(k < f) {  //strictly less!!!
                    triplet_dT.push_back(f-k);
                }
            }
            doublet = 0.0;
            for (float k: dT) {
                doublet += exp(-1*k/tau_minus);
            }
            triplet = 0.0;
            for (float k: triplet_dT) {
                triplet += exp(-1*k/tau_x);
            }
            weight += -1*doublet*(A2_minus+A3_minus*triplet);
            dT.clear();
            triplet_dT.clear();
        }
        //pre before post
        if (post->contains(f)) {
            for(float k: vPre) {
                if(k <= f) {
                    dT.push_back(k -f);
                }
            }
            for(float k: vPost) {
                if(k < f) { //strictly less
                    triplet_dT.push_back(f- k);
                }
            }
            doublet = 0.0;
            for(float k: dT) {
                doublet += exp(k / tau_plus);
            }
            triplet = 0.0;
            for(float k: triplet_dT) {
                triplet += exp(-1*k / tau_y);
            }
            weight += doublet * (A2_plus+A3_plus*triplet);
            dT.clear();
            triplet_dT.clear();
        }
    }
    return weight;
}

#pragma mark getters and setters
float stdp_triplet::getTau_plus() {
    return tau_plus;
}
void stdp_triplet::setTau_plus(float f) {
    tau_plus = f;
}
float stdp_triplet::getTau_minus() {
    return tau_minus;
}
void stdp_triplet::setTau_minus(float f) {
    tau_minus = f;
}
float stdp_triplet::getTau_x() {
    return tau_x;
}
void stdp_triplet::setTau_x(float f) {
    tau_x = f;
}
float stdp_triplet::getTau_y() {
    return tau_y;
}
void stdp_triplet::setTau_y(float f) {
    tau_y = f;
}
float stdp_triplet::getA2_plus() {
    return A2_plus;
}
void stdp_triplet::setA2_plus(float f) {
    A2_plus = f;
}
float stdp_triplet::getA2_minus() {
    return A2_minus;
}
void stdp_triplet::setA2_minus(float f) {
    A2_minus = f;
}
float stdp_triplet::getA3_plus() {
    return A3_plus;
}
void stdp_triplet::setA3_plus(float f) {
    A3_plus = f;
}
float stdp_triplet::getA3_minus() {
    return A3_minus;
}
void stdp_triplet::setA3_minus(float f) {
    A3_minus = f;
}
float stdp_triplet::getT0() {
    return T0;
}
void stdp_triplet::setT0(float f) {
    T0 = f;
}

string stdp_triplet::getName() {
    return "stdp_triplet";
}

void stdp_triplet::print() {
    cout << "tau_plus:\t" << tau_plus << endl;
    cout << "tau_minus:\t" << tau_minus << endl;
    cout << "tau_x:\t" << tau_x << endl;
    cout << "tau_y:\t" << tau_y << endl;
    cout << "A2_plus:\t" << A2_plus << endl;
    cout << "A2_minus:\t" << A2_minus << endl;
    cout << "A3_plus:\t" << A3_plus << endl;
    cout << "A3_minus:\t" << A3_minus << endl;
    cout << "T0:\t" << T0 << endl;
    plasticity_methods::print();
}