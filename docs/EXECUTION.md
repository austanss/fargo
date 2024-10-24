# Execution
## Concurrence
### Parallel simulation
Put simply, if parallel execution of simulations is somehow necessitated, then two separate instances of the program can be run on the operating system level for adequate parallel execution. Design for possible future implementation of such a feature is prohibited and cannot be tolerated due to the unnecessary technical complexity that it would factor into design decisions.
### Singletonism
Consequently, the largest features of the program are obligated to be ran singularly, such as the visualizer. This saves time, resources, and complexity.
### Singular ownership
Objects are only owned and modified by one other object. This helps conserve complexity and spend less time working out memory mechanics for multiple ownership or thread affinity.