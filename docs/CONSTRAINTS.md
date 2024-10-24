# Constraints
## Computational resources
### Memory
Due to the presence of distinct data structures for each individual, the total memory usage of the program increases as the size of a population increases. This usage is multipled whenever multiple simulations are ran simultaneously.
### Execution time
Execution cycles are limited resources, and a delicate balance between simulation detail and computational complexity must be found somewhere. There is a limited amount of time to construct the results of this simulation. With every variable and relationship introduced, the time taken for every tick of the simulation increases. This makes overall program speed optimizations an extremely important endeavour, especially those that optimize the speed of each simulation cycle.
### Disk storage
While a minor factor, it must be noted that any data that is serialized and stored on permanent media must fit inside of a finite storage medium. Larger simulation sizes and larger datasets will produce larger logs and summaries.
## External circumstances
### Deadlines
The development for this model must be completed to a sufficient operational quality by January of 2025. There is a limited amount of developmental effort to be put in, so therefore some shortcuts that do not sacrifice a capability or quality that is too significant must be taken in order to free up development time for the purposes of extensive quality assurance.