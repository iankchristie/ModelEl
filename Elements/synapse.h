//
//  synapse.h
//  Modelel1
//
//  Created by Ian Christie on 4/12/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__synapse__
#define __Modelel1__synapse__

//class intfireleakyel;

#include <iostream>
#include <vector>
#include <map>
#include "modelel.h"
#include "string"
#include "spiketimelistel.h"
#include "plasticity_methods.h"
#include "stdp_classic.h"
#include "stdp_triplet.h"

class synapse: public modelel {
    protected:
        float V_rev;
        float Gmax;
        float G;
        spiketimelistel *pre;
        spiketimelistel *post;
        float Tpast_ignore = 1;
        plasticity_methods *plasticity_method;
        
    public:
        const string type = "synapse";
        synapse();
        synapse(vector<string> fields, vector<string> data);
        synapse(map<string,string> data);
    
        //log
        string logData();
        string logReference();
    
        map<string,string> makeMap(string s);
        string getSeg(string s);
        string getNextStart(string s);
        vector<string> getFields(string s);
        vector<string> getData(string s);
        vector<string> getSegments(string s);
        int getIndex(string s, string find);
    
        virtual float getV_rev();
        virtual void setV_rev(float f);
        virtual float getGmax();
        virtual void setGmax(float f);
        virtual float getG();
        virtual void setG(float f);
        virtual spiketimelistel* getPre();
        virtual void setPre(spiketimelistel *v);
        virtual spiketimelistel* getPost();
        virtual void setPost(spiketimelistel *v);
        virtual float getTpast_ignore();
        virtual void setTpast_ignore(float f);
        virtual plasticity_methods* getPlasticity_method();
        virtual void setPlasticity_method(plasticity_methods* pm);
        virtual string getType();
    
        void connectPlasticityParams();
        void print();
};

#endif /* defined(__Modelel1__synapse__) */
