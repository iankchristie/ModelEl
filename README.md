# ModelEl
## C++ parser, model representation, and simulation environment for arbitrary neuronal networks.

### Paper
Model simulations for this project were developed by Dr. Stephen Van Hooser and are described in this paper: http://jn.physiology.org/content/111/11/2355.long.

### Motivation
Many simulations were taking longer than 3 days to complete. The reasons were identified as inefficient simulations and the MATLAB environment. To increase the speed of the simulations we optimized data access times with vector slicing, used Eulers method to approximate differential equations, and converted the model into C++ to be run in a C++ environment.

### Design
The basic idea was to have MATLAB do what it's good at, and avoid what it's bad at. MATLAB was good at creating the models as Dr. Van Hooser had already developed and extensive MATLAB library model generation. Furthermore, it was fantastic at visualizing the data. MATLAB was bad at running the simulations. A very good explanation for this can be found here: https://stackoverflow.com/questions/20513071/performance-tradeoff-when-is-matlab-better-slower-than-c-c

#### Logic Flow
The basic design was as follows:
1. MATLAB generate model and serialize it into a file.
2. C++ executable started with string of file and accept a logging file path.
3. C++ deserializes MATLAB representation of model and creates a C++ representation.
4. C++ runs the model in it's environment
5. C++ logs the data generated to the logging file path.
6. MATLAB plots and visualizes data gathered.

#### Class Design
* Parser - parses the MATLAB representation and creates a C++ representation of the model. This object is a vector of model elements.
* ModelElements - All elements are a subclass of abstract modelel class. Their job is to override the step(), print(), and log() function for use in the running environment. The step function is a time slice in a differential equation to get x from dt to dt+1. More about the individual differential equations of the different elements can be found here: http://cns-classes.bu.edu/cn510/Papers/Theoretical%20Neuroscience%20Computational%20and%20Mathematical%20Modeling%20of%20Neural%20Systems%20-%20%20Peter%20Dayan,%20L.%20F.%20Abbott.pdf. Particularly, look under the Integrate-and-fire model.
* Runner - Simulation environment that, for each time step, goes through the list of elements and calls their step and log function. 

### Usage
Download the source code and create an executable from it. Here is a link to do so with xcode: https://stackoverflow.com/questions/35015902/xcode-creating-an-executable-file. Double clicking the executable will run the default direction selectivity demo.

#### Demos
We've included a number of demos to get associated with the project:
* CurrentDemo - simulates injecting current into a leaky integrate-and-fire neuron.
* SynapseDemo - demonstrates the change in conductance after a pre-synaptic action potential.
* DirectionSelectivityDemo - demonstrates a configuration of neurons that exhibit direction selective behavior.
* PlasticityDemo - demonstrates change in plasticity of synapses over a training period.

To use run
'''
./ModelEl <NameOfDemo>
'''
to override parameters of the demos you can do so by alternating parameter name and value after the demo name like so
'''
./ModelEl <NameOfDemo> <param1> <value1> <param2> <value2> ...
'''

Doing so will give you a list of spike times from the console. To obtain all time series data provide a lfp (loggingFilePath) like so
'''
./ModelEl <NameOfDemo> <param1> <value1> <param2> <value2> lfp <path>
'''

#### Custom Structure
If you wish to use a custom MATLAB structure please contact Dr. Stephen Van Hooser at vanhoosr@brandeis.edu for further instructions.
