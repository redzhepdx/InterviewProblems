def solution(power_levels):
	if len(power_levels) == 1:
		return power_levels[0]
	
	negative_min = -999999999
	negative_product = 1
	positive_product = 1

	negative_count = 0
	positive_count = 0
	
	zero_found = False

	for power_level in power_levels:
		if power_level > 0:
			positive_product *= power_level
			positive_count += 1

		elif power_level < 0:
			negative_product *= power_level
			negative_min = max(power_level, negative_min)
			negative_count += 1
		else:
			zero_found = True

	# Full of zeros
	if negative_count == 0 and positive_count == 0:
		return 0
	
	# Odd numbered and more than 2 negative values
	if negative_product < 0 and negative_count > 2:
		negative_product = negative_product // negative_min
	# At least one positive value found and there is only one negative value
	elif positive_count > 0 and negative_product < 0:
		negative_product = 1
	
	# One negative value case
	if negative_product < 0 and positive_count == 0:
		# One negative value and zeros [-2, 0, 0, 0 ......]
		if zero_found:
	 		positive_product = 0

	return positive_product * negative_product

def main():
	big_value = 1
	for i in range(50):
		big_value *= 1000

	cases = { 8 : [2, 0, 2, 2, 0],
			  60 : [-2, -3, 4, -5],
			  0 : [-5, 0],
			  30 : [-6, -5, 0],
			  10 : [10],
			  1 : [-2, 1, 1, 1, 1, 1],
			  6 : [-3, -2, 0, 0, 0, 0],
			  0 : [-3, 0],
			  30 : [2,-3, 1, 0,-5],
			  6 : [-2, -2, -3],
			  24 : [-2, -2, 0, 0, -2, -3],
			  24 : [-2, -2, 0, 0, 2, 3],
			  24 : [2, 3, 0, 0, 2, 2],
			  0 : [0, 0, 0],
			  1 : [0, 0, 1],
			  big_value : [1000 for i in range(50)]
			  }
	for answer, case in cases.items():
		result = solution(case)
		if answer != result:
			print(f"CASE : {case} \nANSWER : {answer} \nPREDICTION : {result}\nSUCCESS : {answer == result}")


if __name__ == "__main__":
	main()
