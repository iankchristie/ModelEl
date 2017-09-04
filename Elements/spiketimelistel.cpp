//
//  spiketimelistel.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/12/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "spiketimelistel.h"

using namespace std;

#pragma mark constructors
spiketimelistel::spiketimelistel() {
    set<float> v;
    spiketimes = v;
}
spiketimelistel::spiketimelistel(set<float> _spiketimes) {
    spiketimes = _spiketimes;
}
spiketimelistel::spiketimelistel(vector<string> fields, vector<string> data): modelel(fields,data) {
    string temp;
    for (int k = 0; k < fields.size(); k++) {
        temp = fields.at(k);
        if (temp == "spiketimes") {
            vector<float> i = getVectorInts(data.at(k));
            spiketimes.insert(i.begin(),i.end());
        }
    }
}

spiketimelistel::spiketimelistel(map<string,string> data): modelel(data) {
    vector<float> i = getVectorInts(data["spiketimes"]);
    spiketimes.insert(i.begin(),i.end());
    
    logMap["spiketimes"] = false;
}

#pragma mark log
string spiketimelistel::logReference() {
    string temp = modelel::logReference();
    for(auto k: logMap) {
        if (k.second) {
            if (k.first=="spiketimes") {
                temp+="spiketimes";
                temp+=";";
            }
        }
    }
    return temp;
}

string spiketimelistel::logData() {
    string temp = modelel::logData();
    for(auto k: logMap) {
        if (k.second) {
            if (k.first=="spiketimes") {
                temp+="[";
                for(float f: spiketimes) {
                    temp+=tostr(f);
                    temp+=" ";
                }
                temp+="];";
            }
        }
    }
    return temp;
}

#pragma mark helper
vector<float> spiketimelistel::getVectorInts(string s) {
    vector<float> temp = *new vector<float>();
    if (s.length()==0) {
        return temp;
    }
    string t;
    for (int k = 0; k < s.length(); k++) {
        if (s.at(k)==' ') {
            temp.push_back(atof(t.c_str()));
            t.clear();
        }
        else {
            t+=s.at(k);
        }
    }
    
    temp.push_back(atof(t.c_str()));
    
    return temp;
}

#pragma mark getters and setters
set<float>* spiketimelistel::getSpikeTimes() {
    return &spiketimes;
}

void spiketimelistel::setSpikeTimes(set<float> _v) {
    spiketimes = _v;
}

void spiketimelistel::addSpike(float f) {
    spiketimes.insert(f);
}

string spiketimelistel::getType() {
    return type;
}

#pragma mark other
bool spiketimelistel::contains(float _f) {
    return spiketimes.find(_f) != spiketimes.end();
}

void spiketimelistel::print() {
    modelel::print();
    cout << "spiketimelistel:" << endl;
    for(float f: spiketimes) {
        cout << f << endl;
    }
}
