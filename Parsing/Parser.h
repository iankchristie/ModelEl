//
//  Parser.h
//  Modelel1
//
//  Created by Ian Christie on 9/8/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__Parser__
#define __Modelel1__Parser__

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include "modelel.h"
#include "spiketimelistel.h"
#include "intfireleakyel.h"
#include "synapse.h"
#include "synapset1t2.h"
#include "ToolBox.h"

using namespace std;

class Parser {
private:
    ToolBox toolBox;
    
public:
    
    vector<modelel*> createModel(string s);
    
    modelel* createEl(string s);
    
};

#endif /* defined(__Modelel1__Parser__) */
