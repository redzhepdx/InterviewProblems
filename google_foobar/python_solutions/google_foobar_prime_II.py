import math
import time

# 100 - 197
# 1000 - 1997
# 10000 - 20000
# 100000 - 20000...
# X -> Y <= 2.2 * X

# 1 2 3 4 5 6 7 8 9 10
# F T T F T F T F F F

def main():
	index = int(input())

	start = time.time()

	target_max_number = max(int(index * 2.2), 150)
	print(target_max_number)
	isPrime = [True] * target_max_number

	isPrime[0] = False
	isPrime[1] = False

	output_str = ""
	for i in range(2, target_max_number):
		if isPrime[i]:
			output_str += str(i)

			for factor_i in range(i + i, target_max_number, i):
				isPrime[factor_i] = False

	print("Time : ", time.time() - start)
	# print("String : ", output_str)
	print("Output : ", output_str[index:index + 5])

if __name__ == "__main__":
	main()
