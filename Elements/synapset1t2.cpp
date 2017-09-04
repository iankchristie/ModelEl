//
//  synapset1t2.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/18/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "synapset1t2.h"

synapset1t2::synapset1t2() {
    tau1 = 0.001;
    tau2 = 0.050;
}

synapset1t2::synapset1t2(vector<string> fields, vector<string> data) : synapse(fields,data){
    string temp;
    for (int k = 0; k < fields.size(); k++) {
        temp = fields.at(k);
        if (temp == "tau1") {
            tau1 = atof(data.at(k).c_str());
        }
        if (temp == "tau2") {
            tau2 = atof(data.at(k).c_str());
        }
    }
}

synapset1t2::synapset1t2(map<string,string> data):synapse(data) {
    tau1 = atof(data["tau1"].c_str());
    tau2 = atof(data["tau2"].c_str());
    
    logMap["tau1"] = false;
    logMap["tau2"] = false;
    
}

#pragma mark log

string synapset1t2::logReference() {
    string temp = synapse::logReference();
    for(auto k: logMap) {
        if (k.second) {
            if(k.first=="tau1") {
                temp+="tau1";
                temp+=";";
            }
            if(k.first=="tau12") {
                temp+="tau2";
                temp+=";";
            }
        }
    }
    return temp;
}

string synapset1t2::logData() {
    string temp = synapse::logData();
    for(auto k: logMap) {
        if (k.second) {
            if(k.first=="tau1") {
                temp+=tostr(tau1);
                temp+=";";
            }
            if(k.first=="tau12") {
                temp+=tostr(tau2);
                temp+=";";
            }
        }
    }
    return temp;
}

float synapset1t2::getTau1() {
    return tau1;
}
void synapset1t2::setTau1(float f) {
    tau1 = f;
}
float synapset1t2::getTau2() {
    return tau2;
}
void synapset1t2::setTau2(float f) {
    tau2 = f;
}

string synapset1t2::getType() {
    return type;
}

void synapset1t2::step() {
    if(pre == 0) {
        T+=dT;
        cout<<"THERE IS NO PRESYNAPTIC NEURON CONNECTED TO THIS SYNAPSE"<<endl;
        return;
    }
    
    vector<float> deltaT;
    set<float> vPre = *pre->getSpikeTimes();
    vector<float>::iterator it;
    set<float>::reverse_iterator rit;
    float sum =0.0;
    
    if(Tpast_ignore !=0) {
        for (rit = vPre.rbegin(); rit != vPre.rend(); ++rit) {
            if(*rit> T-Tpast_ignore) {
                deltaT.push_back(T-*rit);
            }
            else {
                break;
            }
        }
    }
    else {
        copy(vPre.begin(), vPre.end(), inserter(deltaT, deltaT.end()));
    }
    
    if (!deltaT.empty()) {
        //sanatize for only future
        it = deltaT.begin();
        while(it!= deltaT.end()) {
            if(*it < 0) {
                it = deltaT.erase(it);
            }
            else ++it;
        }
        
        //calculate G
        for (float f: deltaT) {
            sum += exp(-1*f/tau2)-exp(-1*f/tau1);
        }
        G = Gmax * sum;
    }
    else {
        G = 0.0;
    }
    T+=dT;
    
    /*if(plasticity_method!=NULL) {
        plasticity_method->setPre(pre);
        plasticity_method->setPost(post);
        Gmax = plasticity_method->updateGmax();
        cout << "Gmax: "<<Gmax << endl;
    }*/
}

void  synapset1t2::print() {
    synapse::print();
    cout << "synapset1t2:" << endl;
    cout << "Tau1:\t" << tau1 << endl;
    cout << "Tau2:\t" << tau2 << endl;
    
}

