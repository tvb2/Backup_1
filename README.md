# Backup_1
Gas turbine engine runs hot. After engine shuts down it requires a period of post lubrication. 
This prevents bearing melting due to accumulated heat. 
Normally, a controller would take care of postlube sequence. 
In case of controller failure relay-based backup system ensures postlube sequence. 
Controller and backup systems can have different logic of operation. 
The main source of information about system operation is electrical schematics which is not easy to read. 
The goal was to create an app that would simulate relay system work to allow technicians verify system operation during maintenance or troubleshooting. 
The program requires user to set up timer presets and configure conditions (if fire detected? is oil pressur low? etc) and also explicity set time (in seconds) when conditions starts and ends. 
After configuration is complete, another window with graphs can be opened and a button should be clicked to calculate result. At this stage a calculation is run for each step (a step corresponds to one second of time). 
The graphs show the complete postlube cycle and allow moving the tracer to see state of each parameter. The tracers in all graphs are synchronized. 

Simulation data is stored to structure ResultsData defined in Declarations.h file. In the end of simulation this structure is used to populate plots. QCustomPlot is used to display results

Project structure:
classes and files:
        
        Relay - simple interposing relay. Has two sets of contacts: normally open (NO) and normally closed (NC). When relay is de-energized (enable ==0), its NO contacts are open and NC contacts are closed. When relay is energized (enable == 1) its contacts change state to reverse.
            methods : 
              bool contactsNC() - return 0 if relay is de-energized. return 1 if relay is energized
              bool contactsNO() - return 1 if relay is de-energized. return 0 if relay is energized
        
        TimeRelayFuncA - time relay (on delay) - when power is applied continuously the timing cyle begins. The output contacts change state after the time delya is completed. The contacts will return to their normal state when a reset signal is applied or power is removed
            methods:
              bool contactsNC() - return 0 if relay is de-energized. return 1 if relay is energized
              bool contactsNO() - return 1 if relay is de-energized. return 0 if relay is energized
              bool ckIfDN() - return 1 when timer reaches preset value. Return zero otherwise (Relay will transfer as soon as timer reaches preset.) 

        TimeRelayFuncB - time relay (off delay) - Power is applied continuously. When a start signal is applied, the output contacts change state immediately. When the start signal is removed, the timing cycle begins. The output contacts will return to their normal state once the time delay is completed. Reset will occur when a reset signal is applied or power is removed.
            methods:
              bool contactsNC() - return 0 if relay is de-energized. return 1 if relay is energized
              bool contactsNO() - return 1 if relay is de-energized. return 0 if relay is energized
              bool ckIfDN() - return 1 when timer reaches preset value. Return zero otherwise (Relay will transfer as soon as timer reaches preset.) 
        
        UserData - class used to store user input configuration data from ui to be used in the backend of the simulation
        
        MainWindow - user configuration parameters, initial setup of input conditions. Simulation evaluation and put results into ResultsData structures for each               device.
        
        PlotWindow - display results, move tracer to see state of plots at each simulation step
        
        BackupEval (function). Main evaluation of state of each device. Discrete steps correspond to one second of time.
        
        Declarations - define structure ResultsData to store simulation results (in std::vectors format) to populate plots and retrieve data when moving tracers.
        SizeStruct - (function). Resize ResultsData to the value specified by the user (duration of simulation in seconds)
        
        
