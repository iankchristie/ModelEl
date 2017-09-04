//
//  plasticity_methods.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/19/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "plasticity_methods.h"

plasticity_methods::plasticity_methods() {
    pre = 0;
    post = 0;
}

plasticity_methods::plasticity_methods(vector<string> fields, vector<string> data) {
    string temp;
    for (int k = 0; k < fields.size(); k++) {
        temp = fields.at(k);
        if (temp=="pre") {
            cout << "Plasticity Method Pre-called" << endl;
        }
        if (temp=="post") {
            cout << "Plasticity Method Post-called" << endl;
        }
    }
}

plasticity_methods::plasticity_methods(map<string,string> data) {
    cout << "Plasticity Method Parent Called" << endl;
    pre = 0;
    post = 0;
}

float plasticity_methods::updateGmax() {
    return 0.0;
}
spiketimelistel* plasticity_methods::getPre() {
    return pre;
}
void plasticity_methods::setPre(spiketimelistel* p) {
    pre = p;
}
spiketimelistel* plasticity_methods::getPost() {
    return post;
}
void plasticity_methods::setPost(spiketimelistel* p) {
    post = p;
}

void plasticity_methods::print() {
    if (pre!=0) {
        cout << "Pre:\t" << pre->getName() << endl;
    }
    else {
        cout << "Pre:\tnone"<< endl;
    }
    if (post!=0) {
        cout << "Post:\t" << post->getName() << endl;
    }
    else {
        cout << "Post:\tnone"<< endl;
    }
}

string plasticity_methods::getName() {
    return "plasticity method";
}