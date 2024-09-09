# Design
## Simulation processing
Each simulation has its own handle (`SimulationHandle`) that is used to manage its state. This handle contains the processing for window handling, but simulations can be created headless. Each handle contains the logic to handle each tick, and must be reset after construction in order to function properly.
## Data structures
Each simulation contains a reference to its data context (`SimulationContext`). These context classes contain the processed metadata of each simulation, and also contain pointers to the raw population dataset. A worker (`SimulationWorker`) is created and provided with these pointers in order to process and advance the simulation with each tick.
## Population data
Each individual in the population contains its own small data structure. These values, such as age, income, and various status indicators, are taken together to predict their future values along with factors of chance.