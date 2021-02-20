"""
Challenge 4.2

Escape Pods
===========

You've blown up the LAMBCHOP doomsday device and relieved the bunnies of their work duries -- and now you need to escape from the space station as quickly and as orderly as possible!
The bunnies have all gathered in various locations throughout the station,
and need to make their way towards the seemingly endless amount of escape pods positioned in other parts of the station.
You need to get the numerous bunnies through the various rooms to the escape pods.
Unfortunately, the corridors between the rooms can only fit so many bunnies at a time.
What's more, many of the corridors were resized to accommodate the LAMBCHOP, so they vary in how many bunnies can move through them at a time.

Given the starting room numbers of the groups of bunnies,
the room numbers of the escape pods, and how many bunnies can fit through at a time in each direction of every corridor in between,
 figure out how many bunnies can safely make it to the escape pods at a time at peak.

Write a function solution(entrances, exits, path) that takes an array of integers denoting where the groups of gathered bunnies are,
an array of integers denoting where the escape pods are located, and an array of an array of integers of the corridors,
returning the total number of bunnies that can get through at each time step as an int.
The entrances and exits are disjoint and thus will never overlap.
The path element path[A][B] = C describes that the corridor going from A to B can fit C bunnies at each time step.
There are at most 50 rooms connected by the corridors and at most 2000000 bunnies that will fit at a time.

For example, if you have:
entrances = [0, 1]
exits = [4, 5]
path = [
  [0, 0, 4, 6, 0, 0],  # Room 0: Bunnies
  [0, 0, 5, 2, 0, 0],  # Room 1: Bunnies
  [0, 0, 0, 0, 4, 4],  # Room 2: Intermediate room
  [0, 0, 0, 0, 6, 6],  # Room 3: Intermediate room
  [0, 0, 0, 0, 0, 0],  # Room 4: Escape pods
  [0, 0, 0, 0, 0, 0],  # Room 5: Escape pods
]

Then in each time step, the following might happen:
0 sends 4/4 bunnies to 2 and 6/6 bunnies to 3
1 sends 4/5 bunnies to 2 and 2/2 bunnies to 3
2 sends 4/4 bunnies to 4 and 4/4 bunnies to 5
3 sends 4/6 bunnies to 4 and 4/6 bunnies to 5

So, in total, 16 bunnies could make it to the escape pods at 4 and 5 at each time step.
(Note that in this example, room 3 could have sent any variation of 8 bunnies to 4 and 5,
such as 2/6 and 6/6, but the final solution remains the same.)

"""

import time


class Graph:
    def __init__(self, graph):
        self.graph = graph  # residual graph
        self.rows = len(graph)

    def bfs(self, s, t, parent):
        # Set all the vertices as not visited
        visited = [False] * self.rows

        queue = list()

        queue.append(s)
        visited[s] = True

        # Standard BFS Loop
        while queue:
            u = queue.pop(0)

            if u == t:
                return True

            for ind, val in enumerate(self.graph[u]):
                if visited[ind] is False and val > 0:
                    queue.append(ind)
                    visited[ind] = True
                    parent[ind] = u

        return False

    def fordfulkerson_max_flow(self, source, sink):

        parent = [-1] * self.rows

        max_flow = 0  # There is no flow initially

        path_exists = self.bfs(source, sink, parent)

        # Augment the flow while there is path from source to sink
        while path_exists:

            # Track back and calculate overall flow
            path_flow = 10000000
            t_sink = sink
            while t_sink != source:
                t_sink_parent = parent[t_sink]
                path_flow = min(path_flow, self.graph[t_sink_parent][t_sink])
                t_sink = parent[t_sink]

            # Add path flow to overall flow
            max_flow += path_flow

            # Update the residual capacities
            t_sink = sink
            while t_sink != source:
                t_sink_parent = parent[t_sink]
                self.graph[t_sink_parent][t_sink] -= path_flow
                self.graph[t_sink][t_sink_parent] += path_flow
                t_sink = parent[t_sink]

            path_exists = self.bfs(source, sink, parent)

        return max_flow


def solution(entrances, exits, path):
    g = Graph(path)
    result = 0

    # Check max-flow for each entrance and exit pair
    for entrance in entrances:
        for exit in exits:
            result += g.fordfulkerson_max_flow(entrance, exit)

    return result


def main():
    cases = [([0, 1],
              [4, 5],
              [[0, 0, 4, 6, 0, 0],
               [0, 0, 5, 2, 0, 0],
               [0, 0, 0, 0, 4, 4],
               [0, 0, 0, 0, 6, 6],
               [0, 0, 0, 0, 0, 0],
               [0, 0, 0, 0, 0, 0]],
              16),

             ([0],
              [3],
              [[0, 7, 0, 0],
               [0, 0, 6, 0],
               [0, 0, 0, 8],
               [9, 0, 0, 0]],
              6)]

    for (entrances, exits, path, answer) in cases:
        start = time.time()
        result = solution(entrances, exits, path)
        total = time.time() - start
        if result != answer:
            print(f"Expected : {answer} Got : {result}")
        else:
            print(f"Success! Time : {total}")


if __name__ == '__main__':
    main()
