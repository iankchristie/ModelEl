//
//  PlasticityDemo.cpp
//  Modelel1
//
//  Created by Ian Christie on 5/14/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "PlasticityDemo.h"

PlasticityDemo::PlasticityDemo() {
    pre1 = new spiketimelistel;
    pre2 = new spiketimelistel;
    post = new intfireleakyel;
    syn1 = new synapse;
    syn2 = new synapse;
}

#pragma mark setDefaultSettings
void PlasticityDemo::setDefaultSettings() {
    syn1 = new synapset1t2;
    syn1->setGmax(.5e-9);
    syn1->setPre(pre1);
    syn1->setPost(post);
    post->addSynapse(syn1);
    //syn1->setPlasticity_method(new stdp_classic);
    syn2 = new synapset1t2;
    syn2->setGmax(.5e-9);
    syn2->setPre(pre2);
    syn2->setPost(post);
    post->addSynapse(syn2);
}

#pragma mark compress
void PlasticityDemo::compress() {
    model.push_back(pre1);
    model.push_back(syn1);
    model.push_back(pre2);
    model.push_back(syn2);
    model.push_back(post);
}

#pragma mark run
vector<modelel*> PlasticityDemo::run(string lfp) {
    compress();
    setElementDT(pre1->getDT());
    bool ok = false;
    ofstream outputFile;
    outputFile.open(lfp,ios::trunc);
    if(outputFile.is_open()) {
        outputFile <<"time;syn1;syn2;postVoltage"<<endl;
        ok = true;
    }

    for (float k = 0.0; k < 1; k+=pre1->getDT()) {
        for (modelel *m: model) {
            m->step();
        }
        cout << "Time: " << k << endl;
        cout << "Voltage" << post->getV() << endl;
        if(ok){
            outputFile <<k<<";"<<syn1->getG()<<";"<<syn2->getG()<<";"<<post->getV() << endl;
        }
    }
    outputFile.close();
    return model;
}

#pragma mark getters and setters
spiketimelistel* PlasticityDemo::getPre1() {
    return pre1;
}

void PlasticityDemo::setPre1(spiketimelistel* _n) {
    pre1 = _n;
}

spiketimelistel* PlasticityDemo::getPre2() {
    return pre2;
}
void PlasticityDemo::setPre2(spiketimelistel* _n) {
    pre2 = _n;
}

intfireleakyel* PlasticityDemo::getPost() {
    return post;
}
void PlasticityDemo::setPost(intfireleakyel* _n) {
    post = _n;
}
