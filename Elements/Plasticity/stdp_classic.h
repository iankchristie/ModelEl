//
//  stdp_classic.h
//  Modelel1
//
//  Created by Ian Christie on 4/19/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__stdp_classic__
#define __Modelel1__stdp_classic__

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <math.h>
#include <algorithm>
#include "plasticity_methods.h"

using namespace std;

class stdp_classic: public plasticity_methods {
    protected:
        float tau_plus;
        float tau_minus;
        float A_plus;
        float A_minus;
    
        float T0;
    
    public:
        stdp_classic();
        stdp_classic(vector<string> fields, vector<string> data);
        stdp_classic(map<string,string> data);
        float updateGmax();
        //log
        string logData();
    
        //getters and setters
        float getTau_plus();
        void setTau_plus(float f);
        float getTau_minus();
        void setTau_minus(float f);
        float getA_plus();
        void setA_plus(float f);
        float getA_minus();
        void setA_minus(float f);
        float getT0();
        void setT0(float f);
        string getName();
        void print();

};

#endif /* defined(__Modelel1__stdp_classic__) */
