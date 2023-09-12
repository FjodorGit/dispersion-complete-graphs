# dispersion-process-graphs

**Code for simulation of "Dispersion process on graphs"**

Run `make` in the _src_ directory of the project to build the executables.
This will produce three extecutables:

**distribution:**
Compute the dispersion time 10000 times.

**unhappy_process:**
Run a single dispersion process while keeping track of the number of unhappy particles at every step.

**average process**
Run 1000 dispersion processes and keep track of the number of unhappy particles in each one of them.

Every one of these executables has the following options:

- `-t (string: graph type)`: specifies the graph type. Omit this flag to run the process on the fully connected graph. The other possible graph types are `grid` and `line`.
- `-s (number: graph size)`: specifies the graph size. Only make sense to specify when running experiments on the fully connected graph, because the other graphs are infinite anyway.
- `-p (number: number of particles):` the amount of particles to use for the experiment.
- `-c (number: capacity)` the capacity of each node. The maximum amount of paricles that can be on a node and still be happy. Omitting this flag defaults to one.
- `-d` : Flag to print debug information i.e the visualize the graph representation and where particles mode at every step.
