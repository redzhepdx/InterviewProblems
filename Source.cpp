//#include "structures.h"
#include "google_interview_questions.h"
#include "amazon_interview_questions.h"
#include "facebook_interview_questions.h"
#include "microsoft_interview_questions.h"


int main(void) {
	
	int chessBoard[CHESS_EDGE][CHESS_EDGE];
	for (int i = 0; i < CHESS_EDGE; i++) {
		for (int j = 0; j < CHESS_EDGE; j++) {
			chessBoard[i][j] = -1;
		}
	}


	int row_ch[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int col_ch[8] = { -1, -2, -2, -1 , 1, 2, 2, 1 };


	int step = 0;
	chessBoard[0][0] = 0;
	bool res = knights_tour(chessBoard, 0, 0, 1, row_ch, col_ch);
	if (res) {
		for (int i = 0; i < CHESS_EDGE; i++) {
			for (int j = 0; j < CHESS_EDGE; j++) {
				std::cout << chessBoard[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	else {
		std::cout << "There is no path" << std::endl;
	}

	/*
	char matrix[CHAR_MTR_ROW][CHAR_MTR_COL] = { 
												{ 'F', 'A', 'C', 'I' },
												{ 'O', 'B', 'Q', 'P' },
												{ 'A', 'N', 'O', 'B' },
												{ 'M', 'A', 'S', 'S' }
											  };
	
	std::string s = "CQOS";
	std::string res = findWordInMatrix(matrix, s) ? "found" : "not found";
	std::cout << " The string : " << s << " " <<  res << " in matrix!" << std::endl;
	
	std::vector<std::vector<int>> matrix = generateZeroMatrix(MTR_SIZE, MTR_SIZE);
	int way_count = count_ways(matrix, 0, 0);
	std::cout << "Total Path Count : " << way_count << std::endl;
	
	std::unordered_map<std::string, int> memo;
	std::clock_t begin = std::clock();
	uint64_t res = efficient_pow_iterative(2, 100000);
	std::cout << "res : " << res << std::endl;
	std::clock_t end = std::clock();
	std::cout << "Time : " << double(end - begin) / 100000 << std::endl;

	std::clock_t begin2 = std::clock();
	uint64_t res2 = normal_pow(2, 100000);
	std::cout << "res : " << res2 << std::endl;
	std::clock_t end2 = std::clock();
	std::cout << "Time : " << double(end2 - begin2) / 100000 << std::endl;

	
	
	ColorNode * a = new ColorNode("a");
	ColorNode * b = new ColorNode("b");
	ColorNode * c = new ColorNode("c");
	ColorNode * d = new ColorNode("d");
	ColorNode * e = new ColorNode("e");
	ColorNode * f = new ColorNode("f");

	a->neighbours.push_back(b);
	b->neighbours.push_back(c);
	b->neighbours.push_back(a);
	b->neighbours.push_back(d);
	c->neighbours.push_back(b);
	c->neighbours.push_back(d);
	c->neighbours.push_back(e);
	c->neighbours.push_back(f);
	d->neighbours.push_back(b);
	d->neighbours.push_back(c);
	d->neighbours.push_back(e);
	d->neighbours.push_back(f);
	e->neighbours.push_back(d);
	e->neighbours.push_back(c);
	f->neighbours.push_back(c);
	f->neighbours.push_back(d);

	std::cout << findMaxColorCount(a) << std::endl;
	

	
	std::vector<int> list;

	for (int i = 1; i <= 5; i++) {
	//list.push_back(rand() % 100);
	list.push_back(i);
	std::cout << list.back() << " ";
	}
	list.push_back(15);

	std::cout << std::endl;

	bool res = contains_same_sum(list, list[0], 0, 1);
	std::string s = " ";
	(res) ? s = "True" : s = "False";
	std::cout << "Has same two subset : " << s << std::endl;


	int matrix[SUDOKU_SIZE][SUDOKU_SIZE] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
										   { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
										   { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
									       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
										   { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
										   { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
										   { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
										   { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
										   { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
	std::cout << "Before " << std::endl;
	showMatrix(matrix);
	std::cout << std::endl;

	bool ret = SolveSudoku(matrix);
	if (ret) {
		std::cout << "After " << std::endl;
		showMatrix(matrix);
		std::cout << std::endl;
	}
	else {
		std::cout << "There isn't solution for this matrix" << std::endl;
	}

	exp_node * root				= new exp_node('*');
	root->left					= new exp_node('+');
	root->right					= new exp_node('+');
	root->left->left			= new exp_node( 3 );
	root->left->right			= new exp_node( 2 );
	root->right->left			= new exp_node( 4 );
	root->right->right			= new exp_node('-');
	root->right->right->left	= new exp_node( 5 );
	root->right->right->right	= new exp_node( 6 );
	ExpressionTree * exp_tree	= new ExpressionTree(root);
	
	std::cout << "Result Of Tree : " << exp_tree->getResultOfTree(root) << std::endl;
	std::vector<int> list;
	list.push_back(-2);
	list.push_back(3);
	list.push_back(-7);
	list.push_back(6);
	list.push_back(-5);
	list.push_back(7);
	list.push_back(-8);
	list.push_back(1);
	list.push_back(-4);
	list.push_back(6);
	int max = find_max_subarray(list);
	std::cout << "max value : " << max << std::endl;

	
	std::vector<int> list;
	int size = 100;

	for (int i = 0; i < size; i++) {
		//list.push_back(rand() % 100);
		list.push_back(i);
		std::cout << list.back() << " ";
	}
	std::cout << std::endl;

	int count = count_out_of_orders(list);
	std::cout << " Out of Order Count : "<< count << std::endl;

	std::cout << "Sorted Array " << std::endl;
	for (int i = 0; i < list.size(); i++) {
		std::cout << list[i] << " ";
	}
	std::cout << std::endl;
	
	std::cout << fib(50) << std::endl;	
	
	std::unordered_map<int, int> memo;
	std::cout << memo_fib(10000, memo) << std::endl;

	std::cout << iterative_fib(1000000) << std::endl;
	

	int k, c;
	std::cin >> k >> c;

	int non_rep = getNonRepeatingElem(k, c);

	getchar();

	std::vector<char> rgbList;

	int n;

	std::cout << "Max Elem Size : ";
	std::cin >> n;

	int lowest = 1;
	int highest = 3;

	for (int i = 0; i < n; i++) {
		int random = lowest + rand() % highest;

		switch (random)
		{
		case 1:
			rgbList.push_back('R');
			break;
		case 2:
			rgbList.push_back('G');
			break;
		case 3:
			rgbList.push_back('B');
			break;
		default:
			break;
		}

	}

	std::vector<char> organizedArray = organizeArray(rgbList);
	*/

	getchar();
	return 0;
}