# Administration
## Command line arguments
The program shall accept command line arguments upon execution that modulate the state of the executing simulation. These parameters shall consistently maintain an either `-switch` or `--parameter=value` format. Parameters are delineated between each other with spaces.
## Real-time execution administration
The means of administration to be described in this section are only to be accessible when the visualizer is enabled and attached to the executing simulation.
### Pausing/resuming
To toggle the status of live execution in the simulation, one must simply press the `K` key or corresponding international key.
### Speed modulation
The speed can only be modulated when the execution has been paused via keypress. The `I` key will increase the speed whereas the `O` key will decrease the speed to specific minimums or maximums.
### Stepping
While holding the simulation in a paused state, it is possible to advance the simulation by one singular update by simply pressing the `P` key.
### Result publication
While holding the simulation in a paused state, it is possible to generate a text file containing a serialized dataset of the current **population** by pressing the `N` key. In order to generate a text file containing a serialized dataset of a **random sample** of the population, simply press the `M` key instead.