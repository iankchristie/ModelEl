//
//  intfireleakyel_synapsedemo.cpp
//  Modelel1
//
//  Created by Ian Christie on 5/1/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "intfireleakyel_synapsedemo.h"

#pragma mark constructor
intfireleakyel_synapsedemo::intfireleakyel_synapsedemo() {
    preNeuron = new spiketimelistel;
    postNeuron = new intfireleakyel;
    syn = new synapse;
    dT = .0001;
}

#pragma mark setDefaultSettings
void intfireleakyel_synapsedemo::setDefaultSettings() {
    syn = new synapset1t2;
    syn->setGmax(.5e-9);
    
    syn->setPre(preNeuron);
    syn->setPost(postNeuron);
    postNeuron->addSynapse(syn);
    
}

#pragma mark compress
void intfireleakyel_synapsedemo::compress() {
    model.push_back(preNeuron);
    model.push_back(syn);
    model.push_back(postNeuron);
}

#pragma mark run
vector<modelel*> intfireleakyel_synapsedemo::run() {
    compress();
    setElementDT(preNeuron->getDT());
    
    bool ok = false;
    ofstream outputFile;
    outputFile.open("/Users/ianchristie/Desktop/Matlab/DemoData/SynapseDemo/SynapseDemo_Data.txt",ios::trunc);
    if(outputFile.is_open()) {
        outputFile <<"time;synapticConductivity;postVoltage"<<endl;
        ok = true;
    }
    
    for (float k = 0.0; k < 1; k+=dT) {
        for (modelel *m: model) {
            m->step();
        }
        if(ok){
            outputFile << syn->getT()<<";"<<syn->getG()<<";"<<postNeuron->getV() << endl;
        }
    }
    outputFile.close();
    return model;
}

#pragma mark getters and setters
spiketimelistel* intfireleakyel_synapsedemo::getPre() {
    return preNeuron;
}
void intfireleakyel_synapsedemo::setPre(spiketimelistel* _pre) {
    preNeuron = _pre;
    if(syn) {
        syn->setPre(preNeuron);
    }
}

intfireleakyel* intfireleakyel_synapsedemo::getPost() {
    return postNeuron;
}
void intfireleakyel_synapsedemo::setPost(intfireleakyel* _post) {
    postNeuron = _post;
    if(syn) {
        syn->setPost(postNeuron);
        postNeuron->addSynapse(syn);
    }
}

synapse* intfireleakyel_synapsedemo::getSynapse() {
    return syn;
}
void intfireleakyel_synapsedemo::setSynapse(synapse* _s) {
    syn = _s;
    if(preNeuron) {
        syn->setPre(preNeuron);
    }
    if(postNeuron) {
        syn->setPost(postNeuron);
        postNeuron->addSynapse(syn);
    }
}
float intfireleakyel_synapsedemo::getDT() {
    return dT;
}
void intfireleakyel_synapsedemo::setDT(float f) {
    dT = f;
}

void intfireleakyel_synapsedemo::someSpikes() {
    preNeuron->addSpike(.1);
    preNeuron->addSpike(.11);
    preNeuron->addSpike(.12);
    preNeuron->addSpike(.13);
}
