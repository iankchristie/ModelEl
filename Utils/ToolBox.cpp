//
//  ToolBox.cpp
//  Modelel1
//
//  Created by Ian Christie on 9/25/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include "ToolBox.h"

string ToolBox::getSeg(string s) {
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

string ToolBox::getNextStart(string s) {
    int k = 0;
    while (s.at(k)!='<'&&k<s.length()-1) {
        k++;
    }
    return s.substr(k);
}

vector<string> ToolBox::getSegments(string s) {
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

vector<string> ToolBox::getFields(string s) {
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

vector<string> ToolBox::getData(string s) {
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

int ToolBox::getIndex(string s, string find) {
    for (int i = 0; i < s.length(); ++i) {
        if (s.substr(i,find.length())==find) {
            return i+ (int)find.length();
        }
    }
    
    return -1;
}

map<string, string> ToolBox::makeMap(string s) {
    map<string, string> data = *new map<string, string>();
    
    vector<string> fields1= getFields(s);
    vector<string> data1 = getData(s);
    
    for(int k = 0; k < fields1.size(); k++) {
        data.insert(pair<string,string>(fields1.at(k), data1.at(k)));
    }
    
    return data;
}

vector<string> ToolBox::getLogContents(string s) {
    vector<string> v = *new vector<string>();
    string temp="";
    if (s.length()==0 || s.at(0)=='[') {
        return v;
    }
    for (int k = 1; k < s.length()-1; k++) {
        if (s.at(k)==',') {
            v.push_back(temp);
            temp.clear();
        }
        else {
            temp+=s.at(k);
        }
    }
    v.push_back(temp);
    return v;
}

void ToolBox::connectSynapses(spiketimelistel *pre, synapse *syn, intfireleakyel *post) {
    syn->setPre(pre);
    syn->setPost(post);
    post->addSynapse(syn);
}