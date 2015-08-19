#include <string>
#include <iostream>

//Uses 2 files that is stats from 2014 showing ball park factors
//


using namespace std;

class BallPark{
	int year;
	string team;
	int base1L;
	int base1R;
	int base2L;
	int base2R;
	int base3L;
	int base3R;
	int HRL;
	int HRR;
	
	

public:
	BallPark();
	int getYear();
	string getTeam();
	int getBase1L();
	int getBase1R();
	int getBase2L();
	int getBase2R();
	int getBase3L();
	int getBase3R();
	int getHRL();
	int getHRR();
	void setYear(int x);
	void setTeam(string x);
	void setBase1L(int x);
	void setBase1R(int x);
	void setBase2L(int x);
	void setBase2R(int x);
	void setBase3L(int x);
	void setBase3R(int x);
	void setHRL(int x);
	void setHRR(int x);
};
