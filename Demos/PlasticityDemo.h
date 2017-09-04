//
//  PlasticityDemo.h
//  Modelel1
//
//  Created by Ian Christie on 5/14/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__PlasticityDemo__
#define __Modelel1__PlasticityDemo__

#include <iostream>
#include "Demo.h"
#include "spiketimelistel.h"
#include "intfireleakyel.h"
#include "synapse.h"
#include "synapset1t2.h"
#include "plasticity_methods.h"
#include "stdp_classic.h"

class PlasticityDemo: public Demo {
    protected:
        spiketimelistel *pre1;
        spiketimelistel *pre2;
    
        synapse* syn1;
        synapse* syn2;
    
        intfireleakyel *post;
    
    public:
        //constructor
        PlasticityDemo();
        //run
        vector<modelel*> run(string lfp);
        //parent
        void setDefaultSettings();
        void compress();
        //getters and setters
        spiketimelistel* getPre1();
        void setPre1(spiketimelistel* _n);
    
        spiketimelistel* getPre2();
        void setPre2(spiketimelistel* _n);
    
        intfireleakyel* getPost();
        void setPost(intfireleakyel* _n);
    
};

#endif /* defined(__Modelel1__PlasticityDemo__) */
