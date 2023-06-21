from collections import defaultdict, Counter
import numpy as np
from sortedcontainers import SortedList
from numpy.typing import ArrayLike

n: int =  10_000 # graph size
M: int = (int) (n/2) # number of particles
graph_nodes = np.arange(n, dtype=np.int32)

def main():
    graph = defaultdict(int) # graph is represented by a dictionary. The keys represent the nodes and the values give the current count of particles on the node
    graph[0] = M
    steps = 0
    while max(graph.values()) > 1:
        print(f"Current step: {steps}")
        graph = step(graph)
        steps += 1
        # print("max element:", max(graph.values()))
        # print("graph:", graph)
    
def step(graph):
    destinaions = np.array([], dtype=np.int32)
    for key, value in graph.items():
        if value > 1: # particles on the node are unhappy
            possible_destinations = np.setdiff1d(graph_nodes, key, assume_unique=True)
            destinaions = np.concatenate((np.random.choice(possible_destinations, value), destinaions), dtype=np.int32) # list of nodes where the unhappy particles move to
        else:
            destinaions = np.append(destinaions, key) # particle is happy and stays at its current node
    return Counter(destinaions) # counts the particles for each node as a dict

if __name__ == "__main__":
    main()
