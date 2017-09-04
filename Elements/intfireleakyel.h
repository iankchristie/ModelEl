//
//  intfireleakyel.h
//  Modelel1
//
//  Created by Ian Christie on 4/12/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__intfireleakyel__
#define __Modelel1__intfireleakyel__

#include <iostream>
#include <vector>
#include <map>
#include "spiketimelistel.h"
#include "string"

#include "synapse.h"

class intfireleakyel : public spiketimelistel {
    protected:
        float Ie;
        float V_leak;
        float Rm;
        float Taum;
        float Area;
        float V_reset;
        float V_threshold;
        float V;
        float V_spike;
        vector<synapse*> synapse_list;
    public:
    friend synapse;
        const string type = "intfireleakyel";
        //constructor
        intfireleakyel();
        intfireleakyel(vector<string> fields, vector<string> data);
        intfireleakyel(map<string,string> data);
    
        //log
        string logData();
        string logReference();
        //getters and setters
        float getTaum();
        void setTaum(float f);
        float getIe();
        void setIe(float f);
        float getV_leak();
        void setV_leak(float f);
        float getArea();
        void setArea(float f);
        float getV_reset();
        void setV_reset(float f);
        float getV_threshold();
        void setV_threshold(float f);
        float getV();
        void setV(float f);
        float getV_spike();
        void setV_spike(float f);
        vector<synapse*> getSynapse_list();
        void setSynapse_list(vector<synapse*> v);
        void addSynapse(synapse *s);
        string getType();
        void step();
        void print();

};

#endif /* defined(__Modelel1__intfireleakyel__) */
