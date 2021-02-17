"""
Challenge 4.1

Bringing a Gun to a Trainer Fight
=================================

Uh-oh -- you've been cornered by one of Commander Lambdas elite bunny trainers!
Fortunately, you grabbed a beam weapon from an abandoned storeroom while you were running through the station, so you have a chance to fight your way out.
But the beam weapon is potentially dangerous to you as well as to the bunny trainers: its beams reflect off walls,
meaning you'll have to be very careful where you shoot to avoid bouncing a shot toward yourself!

Luckily, the beams can only travel a certain maximum distance before becoming too weak to cause damage.
You also know that if a beam hits a corner, it will bounce back in exactly the same direction.
And of course, if the beam hits either you or the bunny trainer, it will stop immediately (albeit painfully).

Write a function solution(dimensions, your_position, trainer_position, distance) that gives an array of 2 integers of the width and height of the room,
an array of 2 integers of your x and y coordinates in the room, an array of 2 integers of the trainer's x and y coordinates in the room,
and returns an integer of the number of distinct directions that you can fire to hit the elite trainer, given the maximum distance that the beam can travel.

The room has integer dimensions [1 < x_dim <= 1250, 1 < y_dim <= 1250].
You and the elite trainer are both positioned on the integer lattice at different distinct positions (x, y) inside the room such that [0 < x < x_dim, 0 < y < y_dim].
Finally, the maximum distance that the beam can travel before becoming harmless will be given as an integer 1 < distance <= 10000.

For example, if you and the elite trainer were positioned in a room with dimensions [3, 2], your_position [1, 1], trainer_position [2, 1], and a maximum shot distance of 4,
you could shoot in seven different directions to hit the elite trainer (given as vector bearings from your location):

[1, 0], [1, 2], [1, -2], [3, 2], [3, -2], [-3, 2], and [-3, -2].

As specific examples, the shot at bearing [1, 0] is the straight line horizontal shot of distance 1,
the shot at bearing [-3, -2] bounces off the left wall and then the bottom wall before hitting the elite trainer with a total shot distance of sqrt(13),
and the shot at bearing [1, 2] bounces off just the top wall before hitting the elite trainer with a total shot distance of sqrt(5).

Languages
=========

To provide a Java solution, edit Solution.java
To provide a Python solution, edit solution.py

Test cases
==========
Your code should pass the following test cases.
Note that it may also be run against hidden test cases not shown here.

-- Java cases --
Input:
Solution.solution([3,2], [1,1], [2,1], 4)
Output:
    7

Input:
Solution.solution([300,275], [150,150], [185,100], 500)
Output:
    9

-- Python cases --
Input:
solution.solution([3,2], [1,1], [2,1], 4)
Output:
    7

Input:
solution.solution([300,275], [150,150], [185,100], 500)
Output:
    9
"""

import math


class Vector2:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.angle = math.atan2(y, x)
        self.mag = self.magnitude()
        self.tuple = (x, y)

    def magnitude(self):
        return math.hypot(self.x, self.y)

    def norm(self):
        return Vector2(self.x / self.magnitude(), self.y / self.magnitude())

    def __hash__(self):
        return hash(self.x) ^ hash(self.y)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __str__(self):
        return "(" + str(self.x) + " , " + str(self.y) + ")"


def direction_check(dir, x, y, h, w, forbidden_dirs):
    return (w > x > 0 and h > y > 0) or (dir.angle not in forbidden_dirs)


def euc_dist(p_x, p_y, t_x, t_y):
    return math.sqrt((t_x - p_x) ** 2 + (t_y - p_y) ** 2)


def direction(x1, y1, x2, y2):
    dir_x = (x2 - x1)
    dir_y = (y2 - y1)

    return dir_x, dir_y


def get_forbidden_directions(p_x, p_y, h, w):
    forbidden_directions = {Vector2(-1, 0).angle, Vector2(1, 0).angle, Vector2(0, -1).angle, Vector2(0, 1).angle}

    # 0,0
    dir_00 = Vector2(*direction(p_x, p_y, 0, 0))

    # 0,H
    dir_0H = Vector2(*direction(p_x, p_y, 0, h))

    # W, 0
    dir_W0 = Vector2(*direction(p_x, p_y, w, 0))

    # W, H
    dir_WH = Vector2(*direction(p_x, p_y, w, h))

    forbidden_directions.add(dir_00.angle)
    forbidden_directions.add(dir_0H.angle)
    forbidden_directions.add(dir_W0.angle)
    forbidden_directions.add(dir_WH.angle)

    return forbidden_directions


def get_all_positions(dimensions, your_position, trainer_position, distance):
    w, h = dimensions
    p_x, p_y = your_position
    t_x, t_y = trainer_position

    all_positions = []

    # Upwards Mirroring
    new_t_y = t_y
    new_p_y = p_y
    mirror_y_index = 0

    curr_dist = euc_dist(p_x, p_y, t_x, new_t_y)

    while curr_dist <= distance:
        all_positions.append(((p_x, new_p_y), (t_x, new_t_y)))

        # Mirroring Towards Right
        mirror_right_index = 0

        new_t_x = t_x + 2 * (w - t_x)
        new_p_x = p_x + 2 * (w - p_x)

        curr_right_dist = euc_dist(p_x, p_y, new_t_x, new_t_y)

        while curr_right_dist <= distance:
            all_positions.append(((new_p_x, new_p_y), (new_t_x, new_t_y)))

            # Update X
            if mirror_right_index % 2 == 1:
                new_t_x = new_t_x + 2 * (w - t_x)
                new_p_x = new_p_x + 2 * (w - p_x)
            else:
                new_t_x = new_t_x + 2 * t_x
                new_p_x = new_p_x + 2 * p_x

            curr_right_dist = euc_dist(p_x, p_y, new_t_x, new_t_y)

            mirror_right_index += 1

        # Mirroring Towards Left
        mirror_left_index = 0

        new_t_x = t_x - 2 * t_x
        new_p_x = p_x - 2 * p_x

        curr_left_dist = euc_dist(p_x, p_y, new_t_x, new_t_y)

        while curr_left_dist <= distance:

            all_positions.append(((new_p_x, new_p_y), (new_t_x, new_t_y)))

            # Update X
            if mirror_left_index % 2 == 0:
                new_t_x = new_t_x - 2 * (w - t_x)
                new_p_x = new_p_x - 2 * (w - p_x)
            else:
                new_t_x = new_t_x - 2 * t_x
                new_p_x = new_p_x - 2 * p_x

            curr_left_dist = euc_dist(p_x, p_y, new_t_x, new_t_y)
            mirror_left_index += 1

        # Update Y
        if mirror_y_index % 2 == 0:
            new_t_y = new_t_y + 2 * (h - t_y)
            new_p_y = new_p_y + 2 * (h - p_y)
        else:
            new_t_y = new_t_y + 2 * t_y
            new_p_y = new_p_y + 2 * p_y

        curr_dist = euc_dist(p_x, p_y, t_x, new_t_y)

        mirror_y_index += 1

    # Downwards Mirroring
    new_t_y = t_y - 2 * t_y
    new_p_y = p_y - 2 * p_y
    mirror_y_index = 0

    curr_dist = euc_dist(p_x, p_y, t_x, new_t_y)

    while curr_dist <= distance:
        all_positions.append(((p_x, new_p_y), (t_x, new_t_y)))

        # Mirroring Towards Right
        mirror_right_index = 0

        new_t_x = t_x + 2 * (w - t_x)
        new_p_x = p_x + 2 * (w - p_x)

        curr_right_dist = euc_dist(p_x, p_y, new_t_x, new_t_y)

        while curr_right_dist <= distance:
            all_positions.append(((new_p_x, new_p_y), (new_t_x, new_t_y)))

            # Update X
            if mirror_right_index % 2 == 0:
                new_t_x = new_t_x + 2 * t_x
                new_p_x = new_p_x + 2 * p_x
            else:
                new_t_x = new_t_x + 2 * (w - t_x)
                new_p_x = new_p_x + 2 * (w - p_x)

            curr_right_dist = euc_dist(p_x, p_y, new_t_x, new_t_y)

            mirror_right_index += 1

        # Mirroring Towards Left
        mirror_left_index = 0

        new_t_x = t_x - 2 * t_x
        new_p_x = p_x - 2 * p_x

        curr_left_dist = euc_dist(p_x, p_y, new_t_x, new_t_y)

        while curr_left_dist <= distance:
            all_positions.append(((new_p_x, new_p_y), (new_t_x, new_t_y)))

            # Update X
            if mirror_left_index % 2 == 0:
                new_t_x = new_t_x - 2 * (w - t_x)
                new_p_x = new_p_x - 2 * (w - p_x)
            else:
                new_t_x = new_t_x - 2 * t_x
                new_p_x = new_p_x - 2 * p_x

            curr_left_dist = euc_dist(p_x, p_y, new_t_x, new_t_y)

            mirror_left_index += 1

        # Update Y
        if mirror_y_index % 2 == 0:
            new_t_y = new_t_y - 2 * (h - t_y)
            new_p_y = new_p_y - 2 * (h - p_y)
        else:
            new_t_y = new_t_y - 2 * t_y
            new_p_y = new_p_y - 2 * p_y

        curr_dist = euc_dist(p_x, p_y, t_x, new_t_y)

        mirror_y_index += 1

    return all_positions


def solution(dimensions, your_position, trainer_position, distance):
    w, h = dimensions
    p_x, p_y = your_position
    t_x, t_y = trainer_position

    initial_dist = euc_dist(p_x, p_y, t_x, t_y)

    if initial_dist > distance:
        return 0
    elif initial_dist == distance:
        return 1

    forbidden_dirs = get_forbidden_directions(p_x, p_y, h, w)

    all_positions = get_all_positions(dimensions, your_position, trainer_position, distance)

    valid_dir = {}

    player_directions = {}

    for (pos_p, pos_t) in all_positions:
        dir_t = Vector2(*direction(p_x, p_y, pos_t[0], pos_t[1]))
        dir_p = Vector2(*direction(p_x, p_y, pos_p[0], pos_p[1]))

        if dir_p.angle not in player_directions:
            if dir_p.mag != 0:
                player_directions[dir_p.angle] = dir_p.mag
        else:
            if player_directions[dir_p.angle] > dir_p.mag:
                player_directions[dir_p.angle] = dir_p.mag

        angle_existence_check = (dir_t.angle not in valid_dir) or \
                                (dir_t.angle in valid_dir and dir_t.mag < valid_dir[dir_t.angle])

        # In some cases it will speed it up, makes sense to add it to generation :D
        h_w_direction_check = direction_check(dir_t, pos_t[0], pos_t[1], h, w, forbidden_dirs)

        player_hit_check = not (
                dir_t.angle == dir_p.angle and (dir_t.mag >= dir_p.mag > 0))

        other_player_hit_check = (dir_t.angle not in player_directions) or \
                                 (dir_t.angle in player_directions and dir_t.mag <= player_directions[dir_t.angle]) or \
                                 (player_directions[dir_t.angle] == 0)

        if angle_existence_check and player_hit_check and other_player_hit_check and h_w_direction_check:
            valid_dir[dir_t.angle] = dir_t.mag

    return len(valid_dir.keys())


import matplotlib.pyplot as plt
import numpy as np


def visualize(p_x, p_y, vec):
    xs = [p_x]
    ys = [p_y]
    for elem in vec:
        xs.append(elem.x + p_x)
        ys.append(elem.y + p_y)

    xs = np.array(xs)
    ys = np.array(ys)

    fig = plt.figure()
    ax = fig.add_subplot(111)
    ax.scatter(xs, ys)

    for i in range(1, len(xs)):
        ax.plot([p_x, xs[i]], [p_y, ys[i]], '-ok', mfc='C1', mec='C1')
    ax.grid()

    plt.show()


import time


def main():
    cases = [
        ([3, 2], [1, 1], [2, 1], 4, 7),
        ([300, 275], [150, 150], [185, 100], 500, 9),
        ([10, 10], [4, 4], [3, 3], 5000, 739323),
        ([2, 5], [1, 2], [1, 4], 11, 27),
        ([23, 10], [6, 4], [3, 2], 23, 8),
        ([1250, 1250], [1000, 1000], [500, 400], 10000, 196)
    ]

    for (dim, your_pos, trainer_pos, dst, answer) in cases:
        start = time.time()
        res = solution(dim, your_pos, trainer_pos, dst)
        total = time.time() - start
        print("Time : ", total)
        if res != answer:
            print(f"Dim : {dim} | Your Pos : {your_pos} | Trainer Pos : {trainer_pos} | distance : {dst}")
            print(f"Expected : {answer} | Received : {res}")
        else:
            print("Success")


if __name__ == '__main__':
    main()
