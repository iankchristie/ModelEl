//
//  DirectionalSelectivityDemo.cpp
//  Modelel1
//
//  Created by Ian Christie on 5/31/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "DirectionalSelectivityDemo.h"

#pragma mark constructors
DirectionalSelectivityDemo::DirectionalSelectivityDemo() {
    dT = 1e-4;
    nreps = 1;
    isi = 0.75; //0.75 seconds
    latency = 0.200;  // latency of the second layer, 200ms
    lag = latency; // time between stimulus arriving at cell1 and cell3
    N = 2;
    R = 2;
    Syn_Gmax_initial = NULL;
    randomness = 0;
    plotit = true;
    simit = true;
    simup = true;
    simdown  = true;
}

#pragma mark parent

void DirectionalSelectivityDemo::setDefaultSettings() {
    bool ok = false;
    ofstream outputFile;
    outputFile.open("/Users/ianchristie/Desktop/Matlab/DemoData/DirectionalSelectivityDemo/DirectionalSelectivityDemo_SpikeData.txt",ios::trunc);
    if(outputFile.is_open()) {
        outputFile << (N * R) +1 << endl;
        ok = true;
    }
    
    // override Syn_Gmax_initial
    if (Syn_Gmax_initial == 0) {
        cout << "Warning: overriding Syn_Gmax_initial" << endl;
        Syn_Gmax_initial = 4e-9; //I think, Get confirmation
    }
    
    //target neuron
    intfireleakyel *tNeuron = new intfireleakyel();
    tNeuron->setName("TargetNeuron");
    //variables
    
    for (int k = 0; k < R; k++) {
        for (int j = 0; j < N; j++) {
            //create neuron
            spiketimelistel *n = new spiketimelistel();
            ostringstream s;
            s << "Cell_" << k << "_" << j;
            n->setName(s.str());
            
            //create synapse
            synapset1t2 *syn = new synapset1t2();
            syn->setGmax(Syn_Gmax_initial);
            //connect
            
            syn->setPre(n);
            syn->setPost(tNeuron);
            tNeuron->addSynapse(syn);
            //create other stuff
            if (simup) {
                float firstSpike = dT + k*latency + j*lag + (((float)rand()/RAND_MAX)*2-1)*randomness;
                for (int k = 0; k < nreps; k++) {
                    n->addSpike(firstSpike+isi*k);
                }
            }
            
            if (simdown) {
                float firstSpike2 = dT + k*latency + (R-j)*lag + (((float)rand()/RAND_MAX)*2-1)*randomness;
                for (int k = 0; k < nreps; k++) {
                    n->addSpike(firstSpike2+isi*k);
                }
            }
            
            model.push_back(n);
            model.push_back(syn);
           
            if(ok) {
                 n->print();
                outputFile << n->getName() << ";";
                for (float f: *(n->getSpikeTimes())) {
                    outputFile << f << ";";
                }
                outputFile << endl;
            }
        }
    }
    
    model.push_back(tNeuron);
    
    outputFile.close();
}

void DirectionalSelectivityDemo::compress() {
    
}

vector<modelel*> DirectionalSelectivityDemo::run(string lfp) {
    if (!simit) {
        return model;
    }
    setElementDT(dT);
    
    // TargetVoltage Data
    bool ok = false;
    ofstream outputFile;
    outputFile.open(lfp,ios::trunc);
    if(outputFile.is_open()) {
        outputFile << "time;TargetNeuronVoltage"<<endl;;
        ok = true;
    }
    

    
    for (float k = 0.0; k < isi*nreps; k+=dT) {
        for (modelel* m: model) {
            m->step();
        }
        if (ok) {
            outputFile << k << ";" << ((intfireleakyel*) model.back())->getV() << ";" << endl;
        }
    }
    outputFile.close();
    
    ofstream outputFile2;
    outputFile2.open(lfp,ios::app);
    if(outputFile2.is_open()) {
        cout << "ok";
        outputFile2 << "TargetNeuron;";
        for (float f: *((spiketimelistel*) model.back())->getSpikeTimes()) {
            outputFile2 << f << ";";
        }
    }
    outputFile2.close();

    if (plotit) {
        //system("matlab...");
    }
    return model;
}

#pragma mark getters and setters

float DirectionalSelectivityDemo::getDT() {
    return dT;
}
void DirectionalSelectivityDemo::setDT(float f) {
    dT = f;
}

int DirectionalSelectivityDemo::getNReps() {
    return nreps;
}
void DirectionalSelectivityDemo::setNReps(int i) {
    nreps = i;
}

float DirectionalSelectivityDemo::getISI() {
    return isi;
}
void DirectionalSelectivityDemo::setISI(float f) {
    isi = f;
}

float DirectionalSelectivityDemo::getLatency() {
    return latency;
}
void DirectionalSelectivityDemo::setLatency(float f) {
    latency = f;
}

float DirectionalSelectivityDemo::getLag() {
    return lag;
}
void DirectionalSelectivityDemo::setLag(float f) {
    lag = f;
}

int DirectionalSelectivityDemo::getN() {
    return N;
}
void DirectionalSelectivityDemo::setN(int i) {
    N = i;
}

int DirectionalSelectivityDemo::getR() {
    return R;
}
void DirectionalSelectivityDemo::setR(int i) {
    R = i;
}

float DirectionalSelectivityDemo::getSyn_GMax_initial() {
    return Syn_Gmax_initial;
}
void DirectionalSelectivityDemo::setSyn_GMax_initial(float f) {
    Syn_Gmax_initial = f;
}

plasticity_methods DirectionalSelectivityDemo::getPlasticityMethod() {
    return plasticity_method;
}
void DirectionalSelectivityDemo::setPlasticityMethod(plasticity_methods pm) {
    plasticity_method = pm;
}

float DirectionalSelectivityDemo::getRandomness() {
    return randomness;
}
void DirectionalSelectivityDemo::setRandomness(float f) {
    randomness = f;
}

bool DirectionalSelectivityDemo::getPlotit() {
    return plotit;
}
void DirectionalSelectivityDemo::setPlotit(bool b) {
    plotit = b;
}

bool DirectionalSelectivityDemo::getSimit() {
    return simit;
}
void DirectionalSelectivityDemo::setSimit(bool b) {
    simit = b;
}

bool DirectionalSelectivityDemo::getSimup() {
    return simup;
}
void DirectionalSelectivityDemo::setSimup(bool b) {
    simup = b;
}

bool DirectionalSelectivityDemo::getSimdown() {
    return simdown;
}
void DirectionalSelectivityDemo::setSimdown(bool b) {
    simdown = b;
}
