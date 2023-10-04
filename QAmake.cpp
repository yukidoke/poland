#include <bits/stdc++.h>
#include <direct.h>

using namespace std;

unsigned seed = chrono::system_clock::now().time_since_epoch().count();
mt19937 gen(seed);

int getRandRange(int low, int high)
{
	uniform_int_distribution<> dist(low, high);
	return dist(gen);
}

char getOp(int &select)
{
	char ret;
	switch (select)
	{
	case 1:
		ret = '+';
		break;

	case 2:
		ret = '-';
		break;

	case 3:
		ret = '*';
		break;

	case 4:
		ret = '/';
		break;
	
	default:
		ret = '+';
		break;
	}
	
	return ret;
}

double calc(double a, double b, int select)
{
	double ans;
	switch (select)
	{
	case 1:
		ans = a + b;
		break;

	case 2:
		ans = a - b;
		break;

	case 3:
		ans = a * b;
		break;

	case 4:
		ans = a / b;
		break;
	
	default:
		ans = 1;
		break;
	}
	
	return ans;
}

bool isOverflow(double addNum)
{
	string s = to_string(addNum);

	if(s.size() < 16) return false;
	else return true;
}

void calculator(string &questionFile, stack<long double> &data)
{
	int op = getRandRange(1, 4);
	char operand = getOp(op);
	int a = getRandRange(0, 1000), b = getRandRange(1, 1000);

	double ans = calc(a, b, op);

	while (isOverflow(ans))
	{
		op = getRandRange(1, 4);
		operand = getOp(op);
		ans = calc(a, b, op);
	}
	
	questionFile += to_string(a) + ' ' + to_string(b) + ' ' + operand + ' ';
	data.push(ans);
}

int main()
{
	int QAsize;
	cin >> QAsize;

	int digit = QAsize;
	int QADigit = 0;
	while (digit)
	{
		digit /= 10;
		QADigit++;
	}
	

	_mkdir("in");
	_mkdir("out");

	for(int i = 0; i < QAsize; i++)
	{
		string question;
		stack<long double> calcData;

		while (1)
		{
			if(calcData.size() >= 2 && getRandRange(1, 3) != 1)
			{
				double a, b;
				b = calcData.top();
				calcData.pop();
				a = calcData.top();
				calcData.pop();

				int op = getRandRange(1, 2);
				question += getOp(op);
				question += ' ';

				calcData.push(calc(a, b, op));
			}
			else calculator(question, calcData);

			if(calcData.size() == 1 && getRandRange(1, 2) == 1) break;
		}

		string fileName = to_string(i + 1);
		fileName = string(max(0, QADigit - (int)fileName.size()), '0') + fileName;

		ofstream qFile;
		qFile.open("./in/" + fileName + "q.txt");
		qFile << setprecision(20);
		qFile << question << endl;
		qFile.close();

		ofstream aFile;
		aFile.open("./out/" + fileName + "a.txt");
		aFile << setprecision(20);
		aFile << calcData.top() << endl;
		aFile.close();
	}

	return 0;
}