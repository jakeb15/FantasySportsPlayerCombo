#include <string>
#include <iostream>


//creating a record to input data from "http://rotoguru1.com/cgi-bin/byday.pl?date=405&game=dk"
//


using namespace std;

class mlbPlayer{
	string Date;
	int GID;
	int MLB_ID;
	string Name;
	string LastName;
	int Starter;
	int Batorder;
	string DKposn;
	float DKpts;
	int DKsal;
	string Team;
	string Oppt;
	int dblhdr;
	int TmRuns;
	int OppRuns;
	string Statline;
	string BvP;
	string shortBvP;
	int atBats;
	float ProjectionScore;
	int Hits;
	int base2;
	int base3;
	int HomeRuns;
	int RBI;
	int BB;
	int SO;
	int SB;
	int CS;
	float AVG;
	float OBP;
	float SLG;
	float OPS;
	float wOBA;
	string batLHS;
	string homeaway;
	string pitcherHand;
	int game1Pts;
	int game2Pts;
	int game3Pts;
	int game4Pts;
	int FinalPts;
	string debug;
	float seasonAVG;
	float seasonOPS;
	float seasonOBP;
	float seasonWOBA;
	int seasonSB;
	int seasonCS;
	int seasonGames;
	int seasonHomeRuns;
	float HRrFlyballs;
	string startingPitcher;
	float strikeOutPerecent;
	float walkPercent;
	float wSB;
	float wRC;
	float wRAA;
	float gbPercent;
	float fbPercent;
	float BBpK; // BB/K rate
	int age;
	float RE24;
	int rSB;
	float fastball_percent;
	float curveball_percent;
	float slider_percent;
	float ChangeUp_percent;
	float ct_percent;
	float sf_percent;
	float Knuckle_percent;

	int SB_Projection;


public:
	mlbPlayer();
	void setDate(string d);
	string getDate();
	void setGID(int gID);
	int getGID();
	void setMLB_ID(int id);
	int getMLB_ID();
	void setName(string name);
	void setLastName(string name);
	string getLastName();
	string getName();
	void setStarter(bool x);
	bool isStarter();
	void setBatOrder(int x);
	int getBatOrder();
	void setDkPosn(string x);
	string getDkPosn();
	void setDkpts(float x);
	float getDkpts();
	void setDKsal(int x);
	int getDKsal();
	void setTeam(string x);
	string getTeam();
	void setOppt(string x);
	string getOppt();
	void doubleHeader(bool x);
	bool isDoubleHeader();
	void setTeamRuns(int x);
	int getTeamRuns();
	void setOpptRuns(int x);
	int getOpptRuns();
	void setStatLine(string x);
	string getStateLine();
	string getBvP();
	void setBvP(string x);
	string getShortBvP();
	void setShortBvP(string x);
	void setAtBats(int x);
	int getAtBats();
	float getProjectionScore();
	void setProjectionScore(float x);
	void setHits(int x);
	int getHits();
	void setDoubles(int x);
	int getDoubles();
	void setTriples(int x);
	int getTriples();
	void setHomeRuns(int x);
	int getHomeRuns();
	void setRBI(int x);
	int getRBI();
	void setBB(int x);
	int getBB();
	void setSO(int x);
	int getSO();
	void setSB(int x);
	int getSB();
	void setCS(int x);
	int getCS();
	void setAVG(float x);
	float getAVG();
	void setOBP(float x);
	float getOBP();
	void setSLG(float x);
	float getSLG();
	void setOPS(float x);
	float getOPS();
	void setHomeAway(string x);
	string getHomeAway();
	void setBatLRS(string x);
	string getBatLRS();
	void setPitcherHand(string x);
	string getPitcherHand();
	void setGame1Pts(int x);
	int getGame1Pts();
	void setGame2Pts(int x);
	int getGame2Pts();
	void setGame3Pts(int x);
	int getGame3Pts();
	void setGame4Pts(int x);
	int getGame4Pts();
	string getDebug();
	void setDebug(string x);
	//added
	void setSeasonWOBA(float x);
	float getSeasonWOBA();
	void setSeasonAVG(float x);
	float getSeasonAVG();
	void setSeasonOBP(float x);
	float getSeasonOBP();
	void setSeasonOPS(float x);
	float getSeasonOPS();
	void setSeasonSB(int x);
	void setSeasonCS(int x);
	int getSeasonSB();
	int getSeasonCS();
	void setSeasonGames(int x);
	int getSeasonGames();
	//final to see how it did
	int getFinalPts();
	void setFinalPts(int x);
	//added 5.15.2015
	int getSeasonHR();
	void setSeasonHR(int x);
	float getSeasonHRrFlyball();
	void setSeasonHRrFlyball(float x);
	void setStartingPitcher(string x);
	string getStartingPitcher();
	float getWalkPercent();
	void setWalkPercent(float x);
	float getStrikeOutPerecent();
	void setStrikeOutPercent(float x);
	void set_wRC(float x);
	float get_wRC();
	void set_wRAA(float x);
	float get_wRAA();
	void set_wSB(float x);
	float get_wSB();
	void set_gbPercent(float x);
	float get_gbPercent();
	void set_fbPercent(float x);
	float get_fbPercent();
	float get_BBpK();
	void set_BBpK(float x);
	void setAGE(int x);
	int getAGE();
	float getRE24();
	void setRE24(float x);
	void set_rSB(int x);
	int get_rSB();

	float get_fastball_percent();
	float get_changeup_percent();
	float get_curveball_percent();
	float get_Knuckleball_percent();
	float get_ct_percent();
	float get_SplitFinger_percent();
	float get_slider_percent();

	void set_fastball_percent(float x);
	void set_changeup_percent(float x);
	void set_curveball_percent(float x);
	void set_Knuckleball_percent(float x);
	void set_ct_percent(float x);
	void set_SplitFinger_percent(float x);
	void set_slider_percent(float x);

	void set_SB_Projection(int x);
	int get_SB_Projection();

	

bool sortByProjection(const mlbPlayer &lhs, const mlbPlayer &rhs){ return lhs.ProjectionScore < rhs.ProjectionScore;}
bool sortByPosition(const mlbPlayer &lhs, const mlbPlayer &rhs){ return lhs.DKposn < rhs.DKposn;}

// use to sort by salary - Not sure how this is working need to learn more
struct compareMyDataFunctor : public binary_function<mlbPlayer, mlbPlayer, bool>{
		 bool operator()( mlbPlayer lhs, mlbPlayer rhs){
			 return (lhs.ProjectionScore > rhs.ProjectionScore);
		 }
	 };



struct SortPosition : public binary_function<mlbPlayer, mlbPlayer, bool>{
		 bool operator()( mlbPlayer lhs, mlbPlayer rhs){
			 return (lhs.DKposn > rhs.DKposn);
		 }
	 };



struct SortTeam : public binary_function<mlbPlayer, mlbPlayer, bool>{
		 bool operator()( mlbPlayer lhs, mlbPlayer rhs){
			 return (lhs.Team > rhs.Team);
		 }
	 };

};