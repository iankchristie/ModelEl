//
//  DirectionalSelectivityDemo.h
//  Modelel1
//
//  Created by Ian Christie on 5/31/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__DirectionalSelectivityDemo__
#define __Modelel1__DirectionalSelectivityDemo__

#include <iostream>
#include <sstream> 
#include "Demo.h"
#include "intfireleakyel.h"
#include "synapset1t2.h"
#include "plasticity_methods.h"

class DirectionalSelectivityDemo: public Demo {
    protected:
        float dT;
        int nreps;
        float isi;
        float latency;  
        float lag;
        int N;
        int R;
        float Syn_Gmax_initial;
        plasticity_methods plasticity_method;
        float randomness;
        bool plotit;
        bool simit;
        bool simup;
        bool simdown;
    public:
        //constructor
        DirectionalSelectivityDemo();
    
        //parent stuff
        void setDefaultSettings();
        void compress();
        vector<modelel*> run(string lfp);
    
    
        //getters and setters
        float getDT();
        void setDT(float f);
    
        int getNReps();
        void setNReps(int i);
    
        float getISI();
        void setISI(float f);
    
        float getLatency();
        void setLatency(float f);
    
        float getLag();
        void setLag(float f);
    
        int getN();
        void setN(int i);
    
        int getR();
        void setR(int i);
    
        float getSyn_GMax_initial();
        void setSyn_GMax_initial(float f);

        plasticity_methods getPlasticityMethod();
        void setPlasticityMethod(plasticity_methods pm);

        float getRandomness();
        void setRandomness(float f);

        bool getPlotit();
        void setPlotit(bool b);

        bool getSimit();
        void setSimit(bool b);

        bool getSimup();
        void setSimup(bool b);

        bool getSimdown();
        void setSimdown(bool b);

};

#endif /* defined(__Modelel1__DirectionalSelectivityDemo__) */
