'''
Challenge 3.3

Prepare the Bunnies' Escape
===========================
You're awfully close to destroying the LAMBCHOP doomsday device and freeing Commander Lambda's bunny prisoners, but once they're free of the prison blocks,
the bunnies are going to need to escape Lambda's space station via the escape pods as quickly as possible.
Unfortunately, the halls of the space station are a maze of corridors and dead ends that will be a deathtrap for the escaping bunnies.
Fortunately, Commander Lambda has put you in charge of a remodeling project that will give you the opportunity to make things a little easier for the bunnies.
Unfortunately (again), you can't just remove all obstacles between the bunnies and the escape pods - at most you can remove one wall per escape pod path,
both to maintain structural integrity of the station and to avoid arousing Commander Lambda's suspicions.
You have maps of parts of the space station, each starting at a prison exit and ending at the door to an escape pod.
The map is represented as a matrix of 0s and 1s, where 0s are passable space and 1s are impassable walls.
The door out of the prison is at the top left (0,0) and the door into an escape pod is at the bottom right (w-1,h-1).
Write a function answer(map) that generates the length of the shortest path from the prison door to the escape pod, where you are allowed to remove one wall as part of your remodeling plans.
The path length is the total number of nodes you pass through, counting both the entrance and exit nodes.
The starting and ending positions are always passable (0). The map will always be solvable, though you may or may not need to remove a wall.
The height and width of the map can be from 2 to 20. Moves can only be made in cardinal directions; no diagonal moves are allowed.
Languages
=========
To provide a Python solution, edit solution.py
To provide a Java solution, edit solution.java
Test cases
==========
Inputs:
    (int) maze = [[0, 1, 1, 0],
                  [0, 0, 0, 1],
                  [1, 1, 0, 0],
                  [1, 1, 1, 0]]
Output:
    (int) 7
Inputs:
    (int) maze = [[0, 0, 0, 0, 0, 0],
                  [1, 1, 1, 1, 1, 0],
                  [0, 0, 0, 0, 0, 0],
                  [0, 1, 1, 1, 1, 1],
                  [0, 1, 1, 1, 1, 1],
                  [0, 0, 0, 0, 0, 0]]
Output:
    (int) 11

'''

import time

from collections import deque


def available(x, y, map, visited=None):
    if visited:
        return len(map) > x >= 0 and len(map[0]) > y >= 0 and not visited[x][y]
    return len(map) > x >= 0 and len(map[0]) > y >= 0


def print_map(map):
    for i in range(len(map)):
        print(map[i])


def solve_dfs(x, y, wall, map, visited, step):
    if x == len(map) - 1 and y == len(map[0]) - 1:
        input(step)
        return step

    visited[x][y] = 1
    res = 9999999999

    print("--------------------------------------------")
    print_map(visited)
    print("--------------------------------------------")

    if available(x + 1, y, map, visited):
        if map[x + 1][y] == 0:
            curr_res = solve_dfs(x + 1, y, wall, map, visited, step + 1)
            res = min(curr_res, res)
        else:
            if available(x + 1, y + 1, map, visited) or available(x + 1, y - 1, map, visited) or available(x + 2, y,
                                                                                                           map,
                                                                                                           visited):
                if map[x + 1][y] == 1 and wall:
                    curr_res = solve_dfs(x + 1, y, not wall, map, visited, step + 1)
                    res = min(curr_res, res)

    if available(x, y + 1, map, visited):
        if map[x][y + 1] == 0:
            curr_res = solve_dfs(x, y + 1, wall, map, visited, step + 1)
            res = min(curr_res, res)
        else:
            if available(x, y + 2, map, visited) or available(x + 1, y + 1, map, visited) or available(x - 1, y + 1,
                                                                                                       map,
                                                                                                       visited):
                if map[x][y + 1] == 1 and wall:
                    curr_res = solve_dfs(x, y + 1, not wall, map, visited, step + 1)
                    res = min(curr_res, res)

    if available(x - 1, y, map, visited):
        if map[x - 1][y] == 0:
            curr_res = solve_dfs(x - 1, y, wall, map, visited, step + 1)
            res = min(curr_res, res)
        else:
            if available(x - 1, y - 1, map, visited) or available(x - 1, y + 1, map, visited) or available(x - 2, y,
                                                                                                           map,
                                                                                                           visited):
                if map[x - 1][y] == 1 and wall:
                    curr_res = solve_dfs(x - 1, y, not wall, map, visited, step + 1)
                    res = min(curr_res, res)

    if available(x, y - 1, map, visited):
        if map[x][y - 1] == 0:
            curr_res = solve_dfs(x, y - 1, wall, map, visited, step + 1)
            res = min(curr_res, res)
        else:
            if available(x - 1, y - 1, map, visited) or available(x + 1, y - 1, map, visited) or available(x, y - 2,
                                                                                                           map,
                                                                                                           visited):
                if map[x][y - 1] == 1 and wall:
                    curr_res = solve_dfs(x, y - 1, not wall, map, visited, step + 1)
                    res = min(curr_res, res)

    visited[x][y] = 0

    return res


class Node(object):
    def __init__(self, x, y, wall):
        self.x = x
        self.y = y
        self.wall = wall

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y and self.wall == other.wall

    def __hash__(self):
        return hash(self.x) ^ hash(self.y) ^ hash(self.wall)


def solve_bfs(map, height, width):
    start = Node(0, 0, True)
    path = {start: 1}  # Hash map because different types of nodes(wall or no wall) can be present , matrix overrides it

    queue = deque([start])

    nx_coordinates = [[0, 1], [0, -1], [1, 0], [-1, 0]]

    while len(queue) > 0:
        current_node = queue.popleft()

        if current_node.x == height - 1 and current_node.y == width - 1:
            return path[current_node]

        for nx in nx_coordinates:
            neighbour = Node(current_node.x + nx[0], current_node.y + nx[1], current_node.wall)

            if available(neighbour.x, neighbour.y, map) and not path.get(neighbour):
                if map[neighbour.x][neighbour.y] == 0:
                    queue.append(neighbour)
                    path[neighbour] = path[current_node] + 1
                elif neighbour.wall and map[neighbour.x][neighbour.y] == 1:
                    neighbour.wall = False
                    queue.append(neighbour)
                    path[neighbour] = path[current_node] + 1
    return 999999  # No Solution


def solution(map):
    h = len(map)
    w = len(map[0])

    # visited = [[0 for _ in range(w)] for _ in range(h)]
    # print_map(visited)
    start = time.time()
    steps = solve_bfs(map, h, w)
    print(f"Time : {time.time() - start}")
    return steps


if __name__ == '__main__':
    map1 = [[0, 1, 1, 0],
            [0, 0, 0, 1],
            [1, 1, 0, 0],
            [1, 1, 1, 0]]  # 7

    map2 = [[0, 0, 0, 0, 0, 0],
            [1, 1, 1, 1, 1, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 1, 1, 1, 1, 1],
            [0, 1, 1, 1, 1, 1],
            [0, 0, 0, 0, 0, 0]]  # 11

    map3 = [[0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
            [1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
            [1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1],
            [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
            [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
            [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]]  # 39

    map4 = [[0, 1, 0, 1, 0, 0, 0],
            [0, 0, 0, 1, 0, 1, 0]]  # 10

    map5 = [[0, 0, 0, 0, 0, 0],
            [1, 1, 1, 1, 1, 0],
            [1, 1, 1, 1, 1, 1],
            [0, 0, 0, 0, 0, 0],
            [0, 1, 1, 1, 1, 1],
            [0, 0, 0, 0, 0, 0]]  # 21

    map6 = [[0, 0, 0, 0, 0, 0],
            [1, 1, 1, 1, 1, 0],
            [0, 0, 0, 0, 0, 0],
            [0, 1, 1, 1, 1, 1],
            [0, 1, 1, 1, 1, 1],
            [0, 0, 0, 0, 0, 0]]  # 11

    map7 = [[0, 1, 1, 1],
            [0, 1, 0, 0],
            [1, 0, 1, 0],
            [1, 1, 0, 0]]  # 7

    map8 = [[0, 1, 0, 0, 0],
            [0, 0, 0, 1, 0],
            [1, 1, 1, 1, 0]]  # 7

    map9 = [
        [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
        [0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
        [0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
        [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    ]  # 33

    maps = [(map9, 33), (map8, 7), (map7, 7), (map6, 11), (map5, 21), (map4, 10), (map3, 39), (map2, 11), (map1, 7)]

    for (map, answer) in maps:
        res = solution(map)
        if res != answer:
            print_map("======================================")
            print_map(map)
            print(f"Expected : {answer} Found : {answer}")
            print_map("======================================")
