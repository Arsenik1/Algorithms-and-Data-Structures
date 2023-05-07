#include <iostream>
#include <vector>
#include <stack>

using namespace std;

bool is_connected(vector<vector<int>> graph, int num_nodes) {
    vector<bool> visited(num_nodes, false); // keep track of visited nodes
    stack<int> stk;
    stk.push(0); // start from node 0
    visited[0] = true;
    int num_visited = 1; // count the number of visited nodes

    while (!stk.empty()) {
        int curr = stk.top();
        stk.pop();

        for (int neighbor : graph[curr]) {
            if (!visited[neighbor]) {
                stk.push(neighbor);
                visited[neighbor] = true;
                num_visited++;
            }
        }
    }

    return (num_visited == num_nodes);
}

bool find_loop(vector<vector<int>> matrix, int matrix_size)
{
	vector<int> horizontal(matrix_size, 0), vertical(matrix_size, 0);
	int reverse_diagonal_counter = 0;
	for(int i = 0; i < matrix_size; i++)
	{
		for(int j = 0; j < matrix_size; j++)
		{
			if(matrix.at(i).at(j) > 1) 	//more than one sides
				return false;
			
			if(matrix.at(i).at(j) == 1)	//counter increase when encounter
			{
				++(horizontal.at(i));
				++(vertical.at(j));
			}

			if(matrix.at(i).at(j) == 1)	//chech diagonal "1" symmetry
			{
				if(matrix.at(i).at(j) == 1 && matrix.at(j).at(i) == 1)
				{

				}
				else
					return false;
			}
			if(j == matrix_size - i - 1 && matrix.at(i).at(j) == 1)
				++reverse_diagonal_counter;
		}
	}
	if(reverse_diagonal_counter <= 1)
		return false;

	for(int a = 0; a < matrix_size; a++)
	{
		if(horizontal.at(a) != 2 || vertical.at(a) != 2)
			return false;
	}
	return true;
}

void draw_vector(vector<vector<int>> matrix, int matrix_size)
{
	for(int i = 0; i < matrix_size; i++)
	{
		for(int j = 0; j < matrix_size; j++)
		{
			cout << matrix.at(i).at(j) << " ";
		}
		cout << endl;
	}
}

int main()
{
	int input_lines = 0;
	int matrix_size = 3;
	cin >> input_lines;
	vector<vector<int>> matrix(matrix_size, vector<int>(matrix_size, 0));

	while(input_lines--)
	{
		cin >> matrix_size;
		matrix.resize(matrix_size, vector<int>(matrix_size, 0));
		for(auto &a : matrix)
			a.resize(matrix_size, 0);
		char tmp;
		// cin >> tmp;
		for(int i = 0; i < matrix_size; i++)
		{
			for(int j = 0; j < matrix_size; j++)
			{
				cin >> tmp;
				// if(tmp > '9' || tmp < '0')
				// 	cout << "farkli karakter ASCII: " << (int)tmp;
				matrix[i][j] = tmp - '0';
			}
		}

		// cout << endl << matrix_size << endl;
		// cout << "ooooooooooooooooooooooooooooooooooooo" << endl;
		if(is_connected(matrix, matrix_size) && find_loop(matrix, matrix_size))
			cout << 1 << endl;
		else cout << 0 << endl;
		draw_vector(matrix, matrix_size);
		// cout << "-------------------------------------" << endl;

	}
	// cout << "aaaaaaaaaaaaaaaaaaaaaaaa";
	return 0;
}

// 5
// 3 011101110
// 7 0110000101000011000000000101000101000001010001010
// 7 0100001101000001010000010100000101000001011000010
// 5 0101010000000011000000100
// 5 0100110010000110110010100