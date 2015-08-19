/*/ uses link//http://www.fangraphs.com/leaders.aspx?pos=c&stats=fld&lg=all&qual=10&type=c,4,5,6,17,18&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0
*/
#include <string>
#include <iostream>

//Uses 2 files that is stats from 2014 showing ball park factors
//


using namespace std;

class Catcher{
	string name;
	string team;
	int gamesPlayed;
	int gamesStarted;
	float Tot_innings;
	int stolenBases;
	int caughtStealing;
	int rSB;


public:
	Catcher();
	void setName(string x);
	void setTeam(string x);
	void setGamesPlayed(int x);
	void setGameStarted(int x);
	void setTotInnings(float x);
	void setStolenBases(int x);
	void setCaughtStealing(int x);
	string getName();
	string getTeam();
	int getGamesPlayed();
	int getGamesStarted();
	float getTotInnings();
	int getStolenbases();
	int getCaughtStealing();
	int get_rSB();
	void set_rSB(int x);
};
