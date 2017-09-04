//
//  Demo.cpp
//  Modelel1
//
//  Created by Ian Christie on 5/4/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "Demo.h"

vector<modelel*> Demo::run(string lfp) {
    vector<modelel*> v;
    cout << "Demo Run Called with " << lfp << endl;
    return v;
}

void Demo::setDefaultSettings() {
    cout << "Demo Default Called" << endl;
}

void Demo::setElementDT(float f) {
    for (modelel *m: model) {
        m->setDT(f);
    }
}

void Demo::compress() {
    cout << "Demo Compress Called" << endl;
}
