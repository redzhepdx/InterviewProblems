/*
 Problem : 
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stdio.h>

std::vector<int> shift_array(std::string str) {

	int len = str.length();
	int i = 0, j = 1;

	std::vector<int> lbs(len);
	
	while (j < len) {
		if (str[i] == str[j]) {
			i++;
			lbs[j] = i;
			j++;
		}
		else {
			if (i != 0) {
				i = lbs[i - 1];
			}
			else {
				lbs[j] = 0;
				j++;
			}
		}
	}

	return lbs;


}

int kmp_string_search(std::string txt, std::string pat) {

	int len_txt = txt.length(), len_pat = pat.length();
	int txt_index = 0, pat_index = 0;
	std::vector<int> lbs = shift_array(pat);

	while (txt_index < len_txt) {
		if (pat[pat_index] == txt[txt_index]) {
			pat_index++;
			txt_index++;
		}
		
		if (pat_index == len_pat) {
			return txt_index - pat_index;
		}
		else if(txt_index < len_txt && pat[pat_index] != txt[txt_index]){
			if (pat_index != 0) {
				pat_index = lbs[pat_index - 1];
			}
			else {
				txt_index++;
			}
		}
	}

	return 0;
}

int cyclic_founder(std::string str) {
	std::string double_str = str + str;
	int index = kmp_string_search(double_str.substr(1, double_str.length() - 1), str);
	return index;
}

int main() {

	std::string str = "abcahabcah";
	int index = cyclic_founder(str);
	std::cout << "Cycle Found at : " << index + 1 << std::endl;
	getchar();
	return 0;
}
