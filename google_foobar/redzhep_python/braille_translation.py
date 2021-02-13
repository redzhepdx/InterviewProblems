"""
Challenge 1

Because Commander Lambda is an equal-opportunity despot, she has several visually-impaired minions.
But she never bothered to follow intergalactic standards for workplace accommodations, so those minions have a hard time navigating her space station.
You figure printing out Braille signs will help them, and – since you’ll be promoting efficiency at the same time – increase your chances of a promotion.
Braille is a writing system used to read by touch instead of by sight. Each character is composed of 6 dots in a 2×3 grid,
where each dot can either be a bump or be flat (no bump).
You plan to translate the signs around the space station to Braille so that the minions under Commander Lambda’s command can feel the bumps on the signs and “read” the text with their touch.
The special printer which can print the bumps onto the signs expects the dots in the following order:

1 4
2 5
3 6

So given the plain text word “code”, you get the Braille dots:


11 10 11 10
00 01 01 01
00 10 00 00

Write a function where 1 represents a bump and 0 represents no bump. Put together, “code” becomes the output string “100100101010100110100010”.

Write a function answer(plaintext) that takes a string parameter and returns a string of 1’s and 0’s representing the bumps and absence of bumps in the input string.
Your function should be able to encode the 26 lowercase letters, handle capital letters by adding a Braille capitalization mark before that character, and use a blank character (000000) for spaces.
All signs on the space station are less than fifty characters long and use only letters and spaces.

Inputs:
  (string) plaintext = "code"

Output:
  (string) "100100101010100110100010"

Inputs:
  (string) plaintext = "Braille"

Output:
  (string) "000001110000111010100000010100111000111000100010"

Inputs:
  (string) plaintext = "The quick brown fox jumped over the lazy dog"

Output:
  (string) "000001011110110010100010000000111110101001010100100100101000000000110000111010101010010111101110000000110100101010101101000000010110101001101100111100100010100110000000101010111001100010111010000000011110110010100010000000111000100000101011101111000000100110101010110110"

"""

braille_alphabet = {" ": "000000",
                    "a": "100000",
                    "b": "110000",
                    "c": "100100",
                    "d": "100110",
                    "e": "100010",
                    "f": "110100",
                    "g": "110110",
                    "h": "110010",
                    "i": "010100",
                    "j": "010110",
                    "k": "101000",
                    "l": "111000",
                    "m": "101100",
                    "n": "101110",
                    "o": "101010",
                    "p": "111100",
                    "q": "111110",
                    "r": "111010",
                    "s": "011100",
                    "t": "011110",
                    "u": "101001",
                    "v": "111001",
                    "w": "010111",
                    "x": "101101",
                    "y": "101111",
                    "z": "101011"}


def solution(text):
    barille_code = ""
    for letter in text:
        if letter.isupper():
            barille_code += ("000001" + braille_alphabet[letter.lower()])
        else:
            barille_code += braille_alphabet[letter]
    return barille_code


if __name__ == "__main__":
    cases = {"code": "100100101010100110100010",
             "Braille": "000001110000111010100000010100111000111000100010",
             "The quick brown fox jumps over the lazy dog": f"0000010111101100101000100000001111"
                                                            f"10101001010100100100101000000000110"
                                                            f"000111010101010010111101110000000110"
                                                            f"1001010101011010000000101101010011011"
                                                            f"00111100011100000000101010111001100010"
                                                            f"111010000000011110110010100010000000111"
                                                            f"000100000101011101111000000100110101010110110",
             "The": "000001011110110010100010"}

    for case, answer in cases.items():
        res = solution(case)
        if res != answer:
            for idx in range(len(answer)):
                if answer[idx] != res[idx]:
                    input(f"{answer[idx]} - {res[idx]} {idx}")
            print(case)
            print(len(res))
            print(len(answer))
            print(res)
            print(answer)
