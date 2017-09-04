//
//  main.cpp
//  Modelel1
//
//  Created by Ian Christie on 4/10/13.
//  Copyright (c) 2013 Ian Christie. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "Runner.h"
#include "modelel.h"
#include "Parser.h"
#include "spiketimelistel.h"
#include "intfireleakyel.h"
#include "synapse.h"
#include "synapset1t2.h"
#include "plasticity_methods.h"
#include "stdp_classic.h"
#include "stdp_triplet.h"
#include "Demo.h"
#include "intfireleakyel_currentdemo.h"
#include "intfireleakyel_synapsedemo.h"
#include "PlasticityDemo.h"
#include "DirectionalSelectivityDemo.h"

int main(int argc, const char * argv[])
{
    // Default structure and logFilePath.
    string structure = "<STRUCT size=[1 9]  fields={ 'modelel', 'logged' } data=<<<STRUCT size=[1 1]  fields={ 'type', 'T', 'dT', 'spiketimes', 'name' } data=<<'spiketimelistel'><[0]><[0.0001]><[0.2001]><'cell_1_1'>>/STRUCT>><[]>><<<STRUCT size=[1 1]  fields={ 'type', 'T', 'dT', 'spiketimes', 'name' } data=<<'spiketimelistel'><[0]><[0.0001]><[0.4001]><'cell_1_2'>>/STRUCT>><[]>><<<STRUCT size=[1 1]  fields={ 'type', 'T', 'dT', 'spiketimes', 'name' } data=<<'spiketimelistel'><[0]><[0.0001]><[0.0001]><'cell_2_1'>>/STRUCT>><[]>><<<STRUCT size=[1 1]  fields={ 'type', 'T', 'dT', 'spiketimes', 'name' } data=<<'spiketimelistel'><[0]><[0.0001]><[0.2001]><'cell_2_2'>>/STRUCT>><[]>><<<STRUCT size=[1 1]  fields={ 'type', 'T', 'dT', 'spiketimes', 'name', 'Ie', 'V_leak', 'Rm', 'Taum', 'Area', 'V_reset', 'V_threshold', 'V', 'synapse_list', 'V_spike' } data=<<'intfireleakyel'><[0]><[0.0001]><[]><'output'><[0]><[-0.075]><[10000000]><[0.01]><[0.1]><[-0.08]><[-0.055]><[-0.075]><[6  7  8  9]><[0.01]>>/STRUCT>><'T,V'>><<<STRUCT size=[1 1]  fields={ 'type', 'T', 'dT', 'spiketimes', 'name', 'V_rev', 'Gmax', 'G', 'tau1', 'tau2', 'pre', 'post', 'Tpast_ignore', 'plasticity_method', 'plasticity_params' } data=<<'synapset1t2el'><[0]><[0.0001]><[]><''><[0]><[4e-09]><[0]><[0.001]><[0.05]><[1]><[5]><[1]><''><[]>>/STRUCT>><[]>><<<STRUCT size=[1 1]  fields={ 'type', 'T', 'dT', 'spiketimes', 'name', 'V_rev', 'Gmax', 'G', 'tau1', 'tau2', 'pre', 'post', 'Tpast_ignore', 'plasticity_method', 'plasticity_params' } data=<<'synapset1t2el'><[0]><[0.0001]><[]><''><[0]><[4e-09]><[0]><[0.001]><[0.05]><[2]><[5]><[1]><''><[]>>/STRUCT>><[]>><<<STRUCT size=[1 1]  fields={ 'type', 'T', 'dT', 'spiketimes', 'name', 'V_rev', 'Gmax', 'G', 'tau1', 'tau2', 'pre', 'post', 'Tpast_ignore', 'plasticity_method', 'plasticity_params' } data=<<'synapset1t2el'><[0]><[0.0001]><[]><''><[0]><[4e-09]><[0]><[0.001]><[0.05]><[3]><[5]><[1]><''><[]>>/STRUCT>><[]>><<<STRUCT size=[1 1]  fields={ 'type', 'T', 'dT', 'spiketimes', 'name', 'V_rev', 'Gmax', 'G', 'tau1', 'tau2', 'pre', 'post', 'Tpast_ignore', 'plasticity_method', 'plasticity_params' } data=<<'synapset1t2el'><[0]><[0.0001]><[]><''><[0]><[4e-09]><[0]><[0.001]><[0.05]><[4]><[5]><[1]><''><[]>>/STRUCT>><[]>>/STRUCT>";
    string logFilePath = "/Users/iankchristie/Desktop/Matlab/DemoData/Runner.txt";
    
    
    if(argc > 1) {
        if (strcmp(argv[1], "Help")==0|| strcmp(argv[1], "help")==0) {
            cout << "Type in the name of the demo and any parameters that you would like to manipulate in string literal to variable order." << endl;
        }
        if(strcmp(argv[1], "Struct")==0) {
            for (int k = 2; k < argc; k++) {
                if(strcmp(argv[k], "structure")==0) {
                    structure = strtof(argv[k+1], NULL);
                }
                if(strcmp(argv[k], "lfp")==0) {
                    logFilePath = strtof(argv[k+1], NULL);
                }
            }
            
            Parser p;
            vector<modelel*> cppModel = p.createModel(structure);
            // Print for validation.
            for (int k = 0; k < cppModel.size(); k++) {
                cout << k << ":" << endl;
                modelel* m = cppModel.at(k);
                m->print();
                cout << endl;
            }
            
            // Run and print to file.
            Runner r = *new Runner(cppModel, logFilePath);
            r.Run();

        }
        if(strcmp(argv[1], "CurrentDemo")==0) {
            intfireleakyel_currentdemo cDemo;
            for (int k = 2; k < argc; k++) {
                if(strcmp(argv[k], "Ie")==0) {
                    cDemo.setCurrent(strtof(argv[k+1], NULL));
                }
            }
            cout << "Running at Ie= " << cDemo.getIe() << endl;
            cDemo.run();
        }
        if (strcmp(argv[1], "SynapseDemo")==0) {
            intfireleakyel_synapsedemo sDemo;
            for (int k =2; k < argc; k++) {
                if(strcmp(argv[k],"PreSpikes")==0) {
                    k++;
                    while (k<argc && strtof(argv[k], NULL)!=0) {
                        sDemo.getPre()->addSpike(strtof(argv[k], NULL));
                        k++;
                    }
                }
                sDemo.setDefaultSettings();
                sDemo.run();
            }
        }
        if(strcmp(argv[1],"DirectionalSelectivityDemo")==0) {
            DirectionalSelectivityDemo dsDemo;
            for (int k = 2; k < argc; k++) {
                if(strcmp(argv[k], "dt")==0) {
                    dsDemo.setDT(strtof(argv[k+1], NULL));
                }
                if(strcmp(argv[k], "nreps")==0) {
                    dsDemo.setNReps((int)strtof(argv[k+1], NULL));
                }
                if(strcmp(argv[k], "isi")==0) {
                    dsDemo.setISI(strtof(argv[k+1], NULL));
                }
                if(strcmp(argv[k], "latency")==0) {
                    dsDemo.setLatency(strtof(argv[k+1], NULL));
                }
                if(strcmp(argv[k], "lag")==0) {
                    dsDemo.setLag(strtof(argv[k+1], NULL));
                }
                if(strcmp(argv[k], "Rows")==0) {
                    dsDemo.setR((int)strtof(argv[k+1], NULL));
                }
                if(strcmp(argv[k], "Columns")==0) {
                    dsDemo.setN((int)strtof(argv[k+1], NULL));
                }
                if(strcmp(argv[k], "Syn_Gax_initial")==0) {
                    dsDemo.setSyn_GMax_initial(strtof(argv[k+1], NULL));
                }
                if(strcmp(argv[k], "SimulateIt")==0) {
                    if (strcmp(argv[k+1], "False") == 0 || strcmp(argv[k+1], "false") || strcmp(argv[k+1], "No") || strcmp(argv[k+1], "no")) {
                        dsDemo.setSimit(false);
                    }
                }
                if(strcmp(argv[k], "SimulateUp")==0) {
                    if (strcmp(argv[k+1], "False") == 0 || strcmp(argv[k+1], "false") || strcmp(argv[k+1], "No") || strcmp(argv[k+1], "no")) {
                        dsDemo.setSimup(false);
                    }
                }
                if(strcmp(argv[k], "SimulateDown")==0) {
                    if (strcmp(argv[k+1], "False") == 0 || strcmp(argv[k+1], "false") || strcmp(argv[k+1], "No") || strcmp(argv[k+1], "no")) {
                        dsDemo.setSimdown(false);
                    }
                }
            }
            dsDemo.setDefaultSettings();
            dsDemo.run();
        }
    }
    else {
        DirectionalSelectivityDemo demo;
        demo.setDefaultSettings();
        demo.run();
    }
     
    return 0;
}
