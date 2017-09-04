//
//  Runner.h
//  Modelel1
//
//  Created by Ian Christie on 9/28/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#ifndef __Modelel1__Runner__
#define __Modelel1__Runner__

#include <iostream>
#include <fstream>
#include <vector>
#include "modelel.h"

class Runner {
    vector<modelel*> model;
    string logFilePath;
public:
    Runner(vector<modelel*> _model,string _lFP);
    void Run();
};

#endif /* defined(__Modelel1__Runner__) */
