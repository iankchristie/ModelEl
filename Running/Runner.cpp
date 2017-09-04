//
//  Runner.cpp
//  Modelel1
//
//  Created by Ian Christie on 9/28/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "Runner.h"

Runner::Runner(vector<modelel*> _model,string _lFP) {
    if (_lFP.length()!=0) {
        logFilePath = _lFP;
    }
    else {
        logFilePath = _lFP; //fix later
    }
    model = _model;
}

void Runner::Run() {
    ofstream outputFile;
    outputFile.open(logFilePath,ios::trunc);
    
    for (modelel *m:model) {
        if(outputFile.is_open()) {
            outputFile << m->logReference();
        }
    }
    
    if(outputFile.is_open()) {
        outputFile << "" << endl;
    }
    
    for (float k = 0.0; k < 1; k+=model.at(0)->getDT()) {
        for (modelel *m: model) {
            m->step();
        }
        for (modelel *m: model) {
            if(outputFile.is_open()) {
                outputFile << m->logData(); 
            }
        }
        if(outputFile.is_open()) {
            outputFile << endl;
        }
    }
    outputFile.close();

}