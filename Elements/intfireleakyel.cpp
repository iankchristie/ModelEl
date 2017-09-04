//
//  intfireleakyel.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/12/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "intfireleakyel.h"

using namespace std;

intfireleakyel::intfireleakyel() {
    Ie = 0;
    V_leak = -0.075;
    Rm=10e6;
    Taum=10e-3;
    Area = 0.1;
    V_reset = -0.080;
    V_threshold = -0.055;
    V = -0.075;
    V_spike = 0.010;
}

intfireleakyel::intfireleakyel(vector<string> fields, vector<string> data) : spiketimelistel(fields,data) {
    string temp;
    for (int k = 0; k < fields.size(); k++) {
        temp = fields.at(k);
        if (temp == "Ie") {
            Ie = atof(data.at(k).c_str());
        }
        if (temp == "V_leak") {
           V_leak = atof(data.at(k).c_str());
        }
        if (temp == "Rm") {
          Rm  = atof(data.at(k).c_str());
        }
        if (temp == "Taum") {
          Taum  = atof(data.at(k).c_str());
        }
        if (temp == "Area") {
          Area  = atof(data.at(k).c_str());
        }
        if (temp == "V_reset") {
          V_reset  = atof(data.at(k).c_str());
        }
        if (temp == "V_threshold") {
          V_threshold  = atof(data.at(k).c_str());
        }
        if (temp == "V") {
          V  = atof(data.at(k).c_str());
        }
        if (temp == "V_spike") {
          V_spike  = atof(data.at(k).c_str());
        }
    }
}

intfireleakyel::intfireleakyel(map<string,string> data):spiketimelistel(data) {
    Ie = atof(data["Ie"].c_str());
    V_leak = atof(data["V_leak"].c_str());
    Rm = atof(data["Rm"].c_str());
    Taum = atof(data["Taum"].c_str());
    Area = atof(data["Area"].c_str());
    V_reset = atof(data["V_reset"].c_str());
    V_threshold = atof(data["V_threshold"].c_str());
    V = atof(data["V"].c_str());
    V_spike = atof(data["V_spike"].c_str());
    
    logMap["Ie"] = false;
    logMap["V_leak"] = false;
    logMap["Rm"] = false;
    logMap["Taum"] = false;
    logMap["Area"] = false;
    logMap["V_reset"] = false;
    logMap["V_threshold"] = false;
    logMap["V"] = false;
    logMap["V_spike"] = false;
}

#pragma mark log

string intfireleakyel::logReference() {
    string temp = spiketimelistel::logReference();
    for(auto k: logMap) {
        if (k.second) {
            if(k.first=="Ie") {
                temp+="Ie";
                temp+=";";
            }
            if(k.first=="V_leak") {
                temp+="V_leak";
                temp+=";";
            }
            if(k.first=="Rm") {
                temp+="Rm";
                temp+=";";
            }
            if(k.first=="Taum") {
                temp+="Taum";
                temp+=";";
            }
            if(k.first=="Area") {
                temp+="Area";
                temp+=";";
            }
            if(k.first=="V_reset") {
                temp+="V_reset";
                temp+=";";
            }
            if(k.first=="V_threshold") {
                temp+="V_threshold";
                temp+=";";
            }
            if(k.first=="V") {
                temp+="V";
                temp+=";";
            }
            if(k.first=="V_spike") {
                temp+="V_spike";
                temp+=";";
            }
        }
    }
    return temp;
}

string intfireleakyel::logData() {
    string temp = spiketimelistel::logData();
    for(auto k: logMap) {
        if (k.second) {
            if(k.first=="Ie") {
                temp+=tostr(Ie);
                temp+=";";
            }
            if(k.first=="V_leak") {
                temp+=tostr(V_leak);
                temp+=";";
            }
            if(k.first=="Rm") {
                temp+=tostr(Rm);
                temp+=";";
            }
            if(k.first=="Taum") {
                temp+=tostr(Taum);
                temp+=";";
            }
            if(k.first=="Area") {
                temp+=tostr(Area);
                temp+=";";
            }
            if(k.first=="V_reset") {
                temp+=tostr(V_reset);
                temp+=";";
            }
            if(k.first=="V_threshold") {
                temp+=tostr(V_threshold);
                temp+=";";
            }
            if(k.first=="V") {
                temp+=tostr(V);
                temp+=";";
            }
            if(k.first=="V_spike") {
                temp+=tostr(V_spike);
                temp+=";";
            }
        }
    }
    return temp;
}

#pragma mark getters and setters
float intfireleakyel::getTaum() {
    return Taum;
}
void intfireleakyel::setTaum(float f) {
    Taum = f;
}
float intfireleakyel::getIe() {
    return Ie;
}
void intfireleakyel::setIe(float f) {
    Ie = f;
}
float intfireleakyel::getV_leak() {
    return V_leak;
}
void intfireleakyel::setV_leak(float f) {
    V_leak = f;
}
float intfireleakyel::getArea() {
    return Area;
}
void intfireleakyel::setArea(float f) {
    Area = f;
}
float intfireleakyel::getV_reset() {
    return V_reset;
}
float intfireleakyel::getV() {
    return V;
}
void intfireleakyel::setV(float f) {
    V=f;
}
void intfireleakyel::setV_reset(float f) {
    V_reset = f;
}
float intfireleakyel::getV_threshold() {
    return V_threshold;
}
void intfireleakyel::setV_threshold(float f) {
    V_threshold = f;
}
float intfireleakyel::getV_spike() {
    return V_spike;
}
void intfireleakyel::setV_spike(float f) {
    V_spike = f;
}
vector<synapse*> intfireleakyel::getSynapse_list() {
    return synapse_list;
}
void intfireleakyel::setSynapse_list(vector<synapse*> v) {
    synapse_list = v;
 }
void intfireleakyel::addSynapse(synapse *s) {
    synapse_list.push_back(s);
}
string intfireleakyel::getType() {
    return type;
}

#pragma mark step function
void intfireleakyel::step() {
    float dVsyn =0.0;
    float dVdt = 0.0;
    if(V >= V_spike) {
        V=V_reset;
    }
    
    for(synapse *s: synapse_list) {
        dVsyn -= (Rm/Area) * s->getG() * (V- s->getV_rev());
    }
    
    dVdt = (-1*(V-V_leak)+dVsyn+Ie*Rm)/Taum;
    
    V += dVdt * dT;
    T+=dT;
    
    //We're SPIKINGGGG!!!!
    if(V>V_threshold) {
        V = V_spike;
        spiketimes.insert(T);
        cout << "Time: "<< T <<"\tSpike: " << T << endl;
    }
}

void intfireleakyel::print() {
    spiketimelistel::print();
    cout << "intfireleakyel:" << endl;
    cout << "Ie:\t" << Ie << endl;
    cout << "V_leak:\t" << V_leak << endl;
    cout << "Rm:\t" << Rm << endl;
    cout << "Taum:\t" << Taum << endl;
    cout << "Area:\t" << Area << endl;
    cout << "V_reset:\t" << V_reset << endl;
    cout << "V_threshold:\t" << V_threshold << endl;
    cout << "V:\t" << V << endl;
    cout << "V_spike:\t" << V_spike << endl;
}