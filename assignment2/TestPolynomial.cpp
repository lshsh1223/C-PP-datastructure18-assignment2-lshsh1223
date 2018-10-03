#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <iomanip>
#include "Polynomial.h"

using namespace std;




int main(void)

{
	int m, n;

	srand((unsigned)time(NULL));
	int x, ibug, jbug, counter = 0;



	cout << "가로 크기(m):(2~40) ";

	cin >> m;

	while (m > 40 || m < 2)

	{

		cout << "범위에 안맞음" << endl << "2~40 사이: ";

		cin >> m;

	}

	cout << "세로 크기(n):(2~20) ";

	cin >> n;

	while (n > 20 || n < 2)

	{

		cout << "범위에 안맞음" << endl << "2~20 사이: ";

		cin >> n;

	}


	cout << "시작점 : ( , ) ";

	cin >> ibug >> jbug;


	Matrix a(m, n);






	while ((!a.All_tile(a)) && (counter < 50000))

	{

		do

		{

			x = rand() % 8;

		} while (!a.moving(x, ibug, jbug));

		a.Count(ibug, jbug);

		counter++;

	}



	cout << "총 움직인 횟수: " << counter << endl;

	a.display(counter);

	cout << "모든 타일을 밟았습니다" << endl;



	system("pause");
	return 0;

}
