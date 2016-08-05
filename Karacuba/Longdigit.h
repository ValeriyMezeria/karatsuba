#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <istream>

using namespace std;

class Longdigit
{
private:
	string number;

	Longdigit Karacuba(Longdigit, Longdigit);

	int charToint(char val) const { return val - 48; };

	char intTochar(int val) const { return val + 48; };

	int max(int a, int b){ return a > b ? a : b; };
	

public:
	
	Longdigit();

	Longdigit(string);

	Longdigit(const Longdigit&);

	~Longdigit();




	int getLen() const;

	int getDigitAtPos(int) const;

	void setDigitAtPos(int, int);

	int toInt() const;

	string getNumber() const { return number; };

	string getPart(int, int);

	void multByPowTen(int);

	void show();

	void readRromFile(string);

	void writeToFile(string);

	void pushFront(char*);

	void normalize();



	Longdigit& operator = (int);

	Longdigit& operator = (Longdigit&);

	Longdigit& operator = (string);

	//Longdigit& operator [] (int);

	Longdigit operator + (Longdigit);

	Longdigit operator - (Longdigit);

	Longdigit operator * (Longdigit);


};