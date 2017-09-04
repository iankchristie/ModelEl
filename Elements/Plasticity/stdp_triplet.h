//
//  stdp_triplet.h
//  Modelel1
//
//  Created by Ian Christie on 4/24/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__stdp_triplet__
#define __Modelel1__stdp_triplet__

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <math.h>
#include "plasticity_methods.h"


using namespace std;

class stdp_triplet: public plasticity_methods {
    protected:
        float tau_plus;
        float tau_minus;
        float tau_x;
        float tau_y;
        float A2_plus;
        float A2_minus;
    
        float A3_plus;
        float A3_minus;
    
        float T0;
    
    public:
        stdp_triplet();
        stdp_triplet(vector<string> fields, vector<string> data);
        stdp_triplet(map<string,string> data);
    
        //log
        string logData();
    
        float updateGmax();
        float getTau_plus();
        void setTau_plus(float f);
    
        float getTau_minus();
        void setTau_minus(float f);
    
        float getTau_x();
        void setTau_x(float f);
    
        float getTau_y();
        void setTau_y(float f);
    
        float getA2_plus();
        void setA2_plus(float f);
    
        float getA2_minus();
        void setA2_minus(float f);
    
        float getA3_plus();
        void setA3_plus(float f);
    
        float getA3_minus();
        void setA3_minus(float f);
    
        float getT0();
        void setT0(float f);
    
        string getName();
        void print();
};

#endif /* defined(__Modelel1__stdp_triplet__) */
