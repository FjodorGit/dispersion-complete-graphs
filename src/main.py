from collections import defaultdict, Counter
import numpy as np
from sortedcontainers import SortedList
from numpy.typing import ArrayLike

n: int =  10_000 # graph size
M: int = (int) (n/2) # number of particles
graph_nodes = np.arange(n, dtype=np.int32)

def main():
    graph = defaultdict(int)
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
        if value > 1:
            possible_destinations = np.setdiff1d(graph_nodes, key, assume_unique=True)
            destinaions = np.concatenate((np.random.choice(possible_destinations, value), destinaions), dtype=np.int32)
        else:
            destinaions = np.append(destinaions, key)
    return Counter(destinaions)

if __name__ == "__main__":
    main()
