//
//  spiketimelistel.h
//  Modelel1
//
//  Created by Ian Christie on 4/12/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__spiketimelistel__
#define __Modelel1__spiketimelistel__

#include <iostream>
#include <vector>
#include <map>
#include "modelel.h"
#include "string"
#include "set"

using namespace std;

class spiketimelistel : public modelel {
    protected:
        //attributes
        set<float> spiketimes;
    public:
    
        vector<float> getVectorInts(string s);
    
        string type = "spiketimelistel";
        //constructors
        spiketimelistel();
        spiketimelistel(set<float> _spiketimes);
        spiketimelistel(vector<string> fields, vector<string> data);
        spiketimelistel(map<string,string> data);
    
        //log
        string logData();
        string logReference();
        //setters and getters
        set<float>* getSpikeTimes();
        void setSpikeTimes(set<float> _v);
        void addSpike(float f);
        string getType();
    
        //other method
        bool contains(float f);
        void print();
};

#endif /* defined(__Modelel1__spiketimelistel__) */
