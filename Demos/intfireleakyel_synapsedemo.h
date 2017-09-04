//
//  intfireleakyel_synapsedemo.h
//  Modelel1
//
//  Created by Ian Christie on 5/1/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__intfireleakyel_synapsedemo__
#define __Modelel1__intfireleakyel_synapsedemo__

#include <iostream>
#include "Demo.h"
#include "spiketimelistel.h"
#include "intfireleakyel.h"
#include "synapse.h"
#include "synapset1t2.h"

using namespace std;

class intfireleakyel_synapsedemo: public Demo {
protected:
    spiketimelistel *preNeuron;
    intfireleakyel *postNeuron;
    synapse *syn;
    float dT;
    
public:
    //constructor
    intfireleakyel_synapsedemo();
    //getters and setters
    spiketimelistel* getPre();
    void setPre(spiketimelistel* _pre);
    
    intfireleakyel* getPost();
    void setPost(intfireleakyel* _post);
    
    synapse* getSynapse();
    void setSynapse(synapse* _s);
    
    float getDT();
    void setDT(float f);
    
    //parent stuff
    vector<modelel*> run(string lfp);
    void setDefaultSettings();
    void compress();
    
    //lazy
    void someSpikes();
    string lazy = "working";
    
};
#endif /* defined(__Modelel1__intfireleakyel_synapsedemo__) */
