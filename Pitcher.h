#include <string>
#include <iostream>



//http://www.fangraphs.com/leaders.aspx?pos=all&stats=pit&lg=all&qual=y&type=8&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0
//


using namespace std;

class Pitcher{
	string name;
	string team;
	int gamesPlayed;
	int gamesStarted;
	int wins;
	int loses;
	int saves;
	float Tot_innings;
	float Kper9;
	float BBper9;
	float HRper9;
	float BABIP;
	float LOB;
	float GB;
	float HRFB;
	float ERA;
	float FIP;
	float XFIP;
	float WAR;
	int projection;
	int Kprojection;
	float gbPercent;
	float fbPercent;
	string PitchingHand;
	string Opponent;
	int rSB;
	int Catcher_rSB;

	int OBP_Projection;
	int OPS_Projections;
	int WOBA_Projection;

	float KpBB;

	float fastball_percent;
	float curveball_percent;
	float slider_percent;
	float ChangeUp_percent;
	float ct_percent;
	float sf_percent;
	float Knuckle_percent;

	
public:
	Pitcher();
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
	void setWins(float x);
	void setLoses(float x);
	void setSaves(float x);
	void setKper9(float x);
	void setBBper9(float x);
	void setHRper9(float x);
	void setBABIP(float x);
	void setLOBpercent(float x);
	void setGBpercent(float x);
	void setHRlFB(float x);
	void setERA(float x);
	void setFIP(float x);
	void setXFIP(float x);
	void setWAR(float x);
	float getWins();
	float getLoses();
	float getSaves();
	float getKper9();
	float getBBper9();
	float getHRper9();
	float getBABIP();
	float getLOBpercent();
	float getGBpercent();
	float getHRlFB();
	float getERA();
	float getFIP();
	float getXFIP();
	float getWAR();
	int getProjection();
	int getKprojection();
	void setProjection(int x);
	void setKprojection(int x);
	
	void set_OBP_Projection(int x);
	void set_OPS_Projection(int x);
	void set_WOBA_Projection(int x);
	int get_OBP_Projection();
	int get_OPS_Projection();
	int get_WOBA_Projection();

	void set_gbPercent(float x);
	float get_gbPercent();
	void set_fbPercent(float x);
	float get_fbPercent();

	void setPitchingHand(string x);
	string getPitchingHand();
	void set_KpBB(float x);
	float get_KpBB();

	void setOpponent(string x);
	string getOpponent();

	int get_rSB();
	void set_rSB(int x);

	int get_Catcher_rSB();
	void set_Catcher_rSB(int x);

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


};
