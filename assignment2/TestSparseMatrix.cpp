#include "SparseMatrix.h"

using namespace std;
void main()
{
	int val[8] = { 15, 22, -15, 11, 3, -6, 91, 28 };
	int val2[5] = { 1, 2, 1, 3, 1 };
	int val3[3] = { 1, 1, 1 };

	SparseMatrix a;
	a.Init2(val2);
	cout << "Sparse matrix a, row=3, col=3" << endl;
	a.Output();
	a.OutputToMatrice();
	cout << "-----------------------------" << endl;

	cout << "Sparse matrix b, row=3, col=4" << endl;
	SparseMatrix b;
	b.Init3(val3);
	b.Output();
	b.OutputToMatrice();
	cout << "-----------------------------" << endl;

	cout << "transpose matrix a" << endl;
	SparseMatrix transposeOfMatrixA = a.Transpose();
	transposeOfMatrixA.Output();
	transposeOfMatrixA.OutputToMatrice();
	cout << "-----------------------------" << endl;

	cout << "fast transpose matrix b" << endl;
	SparseMatrix fastTransposeOfMatrixB = b.FastTranspose();
	fastTransposeOfMatrixB.Output();
	fastTransposeOfMatrixB.OutputToMatrice();
	cout << "-----------------------------" << endl;

	cout << "matrix a multiply matrix b (axb), c" << endl;
	SparseMatrix c = a.Multiply(b);
	c.Output();
	c.OutputToMatrice();
	cout << "-----------------------------" << endl;

	cout << "matric b add c (b + c):" << endl;
	cout << "---b----" << endl;
	b.OutputToMatrice();
	cout << "---c---" << endl;
	c.OutputToMatrice();
	cout <<endl << "---result---" << endl;
	SparseMatrix d = b.Add(c);
	d.OutputToMatrice();

	system("pause");
}
