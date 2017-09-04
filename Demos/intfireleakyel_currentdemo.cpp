//
//  intfireleakyel_currentdemo.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/25/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "intfireleakyel_currentdemo.h"

#pragma mark constructor
intfireleakyel_currentdemo::intfireleakyel_currentdemo() {
    Ie = 2.5e-9;
    neuron = new intfireleakyel;
}

#pragma mark defaultSettings

void intfireleakyel_currentdemo::setDefaultSettings() {
    neuron->setIe(Ie);
}

#pragma mark compress
void intfireleakyel_currentdemo::compress() {
    model.push_back(neuron);
}


#pragma mark run
vector<modelel*> intfireleakyel_currentdemo::run(string lfp) {
    compress();
    setElementDT(neuron->getDT());
    bool ok = false;
    ofstream outputFile;
    outputFile.open(lfp, ios::trunc);
    if(outputFile.is_open()) {
        outputFile <<"time;voltage"<<endl;
        ok = true;
    }
    int spikes = 0;
    neuron->setIe(Ie);
    for(float k = 0.0; k < 1; k+=neuron->getDT()) {
        for(modelel *m: model) {
            m->step();
            if(ok){
                outputFile << neuron->getT()<<";"<<neuron->getV()<<endl;
            }
            if(neuron->getV() == neuron->getV_spike()) {
                spikes++;
            }
        }
    }
    cout<<"Spikes: "<<spikes<<endl;
    outputFile.close();
    //system("matlab -nodesktop -nosplash - nojvm -r \"[command];\"");
    return model;
}

#pragma mark getters and setters
float intfireleakyel_currentdemo::getIe() {
    return Ie;
}
void intfireleakyel_currentdemo::setCurrent(float f) {
    Ie = f;
}
intfireleakyel* intfireleakyel_currentdemo::getNeuron() {
    return neuron;
}
void intfireleakyel_currentdemo::setNeuron(intfireleakyel* n) {
    neuron = n;
}
