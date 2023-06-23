from collections import defaultdict, Counter
import numpy as np
import random
from numpy.typing import ArrayLike, NDArray
from itertools import chain

import cProfile

n: int =  100_000 # graph size
M: int = (int) (n/2) # number of particles
graph_nodes = list(range(n))

def simulate_with_dict():
    graph = defaultdict(int) # graph is represented by a dictionary. The keys represent the nodes and the values give the current count of particles on the node
    graph[0] = M
    steps = 0
    while max(graph.values()) > 1:
        print(f"Current step: {steps}")
        steps += 1
        graph = step_dict(graph)
        assert sum(graph.values()) == M
        # print("max element:", max(graph.values()))
        # print("graph:", graph)
    
def step_dict(graph: dict):
    destinaions = []
    for key, value in graph.items():
        if value > 1: # particles on the node are unhappy
            destinaions += random.choices(graph_nodes, k=value) # list of nodes where the unhappy particles move to
        else:
            destinaions.append(key) # particle is happy and stays at its current node
    return Counter(destinaions) # counts the particles for each node as a dict

def simulate_with_list():
    graph = np.zeros(n, dtype=np.int32)
    graph[0] = M
    steps = 0
    while np.max(graph) > 1:
        print(f"Current step: {steps}")
        steps += 1
        graph = step_list(graph)
        # print("max element:", np.max(graph))
        # print("graph:", graph)
        assert np.sum(graph) == M

def step_list(graph: NDArray) -> ArrayLike:
    destinations = []
    for index, value in enumerate(graph):
        if value > 1: # particles on the node are unhappy
            destinations += random.choices(graph_nodes, k=value) # list of nodes where the unhappy particles move to
        elif value == 1:
            destinations.append(index)
            
    graph = np.zeros(n, dtype=np.int32)
    for destination in destinations: 
        graph[destination] += 1

    return graph
    

if __name__ == "__main__":
    profiler = cProfile.Profile()
    profiler.enable()
    simulate_with_list()
    profiler.disable()
    profiler.dump_stats("./stats")
