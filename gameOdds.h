#include <string>
#include <iostream>


//creating a record to input data from "covers.com/liveodds mlb <-- get 
//


using namespace std;

class gameOdds{
	string HomeTeam;
	string AwayTeam;
	float overUnder;
	int moneyLine;
	

public:
	gameOdds();
	void setHomeTeam(string x);
	void setAwayTeam(string x);
	void setOverUnder(float x);
	void setMoneyLine(int x);
	string getHomeTeam();
	string getAwayTeam();
	float getOverUnder();
	int getMoneyLine();
	
};