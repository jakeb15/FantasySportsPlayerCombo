#include <string>
#include <iostream>

using namespace std;

class PlayerInfo{
	string Name;
	int Salary;
	string Pos;
	float AveragePts;
	string matchUP;
	string Trigger;
	string teamTrigger;
	string team1;
	string team2;
	string HAgames;
	string prevGameData;
	string BvPinfo;
	int atBats;
	

public:
	PlayerInfo();
	void setTrigger(string Trigger, string teamTrigger);
	void setTeam1(string teamOne);
	void setTeam2(string teamTwo);
	string getTeam1();
	string getTeam2();
	string getTrigger();
	string getTeamTrigger();
	void setName(string name);
	void setSalary(int salary);
	void setPos(string pos);
	void setMatchUP(string data);
	void setAVGPTS(float avgPTS);
	string getName();
	int getSalary();
	string getPos();
	float getAVGPTS();
	string getMatchUP();
	void setprevGameData(string s);
	string getprevGameData();
	string getBvPinfo();
	void setBvPinfo(string x);
	void setAtBats(int x);
	int getAtBats();
	
	bool sortBySalary(const PlayerInfo &lhs, const PlayerInfo &rhs){ return lhs.Salary < rhs.Salary;}

	bool sortByPos(const PlayerInfo &lhs, const PlayerInfo &rhs){ return lhs.Pos < rhs.Pos;}
	
	// use to sort by salary - Not sure how this is working need to learn more
	struct compareMyDataFunctor : public binary_function<PlayerInfo, PlayerInfo, bool>{
		 bool operator()( PlayerInfo lhs, PlayerInfo rhs){
			 return (lhs.Salary > rhs.Salary);
		 }
	 };
	 
	struct comparePOS : public binary_function<PlayerInfo, PlayerInfo, bool>{
		 bool operator()( PlayerInfo lhs, PlayerInfo rhs){
			 return (lhs.Pos > rhs.Pos);
		 }
	 };
};
