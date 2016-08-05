#include "Longdigit.h"


Longdigit::Longdigit()
{

}

Longdigit::Longdigit(string val)
{
	number = val;
}

Longdigit::~Longdigit()
{
	number.clear();
}

Longdigit::Longdigit(const Longdigit& val)
{
	number = val.getNumber();
}




int Longdigit::getLen() const
{
	return number.length();
}

string Longdigit::getPart(int first, int last)
{
	string tmp;
	for (int i = first; i < last + 1; i++)
		tmp.push_back(number[i]);

	return tmp;


}

int Longdigit::toInt() const
{
	if (this->number.length() < 10)
	{
		return atoi(number.c_str());
	}
}

int Longdigit::getDigitAtPos(int pos) const
{
	return charToint(number[pos]);
}

void Longdigit::setDigitAtPos(int pos, int val)
{
	number[pos] = intTochar(val);
}

void Longdigit::multByPowTen(int pow)
{
	for (int i = 0; i < pow; i++)
		number.append("0");
}

void Longdigit::show()
{
	for (int i = 0; i < number.size(); i++)
		cout << number[i];

	cout << endl;
}

void Longdigit::readRromFile(string filename)
{
	ifstream is(filename);

	if (!is.bad())
		is >> number;
}

void Longdigit::writeToFile(string filename)
{
	ofstream os(filename);

	if (!os.bad())
		os << number;
}

void Longdigit::pushFront(char* val)
{
	number.insert(0, val);
}

void Longdigit::normalize()
{
	int i = 0;

	while (number[i++] == '0')
		number.erase(--i, 1);
}





Longdigit& Longdigit::operator = (int val)
{
	char buf[128];

	_itoa_s(val, buf, 128, 10);
	this->number = buf;
	return *this;
}

Longdigit& Longdigit::operator = (Longdigit& val)
{
	number = val.getNumber();
	return *this;
}

Longdigit& Longdigit::operator = (string val)
{
	number = val;
	return *this;
}

Longdigit Longdigit::operator + (Longdigit val)
{
	string tmp;
	int i, j, k, sum;

	//if (number == "0" && val.getNumber() == "0")
	//{
	//	tmp = "0"; 
	//	return tmp;
	//}

	i = this->getLen();
	j = val.getLen();

	if (this->getLen() > val.getLen())
		tmp = number;
	else
		tmp = val.getNumber();

	k = tmp.size();

	i--;k--;j--;

	vector<int> transfer(tmp.size());
	for (int i = 0; i < transfer.size(); i++)
		transfer[i] = 0;

	do
	{
		if (i > -1 && j > -1)
			sum = this->getDigitAtPos(i--) + val.getDigitAtPos(j--);
		else if (i == -1)
			sum = val.getDigitAtPos(j--);
		else
			sum = this->getDigitAtPos(i--);

		if (transfer[k])
			sum++;

		if (sum < 10)
		{
			tmp[k--] = intTochar(sum);
		}
		else
		{
			if (k == 0)
			{
				tmp[k--] = intTochar(sum - 10);
				tmp.insert(0, "1");
			}
			else
			{
				tmp[k--] = intTochar(sum - 10);
				transfer[k] = 1;
			}
		}
	} 
	while (k > -1);
	

	return Longdigit(tmp);
		
}

Longdigit Longdigit::operator - (Longdigit val)
{
	string tmp;
	int i, j, k, sum;
	i = this->getLen();
	j = val.getLen();

	if (this->getLen() > val.getLen())
		tmp = number;
	else
		tmp = val.getNumber();

	k = tmp.size();

	i--; k--; j--;

	vector<int> transfer(tmp.size());
	for (int i = 0; i < transfer.size(); i++)
		transfer[i] = 0;

	do
	{
		if (i > -1 && j > -1)
			sum = this->getDigitAtPos(i--) - val.getDigitAtPos(j--);
		else if (i == -1)
			sum = val.getDigitAtPos(j--);
		else
			sum = this->getDigitAtPos(i--);

		if (transfer[k])
			sum--;

		if (sum > -1)
		{
			tmp[k--] = intTochar(sum);
		}
		else
		{

				tmp[k--] = intTochar(sum + 10);
				transfer[k] = 1;
			
		}
	} while (k > -1);


	return Longdigit(tmp);
}

Longdigit Longdigit::operator * (Longdigit val)
{
	return Karacuba(*this, val);
}


Longdigit Longdigit::Karacuba(Longdigit x, Longdigit y)
{
	Longdigit a, b, c, d, ac, bd, adbc, xy, temp;
	int K1, K2;//power of 10 near ac and (ad + bc)
	int len, power = 1;
	//int count1, count2, count3;
	//count1 = count2 = count3 = 0;

	if (x.getLen() != y.getLen() || x.getLen() % 2 != 0 || y.getLen() % 2 != 0)
	{
		len = max(x.getLen(), y.getLen());

			while (power < len)
				power *= 2;

			len = x.getLen();

			for (int i = 0; i < power - len; i++)
				x.pushFront("0");

			len = y.getLen();

			for (int i = 0; i < power - len; i++)
				y.pushFront("0");
	}


	if (x.getLen() == 1 && y.getLen() == 1)
	{
		temp = x.toInt() * y.toInt();
		return temp;
	}
	else
	{
			a = x.getPart(0, x.getLen() / 2 - 1);
			b = x.getPart(x.getLen() / 2, x.getLen() - 1);
			K1 = x.getLen();
			K2 = x.getLen() / 2;
			c = y.getPart(0, y.getLen() / 2 - 1);
			d = y.getPart(y.getLen() / 2, y.getLen() - 1);
	}

	ac = a * c;
	bd = b * d;
	adbc = (a + b) * (c + d) - ac - bd;

	adbc.normalize();

	ac.multByPowTen(K1);
	adbc.multByPowTen(K2);

	xy = ac + adbc + bd;

	return xy;
}