"""
Challenge 3.1

Find the Access Codes
=====================
In order to destroy Commander Lambda's LAMBCHOP doomsday device, you'll need access to it. But the only door leading to
the LAMBCHOP chamber is secured with a unique lock system whose number of passcodes changes daily. Commander Lambda
gets a report every day that includes the locks' access codes, but only she knows how to figure out which of several
lists contains the access codes. You need to find a way to determine which list contains the access codes once you're
ready to go in.
Fortunately, now that you're Commander Lambda's personal assistant, she's confided to you that she made all the access
codes "lucky triples" in order to help her better find them in the lists. A "lucky triple" is a tuple (x, y, z) where
x divides y and y divides z, such as (1, 2, 4). With that information, you can figure out which list contains the number
of access codes that matches the number of locks on the door when you're ready to go in (for example, if there's 5
passcodes, you'd need to find a list with 5 "lucky triple" access codes).
Write a function answer(l) that takes a list of positive integers l and counts the number of "lucky triples" of
(lst[i], lst[j], lst[k]) where i < j < k.  The length of l is between 2 and 2000 inclusive.  The elements of l are
between 1 and 999999 inclusive.  The answer fits within a signed 32-bit integer. Some of the lists are purposely
generated without any access codes to throw off spies, so if no triples are found, return 0.
For example, [1, 2, 3, 4, 5, 6] has the triples: [1, 2, 4], [1, 2, 6], [1, 3, 6], making the answer 3 total.
Languages
=========
To provide a Python solution, edit solution.py
To provide a Java solution, edit solution.java
Test cases
==========
Inputs:
    (int list) l = [1, 1, 1]
Output:
    (int) 1
Inputs:
    (int list) l = [1, 2, 3, 4, 5, 6]
Output:
    (int) 3
"""


def solution_count_once(values):
    """
    I misunderstood the question and solved like this!
    Case : 1, 1, 1, 2 -> 2 for this version
    """
    if len(values) < 3:
        return 0

    length = len(values)

    memo = {}

    all_triplets = {}

    triplet_count = 0

    for ix in range(length - 1, -1, -1):
        val_x = values[ix]
        if not memo.get(val_x):
            memo[val_x] = {"p": {}}

        for iy in range(ix + 1, length, 1):
            val_y = values[iy]

            if val_y % val_x == 0:
                for pair_y, p_idx in memo[val_y]["p"].items():
                    triplet = str(val_x) + " " + str(val_y) + " " + str(pair_y)

                    # Order is important
                    if p_idx > iy:
                        if not all_triplets.get(triplet):
                            all_triplets[triplet] = 0
                        all_triplets[triplet] += 1
                        triplet_count += 1

                if not memo[val_x]["p"].get(val_y):
                    memo[val_x]["p"][val_y] = iy

    return triplet_count  # len(all_triplets)


def solution(values):
    if len(values) < 3:
        return 0

    length = len(values)
    divisor_memo = [0 for _ in range(length)]
    total_triplets = 0

    for ix in range(length):
        val_x = values[ix]
        for iy in range(ix + 1, length, 1):
            val_y = values[iy]
            if val_y % val_x == 0:
                divisor_memo[iy] += 1  # A new divisor found for iy'th element!
                total_triplets += divisor_memo[ix]  # every ix'th divisor can be used to create a triplet
    return total_triplets


if __name__ == '__main__':
    cases = [([1, 1, 1], 1),
             ([1, 1, 1, 2], 4),
             ([1, 2, 3, 4, 5, 6, 7], 3),
             ([4, 8, 4, 16], 2),
             ([4, 7, 14, 8, 21, 56, 42], 4),
             ([4, 21, 7, 14, 56, 8, 56, 4, 42], 7),
             (list(range(1, 2001)), 40888)]

    for case in cases:
        correct_answer = case[1]
        lst = case[0]
        algo_answer = solution(lst)

        if algo_answer != correct_answer:
            input(f"{lst} {correct_answer} {algo_answer}")
