//
//  Demo.h
//  Modelel1
//
//  Created by Ian Christie on 5/4/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__Demo__
#define __Modelel1__Demo__

#include <iostream>
#include <fstream>
#include "modelel.h"
#include "vector"

using namespace std;

class Demo {
    protected:
        vector<modelel*> model;
        virtual void compress();
        virtual void setElementDT(float f);
    public:
        virtual vector<modelel*> run(string lfp);
        virtual void setDefaultSettings();
};

#endif /* defined(__Modelel1__Demo__) */
