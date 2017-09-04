//
//  plasticity_methods.h
//  Modelel1
//
//  Created by Ian Christie on 4/19/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__plasticity_methods__
#define __Modelel1__plasticity_methods__

#include <iostream>
#include <map>
#include "spiketimelistel.h"

class plasticity_methods {
    protected:
        spiketimelistel *pre;
        spiketimelistel *post;
    public:
        plasticity_methods();
        plasticity_methods(vector<string> fields, vector<string> data);
        plasticity_methods(map<string,string> data);
        virtual float updateGmax(); //returns weighted value of snapse
        //log
        string logData();
        virtual spiketimelistel* getPre();
        virtual void setPre(spiketimelistel* p);
        virtual spiketimelistel* getPost();
        virtual void setPost(spiketimelistel* p);
        virtual string getName();
        void print();
    
};

#endif /* defined(__Modelel1__plasticity_methods__) */
