def solution(pegs):
	if ((not pegs) or len(pegs) == 1):
		return [-1,-1]

	x_signature = 1
	diff = 0

	for i in range(1, len(pegs), 1):
		x_signature *= -1

		diff = (pegs[i] - pegs[i - 1]) - diff

	if x_signature == -1 and diff > 0:
		current_radius = 2 * diff / 3

		if current_radius < 2:
			return [-1, -1]

		valid = True

		for i in range(1, len(pegs), 1):
			if pegs[i - 1] + current_radius < pegs[i] and current_radius >= 1:
				current_radius = (pegs[i] - pegs[i - 1]) - current_radius
			else:
				valid = False
				break

		if valid:
			if diff % 3 == 0:
				diff = diff // 3
				return [2 * diff, 1]
			return [2 * diff, 3]
		else:
			return [-1, -1]

	elif x_signature == 1 and diff < 0:
		current_radius = -2 * diff

		if current_radius < 2:
			return [-1, -1]

		valid = True
		for i in range(1, len(pegs), 1):
			if pegs[i - 1] + current_radius < pegs[i] and current_radius >= 1:
				current_radius = (pegs[i] - pegs[i - 1]) - current_radius
			else:
				valid = False
				break
	
		if valid:
			return [-2 * diff, 1]
		else:
			return [-1, -1]
	else:
		return [-1, -1]


if __name__ == "__main__":
	cases = [
		[1, 2, 3],
		[1, 2, 3, 4],
		[2, 4, 6],
		[10, 20, 30, 40, 45],
		[5, 15, 20],
        [4, 30, 50],
        [4, 17, 50],
        [1, 51],
        [1, 31],
        [1, 31, 51, 71],
        [1, 31, 51, 71, 91],
        [4, 9, 17, 31, 40],
		[2827, 3797, 4856, 5398, 6400, 7191],
		[850, 852],
		[4, 16, 24, 30, 34],
    ]

	for case in cases[-1:]:
		print(case)
		print(solution(case))
