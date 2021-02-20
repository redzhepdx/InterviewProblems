"""
Challenge 5.1

Dodge the Lasers!
=================

Oh no! You've managed to escape Commander Lambda's collapsing space station in an escape pod with the rescued bunny workers -
but Commander Lambda isnt about to let you get away that easily. Lambda sent an elite fighter pilot squadron after you -- and they've opened fire!

Fortunately, you know something important about the ships trying to shoot you down.
Back when you were still Lambda's assistant, the Commander asked you to help program the aiming mechanisms for the starfighters.
They undergo rigorous testing procedures, but you were still able to slip in a subtle bug.
The software works as a time step simulation: if it is tracking a target that is accelerating away at 45 degrees,
the software will consider the targets acceleration to be equal to the square root of 2, adding the calculated result to the targets end velocity at each timestep.
However, thanks to your bug, instead of storing the result with proper precision, it will be truncated to an integer before adding the new velocity to your current position.
This means that instead of having your correct position, the targeting software will erringly report your position as sum(i=1..n, floor(i*sqrt(2))) - not far enough off to fail Commander Lambdas testing,
 but enough that it might just save your life.

If you can quickly calculate the target of the starfighters' laser beams to know how far off they'll be, you can trick them into shooting an asteroid, releasing dust, and concealing the rest of your escape.
Write a function solution(str_n) which, given the string representation of an integer n, returns the sum of (floor(1*sqrt(2)) + floor(2*sqrt(2)) + ... + floor(n*sqrt(2))) as a string.
That is, for every number i in the range 1 to n, it adds up all of the integer portions of i*sqrt(2).

For example, if str_n was "5", the solution would be calculated as
floor(1*sqrt(2)) +
floor(2*sqrt(2)) +
floor(3*sqrt(2)) +
floor(4*sqrt(2)) +
floor(5*sqrt(2)) = 1+2+4+5+7 = 19

so the function would return "19".

str_n will be a positive integer between 1 and 10^100, inclusive. Since n can be very large (up to 101 digits!),
using just sqrt(2) and a loop won't work.

[IMPORTANT!]Sometimes, it's easier to take a step back and concentrate not on what you have in front of you, but on what you don't.

Useful Links:
- https://mathworld.wolfram.com/BeattySequence.html
- https://math.stackexchange.com/questions/2052179/how-to-find-sum-i-1n-left-lfloor-i-sqrt2-right-rfloor-a001951-a-beatty-s
- https://en.wikipedia.org/wiki/Beatty_sequence
"""

root_2 = 14142135623730950488016887242096980785696718753769480731766797379907324784621070388503875343276415727
one_minus_rt_2 = 4142135623730950488016887242096980785696718753769480731766797379907324784621070388503875343276415727
ten_over_hundred = 10 ** 100


def solve(value):
    if value < 1:
        return 0

    if value == 1:
        return 1

    # Theorem 1 : Beatty sequence -> floor(an) union floor(bn) = {1, ..... N}
    # m = floor(a * n)
    # S(a, n) + S(b, floor(m / b)) = m * (m + 1) / 2
    # S(a, n) = m * (m + 1) / 2 - S(b, floor(m / b))
    # floor(m / b) = m - ceil(m / n) = m - n = floor((a - 1) * n)
    m = int(value * root_2) // ten_over_hundred

    m_div_b = int(value * one_minus_rt_2) // ten_over_hundred

    # Theorem 2 : if a >= 2 B = a - 1 => S(a, n) = S(b, n) + n * (n + 1) / 2
    # S(2 + rt_2, x) = x * (x + 1) / 2 + S(1 + rt_2, x)
    # S(2 + rt_2, x) = x * (x + 1) / 2 + x * (x + 1) / 2 + S(rt_2, x)
    remaining = solve(m_div_b)

    return int((m * (m + 1) / 2) - (m_div_b * (m_div_b + 1)) - remaining)


def solution(s):
    val = int(s)
    return str(solve(val))


import math

rt_2 = math.sqrt(2)


def check_pattern(s):
    val = int(s)
    total = 1
    operation_str = "1"
    for i in range(1, val):
        operation_str += f" + {int((i + 1) * rt_2)}"
        total += int((i + 1) * rt_2)

    operation_str += f" = {total}"
    print(*list(range(1, val + 1)))
    print(operation_str)
    return total


def main():
    small_range = range(1, 10000, 1)
    large_range = range(
        100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000,
        100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010, 1)

    for i in small_range:
        answer = check_pattern(str(i))
        given = int(solution(str(i)))
        if answer != given:
            input(f"value : {i} result : {answer} solution : {given} Diff : {given - answer}")
        else:
            print(f"value : {i} result : {answer} solution : {given}")
        print("=======================================================================================================")

    for i in large_range:
        result = solution(str(i))
        print(f"Result : {result}")
        print("=======================================================================================================")


if __name__ == '__main__':
    main()
