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



	cout << "���� ũ��(m):(2~40) ";

	cin >> m;

	while (m > 40 || m < 2)

	{

		cout << "������ �ȸ���" << endl << "2~40 ����: ";

		cin >> m;

	}

	cout << "���� ũ��(n):(2~20) ";

	cin >> n;

	while (n > 20 || n < 2)

	{

		cout << "������ �ȸ���" << endl << "2~20 ����: ";

		cin >> n;

	}


	cout << "������ : ( , ) ";

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



	cout << "�� ������ Ƚ��: " << counter << endl;

	a.display(counter);

	cout << "��� Ÿ���� ��ҽ��ϴ�" << endl;



	system("pause");
	return 0;

}
