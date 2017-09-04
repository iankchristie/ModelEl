//
//  synapse.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/12/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "synapse.h"

#pragma mark constructor

synapse::synapse() {
    V_rev = 0.00;
    Gmax = 10e-9;
    G = 0;
    Tpast_ignore = 1;
    plasticity_method = 0;
}

synapse::synapse(vector<string> fields, vector<string> data):modelel(fields, data) {
    string temp;
    for (int k = 0; k < fields.size(); k++) {
        temp = fields.at(k);
        if (temp == "V_rev") {
            V_rev= atof(data.at(k).c_str());
        }
        if (temp == "Gmax") {
            Gmax= atof(data.at(k).c_str());
        }
        if (temp == "G") {
           G = atof(data.at(k).c_str());
        }
        if (temp == "Tpast_ignore") {
           Tpast_ignore = atof(data.at(k).c_str());
        }
        if (temp == "plasticity_method" && data.at(k)!="") {
            vector<string> fields1 = getFields(data.at(k));
            vector<string> data1 = getData(data.at(k));
            if (data1.at(0)=="stdp_classic") {
                plasticity_method = new stdp_classic(fields1, data1);
            }
            if (data1.at(0)=="stdp_triplet") {
                plasticity_method = new stdp_triplet(fields1, data1);
            }
        }
    }
}

synapse::synapse(map<string,string> data):modelel(data) {
    V_rev = atof(data["V_rev"].c_str());
    Gmax = atof(data["Gmax"].c_str());
    G = atof(data["G"].c_str());
    Tpast_ignore = atof(data["Tpast_ignore"].c_str());
    if (data["plasticity_method"]!="") {
        map<string,string> temp = makeMap(data["plasticity_method"]);
        if (temp["type"]=="stdp_classic") {
            plasticity_method = new stdp_classic(temp);
        }
        else if (temp["type"]=="stdp_triplet") {
            plasticity_method = new stdp_triplet(temp);
        }
        else {
            cout << "Issue creating Plasticity Method" << endl;
        }
    }
    else {
        plasticity_method = 0;
    }
    
    
    logMap["V_rev"] = false;
    logMap["Gmax"] = false;
    logMap["G"] = false;
    logMap["Tpast_ignore"] = false;
}

#pragma mark log

string synapse::logReference() {
    string temp = modelel::logReference();
    for(auto k: logMap) {
        if (k.second) {
            if(k.first=="V_rev") {
                temp+="V_rev";
                temp+=";";
            }
            if(k.first=="Gmax") {
                temp+="Gmax";
                temp+=";";
            }
            if(k.first=="G") {
                temp+="G";
                temp+=";";
            }
            if(k.first=="Tpast_ignore") {
                temp+="Tpast_ignore";
                temp+=";";
            }
        }
    }
    return temp;
}

string synapse::logData() {
    string temp = modelel::logData();
    for(auto k: logMap) {
        if (k.second) {
            if(k.first=="V_rev") {
                temp+=tostr(V_rev);
            }
            if(k.first=="Gmax") {
                temp+=tostr(Gmax);
            }
            if(k.first=="G") {
                temp+=tostr(G);
            }
            if(k.first=="Tpast_ignore") {
                temp+=tostr(Tpast_ignore);
            }
        }
    }
    return temp;
}


map<string, string> synapse::makeMap(string s) {
    map<string, string> data = *new map<string, string>();
    
    vector<string> fields1= getFields(s);
    vector<string> data1 = getData(s);
    
    for(int k = 0; k < fields1.size(); k++) {
        data.insert(pair<string,string>(fields1.at(k), data1.at(k)));
    }
    
    return data;
}

string synapse::getSeg(string s) {
    if(s.length()==0||s.at(0)!='<'){
        return "";
    }
    int k = 1;
    int counter = 1;
    while(k!=0&&counter<s.length()) {
        if(s.at(counter)=='<') {
            k++;
        }
        if(s.at(counter)=='>') {
            k--;
        }
        counter++;
    }
    return s.substr(1,counter-2);
}

string synapse::getNextStart(string s) {
    int k = 0;
    while (s.at(k)!='<'&&k<s.length()-1) {
        k++;
    }
    return s.substr(k);
}

vector<string> synapse::getSegments(string s) {
    vector<string> segs = *new vector<string>();
    if (s.length()==0 || s.at(0)!='<') {
        return segs;
    }
    string temp = getSeg(s);
    while (temp.length()!=0) {
        segs.push_back(temp);
        s = s.substr(temp.length());
        s = getNextStart(s);
        temp=getSeg(s);
    }
    return segs;
}

vector<string> synapse::getFields(string s) {
    vector<string> v = *new vector<string>();
    int t = getIndex(s, "fields={");
    if (t==-1) {
        return v;
    }
    s = s.substr(t);
    s = s.substr(0,getIndex(s, "}")-1);
    string temp;
    for (int k = 0; k < s.length(); k++) {
        if (s.at(k)=='\'') {
            v.push_back(temp);
            temp.clear();
        }
        else {
            temp+=s.at(k);
        }
    }
    vector<string> v2 = *new vector<string>();
    for(string vs: v) {
        if (vs.at(0)!=' ' && vs.at(0)!=',') {
            v2.push_back(vs);
        }
    }
    return v2;
}

vector<string> synapse::getData(string s) {
    vector<string> v = *new vector<string>();
    int t = getIndex(s, "data=");
    if (t==-1) {
        return v;
    }
    s = s.substr(t);
    s = getNextStart(s);
    s = getSeg(s);
    v = getSegments(s);
    vector<string> v2 = *new vector<string>();
    string temp;
    for (string vs: v) {
        for (int k=0; k < vs.length(); k++) {
            if (vs.at(k)!='[' && vs.at(k)!=']' && vs.at(k)!='\'') {
                temp+=vs.at(k);
            }
        }
        v2.push_back(temp);
        temp.clear();
    }
    return v2;
}

int synapse::getIndex(string s, string find) {
    for (int i = 0; i < s.length(); ++i) {
        if (s.substr(i,find.length())==find) {
            return i+ (int)find.length();
        }
    }
    
    return -1;
}
#pragma mark getters and setters

float synapse::getV_rev() {
    return V_rev;
}
void synapse::setV_rev(float f) {
    V_rev = f;
}
float synapse::getGmax() {
    return Gmax;
}
void synapse::setGmax(float f) {
    Gmax = f;
}
float synapse::getG() {
    return G;
}
void synapse::setG(float f) {
    G = f;
}
spiketimelistel* synapse::getPre() {
    return pre;
}
void synapse::setPre(spiketimelistel *v) {
    pre = v;
}
spiketimelistel* synapse::getPost() {
    return post;
}
void synapse::setPost(spiketimelistel *v) {
    post = v;
}

float synapse::getTpast_ignore() {
    return Tpast_ignore;
}
void synapse::setTpast_ignore(float f) {
    Tpast_ignore = f;
}
plasticity_methods* synapse::getPlasticity_method() {
    return plasticity_method;
}
void synapse::setPlasticity_method(plasticity_methods* pm) {
    plasticity_method = pm;
}

string synapse::getType() {
    return type;
}

void synapse::connectPlasticityParams() {
    if (plasticity_method!=0) {
        plasticity_method->setPre(pre);
        plasticity_method->setPost(post);
    }
}

void synapse::print() {
    modelel::print();
    cout<< "synapse:" << endl;
    cout << "V_rev:\t" << V_rev << endl;
    cout << "Gmax:\t" << Gmax << endl;
    cout << "G:\t" << G << endl;
    if (pre) {
        
        cout << "Pre:\t" << pre->getName() << endl;
    }
    else {
        cout << "Pre:\t" << "none" << endl;
    }
    if (post!=NULL) {
        cout << "Post:\t" << post->getName() << endl;
    }
    else {
        cout << "Post:\t" << "none" << endl;
    }
    
    cout << "Tpast_ignore:\t" << Tpast_ignore << endl;
    if (plasticity_method!=NULL) {
        cout << "plasticity_method:\t" << plasticity_method->getName() << endl;
    }
    else {
        cout << "plasticity_method:\t" << "none" << endl;
    }
}