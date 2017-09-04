//
//  modelel.h
//  Modelel1
//
//  Created by Ian Christie on 4/10/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__modelel__
#define __Modelel1__modelel__

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "string"

using namespace std;

template <typename T> string tostr(const T& t) { ostringstream os; os<<t; return os.str(); }

class modelel {
    protected:
        float T;
        float dT;
        string name;

    public:
    
        map<string,bool> logMap;
    
        const string type = "modelel"; // constant for identification
    
        modelel(); // true constructor
        modelel(float _t, float _dT, string _name); // true constructor
        modelel(vector<string> fields, vector<string> data);
        modelel(map<string,string> data);
    
        //log methods
        virtual string logReference();
        virtual string logData();
    
        //getters and setters
        float getT();
        void setT(float _T);
        float getDT();
        void setDT(float _dT);
        string getName();
        void setName(string _name);
        virtual string getType();
        //fuctions
        virtual void step();
        virtual void print();
        static double fRand(double fMin, double fMax);
};
#endif /* defined(__Modelel1__modelel__) */
