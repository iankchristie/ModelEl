//
//  Parser.cpp
//  Modelel1
//
//  Created by Ian Christie on 9/8/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "Parser.h"

vector<modelel*> Parser::createModel(string s) {
    vector<modelel*> model = *new vector<modelel*>();
    vector<string> temp;
    int pre = 0, post = 0;
    
    s = toolBox.getSeg(s);
    s = toolBox.getNextStart(s);
    temp = toolBox.getSegments(s);
    
    for (string t: temp) {        
        model.push_back(createEl(t));
    }
    
    for(int j = 0; j < temp.size(); j++) {
        
        vector<string> asd = toolBox.getSegments(temp.at(j));
        asd = toolBox.getLogContents(asd.at(1));
        
        for (string t: asd) {
            model.at(j)->logMap[t]=true;
        }
        
        
        map<string,string> data = toolBox.makeMap(temp.at(j));
        
        if (data["type"]=="synapse" || data["type"]=="synapset1t2el") {
            synapse *syn = (synapse*)model.at(j);
            pre = atoi(data["pre"].c_str());
            post = atoi(data["post"].c_str());
            toolBox.connectSynapses((spiketimelistel*)model.at(pre-1), syn, (intfireleakyel*) model.at(post-1));
            
            syn->connectPlasticityParams();
        }
    }
    return model;
}

modelel* Parser::createEl(string s) {
    modelel* El;

    map<string,string> data = toolBox.makeMap(s);
    
    if (data["type"]=="modelel") {
        El = new modelel(data);
    }
    else if (data["type"]=="spiketimelistel") {
        El = new spiketimelistel(data);
    }
    else if (data["type"]=="intfireleakyel") {
        El = new intfireleakyel(data);
    }
    else if (data["type"]=="synapse") {
        El = new synapse(data);
    }
    else if(data["type"]=="synapset1t2el") {
        El = new synapset1t2(data);
    }
    else {
        El = NULL;
        cout << "Warning: Did not convert to known element" << endl;
    }
    
    return El;
}

