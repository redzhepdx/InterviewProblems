import math
import time

def next_prime(prev_value):
	found = False
	target = prev_value + 2	

	prev_sqrt = int(math.sqrt(prev_value))

	while not found:
		target_sqrt = int(math.sqrt(target))
		isPrime = True
		
		for i in range(3, target_sqrt + 1, 2):
			if target % i == 0:
				isPrime = False
				break;

		if isPrime:
			found = True
		else:
			target += 2
	
	return target

def main():
	query_index = input()
	query_index = int(query_index)
	
	start = time.time()

	output_string = "23571113171923293137414347"
	prev_prime = 47
	prime_count = 15

	while query_index > (len(output_string) - 5):
		nxt_prime = next_prime(prev_prime)
		output_string += str(nxt_prime)
		# input(nxt_prime)
		prev_prime = nxt_prime
		prime_count += 1
	
	print("prime count : ", prime_count)
	print("previous prime : ", prev_prime)
	print("output string : ", output_string)
	print("output : ", output_string[query_index : query_index + 5])
	
	print("Time : ", time.time() - start)

if __name__ == "__main__":
	main()
