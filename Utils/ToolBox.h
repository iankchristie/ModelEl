//
//  ToolBox.h
//  Modelel1
//
//  Created by Ian Christie on 9/25/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__ToolBox__
#define __Modelel1__ToolBox__

#include <iostream>
#include <map>
#include "synapse.h"
#include "spiketimelistel.h"
#include "intfireleakyel.h"

using namespace std;

class ToolBox {
    
public:
    
    string getSeg(string s);
    string getNextStart(string s);
    vector<string> getFields(string s);
    vector<string> getData(string s);
    vector<string> getSegments(string s);
    int getIndex(string s, string find);
    map<string, string> makeMap(string s);
    vector<string> getLogContents(string s);
    
    void connectSynapses(spiketimelistel *pre, synapse *syn, intfireleakyel *post);
};


#endif /* defined(__Modelel1__ToolBox__) */
