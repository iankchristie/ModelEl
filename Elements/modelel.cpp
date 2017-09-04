//
//  modelel.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/10/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "modelel.h"

#pragma mark constructors
modelel::modelel() {
    T = 0.0;
    dT = .0001;
    name = "";
}

modelel::modelel(float _t, float _dT, string _name) {
    T = _t;
    dT = _dT;
    name = _name;
}

modelel::modelel(vector<string> fields, vector<string> data) {
    
    string temp;
    for(int k = 0; k < fields.size(); k++) {
        temp = fields.at(k);
        if(temp == "T") {
            T= atof(data.at(k).c_str());
        }
        if (temp == "dT") {
            dT = atof(data.at(k).c_str());
        }
        if (temp == "name") {
            name = data.at(k);
        }
    }
}

modelel::modelel(map<string,string> data) {
    T = atof(data["T"].c_str());
    dT = atof(data["dT"].c_str());
    name = data["name"];
    
    logMap = *new map<string, bool>();
    
    logMap["T"] = false;
    logMap["dT"] = false;
    logMap["name"] = false;
    
}

#pragma mark log methods
string modelel::logReference() {
    string temp="";
    for(auto k: logMap) {
        if (k.second) {
            if (k.first=="T") {
                temp+="T";
                temp+=";";
            }
            if (k.first=="dT") {
                temp+="dT";
                temp+=";";
            }
            if (k.first=="name") {
                temp+="name";
                temp+=";";
            }
        }
    }
    return temp;
}

string modelel::logData() {
    string temp="";
    for(auto k: logMap) {
        if (k.second) {
            if (k.first=="T") {
                temp+=tostr(T);
                temp+=";";
            }
            if (k.first=="dT") {
                temp+=tostr(dT);
                temp+=";";
            }
            if (k.first=="name") {
                temp+=name;
                temp+=";";
            }
        }
    }
    return temp;
}

#pragma mark gettters and setters
float modelel::getT() {
    return T;
}

void modelel::setT(float _T) {
    T = _T;
}

float modelel::getDT() {
    return dT;
}

void modelel::setDT(float _dT){
    dT = _dT;
}

string modelel::getName() {
    return name;
}

void modelel::setName(string _name){
    name = _name;
}

string modelel::getType() {
    return type;
}

#pragma mark functions
void modelel::step() {
    T += dT;
}

static double fRand(double fMin, double fMax) {
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void modelel::print() {
    cout << "Logging:\t" << logReference() << endl;
    cout << "modelel:" << endl;
    cout << "T:\t" << T << endl;
    cout << "dT:\t" << dT << endl;
    cout << "name:\t" << name << endl;
}