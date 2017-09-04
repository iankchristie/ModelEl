//
//  synapset1t2.h
//  Modelel1
//
//  Created by Ian Christie on 4/18/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__synapset1t2__
#define __Modelel1__synapset1t2__

#include <iostream>
#include <set>
#include <map>
#include "synapse.h"
#include "math.h"

class synapset1t2 : public synapse {
    protected:
        float tau1;
        float tau2;
    public:
        const string type = "synapset1t2";
        // constructor
        synapset1t2();
        synapset1t2(vector<string> fields, vector<string> data);
        synapset1t2(map<string,string> data);
        //log
        string logData();
        string logReference();
        //setters and getters
        float getTau1();
        void setTau1(float f);
        float getTau2();
        void setTau2(float f);
        string getType();
        void step();
        void print();
};

#endif /* defined(__Modelel1__synapset1t2__) */
