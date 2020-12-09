#include <iostream>
#include "MultyStack.h"

void main()
{
	MultyStack<int> s(12, 3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			s.push(j,i);
		}
	}
	cout << "Multystack" << endl << s << endl;
	int m = 0;
	m = s.MaxStack();
	cout << "Znachenie stecka ravno" << endl << m << endl;
    s.Rotate(1);
	cout << "Changed multystack" << endl << s << endl;
	s.DelEv(1);
	cout << "Changed multystack" << endl << s << endl;
}
