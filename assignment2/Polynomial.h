#include <iostream>
#include <iomanip>

using namespace std;

class Matrix {

public:

	Matrix(int m, int n);

	bool All_tile(Matrix a); //모든 타일을 밟았는지

	bool moving(int x, int &imove, int &jmove); //바퀴벌레 움직임

	void initialize(Matrix a);

	bool room(int imove, int jmove); //방안에 있는지

	void display(int counter);

	void Count(int imove, int jmove);


private:
	int m, n;
	int rows, cols;//전역변수
	int *data;
};


Matrix::Matrix(int m, int n) : rows(m), cols(n)
{
	data = new int[m * n];
}

bool Matrix::All_tile(Matrix a)

{
	for (int i = 0; i < m; i++)

		for (int j = 0; j < n; j++)

			if (data[i*n + j] == 0)

				return false;

	return true;

}

bool Matrix::moving(int x, int &ibug, int &jbug)

{

	int imove[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };

	int jmove[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };

	int i = ibug + imove[x], j = jbug + jmove[x];

	if (room(i, j)) //움직임을 가세했을 때 여전히 방 안이여야한다

	{

		ibug = i;

		jbug = j;

		return true;

	}

	return false;

}

void Matrix::initialize(Matrix a)

{

	data[0] = 0;

}

bool Matrix::room(int ibug, int jbug)

{

	if (ibug >= m || ibug < 0 || jbug >= n || jbug < 0)
		return false;

	else

		return true;

}

void Matrix::Count(int ibug, int jbug)
{
	rows = ibug;
	cols = jbug;

	data[rows]++;
	data[cols]++;
}

void Matrix::display(int counter)

{

	for (int i = 0; i < cols; i++)

	{

		for (int j = 0; j < rows; j++)

			cout << setw(3) << data[i*cols + j] << " ";

		cout << endl;

	}




}
