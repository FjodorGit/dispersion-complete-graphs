# dispersion-process-graphs

**Code for simulation of "Dispersion process on graphs"**

Run `make` in the _src_ directory of the project to build the executables.
This will produce three extecutables:

**distribution:**
Compute the dispersion time of 10000 processes.

**unhappy_process:**
Run a single dispersion process while keeping track of the number of unhappy particles at every step.

**average process:**
Run 1000 dispersion processes and keep track of the number of unhappy particles in each one of them.

Every one of these executables has the following options:

- `-t (string: graph type)`: specifies the graph type. Omit this flag to run the process on the fully connected graph. The other possible graph types are `grid` and `line`.
- `-s (number: graph size)`: specifies the graph size. Only make sense to specify when running experiments on the fully connected graph, because the other graphs are infinite anyway.
- `-p (number: number of particles):` the amount of particles to use for the experiment.
- `-c (number: capacity)` the capacity of each node. The maximum amount of particles that can be on a node and still be happy. Omitting this flag defaults to one.
- `-d` : Flag to print debug information i.e visualize the graph representation and where particles moved at every step. Makes most sense, when running a single unhappy process with low particles counts.

**Examples:**

- `./distribution.out -s 100 -p 50`: Compute the dispersion time of the process on a fully connected graph wih size 100 and 50 particles.
- `./distribution.out -s 100 -p 50 -c 2`: Same as before only now the graph has capacity 2.
- `./unhappy_process.out -t grid -p 50`: Run a single unhappy process on the grid with 50 particles.
- `./unhappy_process.out -t line -p 20 -d`: Run a single unhappy process on the line with 20 particles and debug information. This is what the debug information would look like in this case. ![alt text](https://github.com/FjodorGit/dispersion-process-graphs/blob/main/.image/Screenshot%20from%202023-09-12%2011-39-29.png?raw=true)
  <br>Each group of move and stay commands corresponds to a node on the graph.
