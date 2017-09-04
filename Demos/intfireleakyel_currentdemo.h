//
//  intfireleakyel_currentdemo.h
//  Modelel1
//
//  Created by Ian Christie on 4/25/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__intfireleakyel_currentdemo__
#define __Modelel1__intfireleakyel_currentdemo__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include "Demo.h"
#include "intfireleakyel.h"

class intfireleakyel_currentdemo: public Demo {
    protected:
        float Ie;
        intfireleakyel *neuron;
        
    public:
        //constructor
        intfireleakyel_currentdemo();
        //parent stuff
        vector<modelel*> run();
        void setDefaultSettings();
        void compress();
    
        //getters and setters
        float getIe();
        void setCurrent(float f);
        intfireleakyel* getNeuron();
        void setNeuron(intfireleakyel* n);
        
};

#endif /* defined(__Modelel1__intfireleakyel_currentdemo__) */
