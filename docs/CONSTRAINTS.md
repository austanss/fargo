# Constraints
## Computational resources
### Memory
Due to the presence of distinct data structures for each individual, the total memory usage of the program increases as the size of a population increases. This usage is multipled whenever multiple simulations are ran simultaneously.
### Execution time
Execution cycles are limited resources, and a delicate balance between simulation detail and computaion complexity must be found somewhere. There is a limited amount of time to construct the results of this simulation. With every variable and relationship introduced, the time taken for every tick of the simulation increases. This makes overall program speed optimizations an extremely important endeavour, especially those that optimize the speed of each simulation cycle.
### Disk storage
While a minor factor, it must be noted that any data that is serialized and stored on permanent media must fit inside of a finite storage medium. Larger simulation sizes and larger datasets will produce larger logs and summaries.