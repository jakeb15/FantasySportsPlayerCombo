#include "stdafx.h"
#include "mlbFunctions.h"
#include <sstream>
#include <Windows.h>

using namespace std;

string PITCHERFILE = "Pitcher628"; //http://www.fangraphs.com/leaders.aspx?pos=all&stats=pit&lg=all&qual=0&type=c,4,5,11,7,8,13,-1,36,37,40,43,44,48,51,-1,6,45,62,-1,59,48,49,38&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0&sort=8,d
string ROSTERFILE = "PlayersX717"; //http://www.fangraphs.com/leaders.aspx?pos=all&stats=bat&lg=all&qual=10&type=c,4,50,23,37,39,21,22,11,47,35,34,200,52,51,44,45,36&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0
// new roster RE24 added to end http:www.fangraphs.com/leaders.aspx?pos=all&stats=bat&lg=all&qual=10&type=c,4,50,23,37,39,21,22,11,47,35,34,200,52,51,44,45,36,65&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0
string BATTERvsPITCHER = "game818"; //
string CATCHERFILE = "catcher724"; // http://www.fangraphs.com/leaders.aspx?pos=c&stats=fld&lg=all&qual=10&type=c,4,5,6,17,18,23&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0&sort=8,a
string isStartingFile = "Starting818"; // https://twitter.com/mlblineups
string BatterHands2015 = "BatterHand2015"; // located in "C:\\progData\\mlbFactors\\"
string FIXTEAMS = "BatterTeams810"; // since using data form multiple years in the above roster and pitcher files, thier current team may not be there so we must get a updated file and attach the team to player
string PITCHERFIXTEAMS = "PitcherTEAMFIX810"; // use same strategy as BatterTeams - fixes team
string PitcherDefenseFanGRAPHS = "PitcherDefense724"; // http://www.fangraphs.com/leaders.aspx?pos=p&stats=fld&lg=all&qual=y&type=c,6,-1,23,17,19&season=2015&month=0&season1=2013&ind=0&team=0&rost=0&age=0&filter=&players=0
string Pitcher_PitchType = "Pitcher_This_Year_PitchType";
string Batter_PitchType = "BatterPitchType"; //using data from 2013-present

// pitcher defense is 3 year data on rSB and stolen bases on a pitcher combine with catcher data to determin sb picks

//Items to get BvP <----http://dailybaseballdata.com/cgi-bin/dailyhit.pl
//  Last 4 daily score <------http://rotoguru1.com/cgi-bin/byday.pl?game=dk
// Park Factors <-----Saved to c: Historicdata
//

// Things to add.... Batting order <-- attach to mlbPlayer <- is in dailygames
// 

vector<mlbPlayer> parseData(int dateXXXX){

	
	vector<mlbPlayer> DraftKingsPlayers;
	string dayResults = "C:\\progData\\MLBDailyScores\\";
	dayResults = dayResults + std::to_string(dateXXXX);
	ifstream myFile(dayResults);
	string templine ="";
	int pos = 0;
	int namePos = 0;
	int gameID = 0;
	int MLB_ID = 0;
	string lastName = "";
	string firstName = "";
	string temp = "";
	


	while(getline(myFile,templine)){
		if(templine[0]=='2'){// skips first line all lines start with 2015 or the year so 2 should work for very long time
			mlbPlayer* tempMLBplayer = new mlbPlayer();
			for(int x =0; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets the Date ex: 20150407
			tempMLBplayer->setDate(temp);
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets GameID

			tempMLBplayer->setGID(atoi(temp.c_str()));
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets MLB_ID
			tempMLBplayer->setMLB_ID(atoi(temp.c_str()));
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets Name
			//////need to reverse name here so i can compare to my imports easier///

			for(int x =0; x<temp.length(); x++){
				if(temp[x]!=','){
					lastName = lastName + temp[x];
				}
				else{
					namePos = x;
					x = x + temp.length();
				}
			}

			for(int x = namePos+2; x < temp.length();x++){
				firstName = firstName + temp[x];
			}

			temp = "";
			temp = firstName + " " + lastName;
			tempMLBplayer->setName(temp);
			temp = "";
			firstName = "";
			lastName ="";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets Starter
			//tempMLBplayer->setStarter(atoi(temp.c_str())); REMOVED Will Set Starter from TWitter File Parse
			temp = "";


			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets Batting order
			tempMLBplayer->setBatOrder(atoi(temp.c_str()));
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets DK posn
			tempMLBplayer->setDkPosn(temp.c_str());
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets DKpts
			
			tempMLBplayer->setDkpts(atof(temp.c_str()));
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets DK salary
			tempMLBplayer->setDKsal(atoi(temp.c_str()));
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets Team
			tempMLBplayer->setTeam(temp);
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets Opponent
			tempMLBplayer->setOppt(temp);
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets doubleHeader 0/1 true/false
			tempMLBplayer->doubleHeader(atoi(temp.c_str()));
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets Team Runs
			tempMLBplayer->setTeamRuns(atoi(temp.c_str()));
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets Opponent Runs
			tempMLBplayer->setOpptRuns(atoi(temp.c_str()));
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=';'){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//gets Stat Line
			tempMLBplayer->setStatLine(temp);
			temp = "";
			DraftKingsPlayers.push_back(*tempMLBplayer);
		}
	}

	return DraftKingsPlayers;
}


//	Name	Team	G	wOBA	AVG	OBP	OPS	SB	CS  ::::: uses LINK for UPDATING http://www.fangraphs.com/leaders.aspx?pos=all&stats=bat&lg=all&qual=y&type=c,4,50,23,37,39,21,22&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0&page=1_50

// new link added Home runs and HR/ flyball ration http://www.fangraphs.com/leaders.aspx?pos=all&stats=bat&lg=all&qual=10&type=c,4,50,23,37,39,21,22,11,47,35,34,200,52,51&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0
vector<mlbPlayer> MLBPlayerRoster(){
	vector<mlbPlayer> MLBRoster;
	string BvPFile = "C:\\progData\\mlbFactors\\";
	BvPFile = BvPFile + ROSTERFILE; ///Players520"; // replace spaces with a + and remove the %
	cout << BvPFile <<endl;
	ifstream myFile(BvPFile);
	string templine ="";
	string temp = "";
	int pos = 0;
	bool lastNameSpace = false;
	string lastName = "";

	while(getline(myFile,templine)){
		mlbPlayer* newPlayer = new mlbPlayer();
		for(int x = 0; x< templine.length(); x++){
			if(templine[x]!='+'){
				if(lastNameSpace == true){
					lastName = lastName + templine[x];
				}
				if(templine[x]==' '){
					lastNameSpace = true;
				}
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//gets name
		newPlayer->setLastName(lastName);
		newPlayer->setName(temp);
		//cout << temp << " ";
		temp = "";
		lastName = "";
		lastNameSpace = false;
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets team
		
		newPlayer->setTeam(changeTeam(temp));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets games
		newPlayer->setSeasonGames(atoi(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets woba
		newPlayer->setSeasonWOBA(atof(temp.c_str()));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets AVG
		newPlayer->setSeasonAVG(atof(temp.c_str()));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets OBP
		newPlayer->setSeasonOBP(atof(temp.c_str()));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets OPS
		newPlayer->setSeasonOPS(atof(temp.c_str()));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// SB
		newPlayer->setSeasonSB(atoi(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// getsCS
		newPlayer->setSeasonCS(atoi(temp.c_str()));
		//cout << temp << endl;
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// Home Runs
		newPlayer->setSeasonHR(atoi(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// HR/Flyball ratio
		newPlayer->setSeasonHRrFlyball(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// StrikeOutPercent
		newPlayer->setStrikeOutPercent(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// Walk Percent
		newPlayer->setWalkPercent(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// wSB -- Waited stolen Base Runs 0- average +6 excellent -6 poor
		newPlayer->set_wSB(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// wRC -- Waited runs created
		newPlayer->set_wRC(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// wRAA -- Waited Runs Above Average
		newPlayer->set_wRAA(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gb% -- groundball percent
		newPlayer->set_gbPercent(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// fb% -- flyball%
		newPlayer->set_fbPercent(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// BB/K
		newPlayer->set_BBpK(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// age
		newPlayer->setAGE(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// RE24
		newPlayer->setRE24(atof(temp.c_str()));
		temp = "";

		MLBRoster.push_back(*newPlayer);
	}

	return MLBRoster;
}

//
vector<mlbPlayer> BvPParse(){
	vector<mlbPlayer> DraftKingsPlayers;
	string BvPFile = "C:\\progData\\MLBBvP\\";
	BvPFile = BvPFile + BATTERvsPITCHER;
	ifstream myFile(BvPFile);
	string templine ="";
	int pos = 0;
	int namePos = 0;
	int gameID = 0;
	int MLB_ID = 0;
	int ESPN_ID =0;
	string OppPitcher = "";
	string Last2Firstname = "";
	string first2Lastname ="";
	string team;
	int AB = 0;
	int Hits = 0;
	int base2 = 0;
	int base3 = 0;
	int HomeRuns = 0;
	int RBI = 0;
	int BB = 0;
	int SO = 0;
	int SB = 0;
	int CS = 0;
	float AVG = 0;
	float OBP = 0;
	float SLG = 0;
	float OPS = 0;
	string PitcherName = "";
	string BvPline = "";
	string BvPshort = "";
	std::stringstream ss;
	std::stringstream tt;




	string temp = "";
	
	while(getline(myFile,templine)){
		if(templine[0]!='M'){// skips first line all lines start with 2015 or the year so 2 should work for very long time
			mlbPlayer* tempMLBplayer = new mlbPlayer();
			for(int x =0; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets MLB_ID
			MLB_ID = atoi(temp.c_str());
			temp = "";

			
			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets ESPN_ID
			ESPN_ID = atoi(temp.c_str());
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets Last name, first name
			Last2Firstname = temp;
			temp ="";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets FirstName first
			Last2Firstname = temp;
			temp ="";


			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets First name Last name
			first2Lastname = temp;
			temp = "";
			first2Lastname.erase(0,1);
			first2Lastname.erase(first2Lastname.length()-1,first2Lastname.length());
			//cout << first2Lastname <<endl;
			tempMLBplayer->setName(first2Lastname);

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets team
			team = temp;
			tempMLBplayer->setTeam(changeTeam(team));
			temp = "";

	
			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}// homeAway
			tempMLBplayer->setHomeAway(temp);
			temp = "";


			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//batts l/r/s
			tempMLBplayer->setBatLRS(temp);
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Active 
			temp = "";


			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//FD position
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets Draftkings position
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets DD position
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets SF Position
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets FD salary
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets Draftkings salary
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets Draftday salary
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets SF salary
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//NP
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Plate Appearances
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets At Bats
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets Hits
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets Doubles
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets Triples
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets HomeRuns
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets RUNS
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets RBIs
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets Walks
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets IBB
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets SO
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets HBP
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets SB
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets CS
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets AVG
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets OBP
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets SLG
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets OPS
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets WOBA
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets MLB_ID(Pitcher)
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets ESPN ID (PITCHER)
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets Last name, first name
			temp ="";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Sets FirstName first
			temp ="";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]=='"'){
				}
				else if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Pitcher Name

			PitcherName = temp;
			tempMLBplayer->setStartingPitcher(PitcherName);
			temp ="";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//Oppteam

			tempMLBplayer->setOppt(changeTeam(temp));
			temp = "";

			for(int x=pos; x<templine.length();x++){
				if(templine[x]!=','){
					temp = temp + templine[x];
				}
				else{
					pos = x + 1;
					x = x + templine.length();
				}
			}//PitcherHand
			tempMLBplayer->setPitcherHand(temp);
			temp = "";

			///
			
			///creat BvP line and attach
			
			ss << " H: " << Hits << " 2B: " << base2 << " 3B: " << base3 << " HR: " << HomeRuns << " RBI: " << RBI << " BB: " << BB
				<< " SO: " << SO << " SB: " << SB << " CS: " << CS << " AVG: " << AVG <<  " OBP: " << OBP << " SLG: " << SLG << " OPS: " << OPS 
				<< " " << PitcherName.c_str();
			BvPline = ss.str();

			// short version of BvP.//

			tt << " H: " << Hits << " AVG: " << AVG << " HR: " << HomeRuns << " " << PitcherName.c_str();
			BvPshort = tt.str();

			tempMLBplayer->setShortBvP(BvPshort);
			tempMLBplayer->setBvP(BvPline);
			//cout << BvPshort <<endl;
			BvPline = "";
			BvPshort ="";

			tt.str("");
			ss.str("");

			DraftKingsPlayers.push_back(*tempMLBplayer);
		}


	}

return DraftKingsPlayers;
}

vector<BallPark> BallParkParse(){
	vector<BallPark> BallParks;
	string fileLoc = "C:\\progData\\MLBhistoricStats\\";
	string ParkFile = fileLoc  + "HandednessParkFactors";
	ifstream myFile(ParkFile);
	string templine = "";
	int pos = 0;
	string temp = "";

	while(getline(myFile,templine)){
		BallPark* tempBallPark = new BallPark();
		for(int x=0; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x]!= ' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		} // gets year
		tempBallPark->setYear(atoi(temp.c_str()));
		temp = "";

		for(int x=pos; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x] !=' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		} // gets Team
		tempBallPark->setTeam(changeTeam(temp));
		temp = "";
		
		for(int x=pos; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x] !=' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets base1L
		tempBallPark->setBase1L(atoi(temp.c_str()));
		temp = "";

		for(int x=pos; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x] !=' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets base1R
		tempBallPark->setBase1R(atoi(temp.c_str()));
		temp = "";

		for(int x=pos; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x] !=' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets base2L
		tempBallPark->setBase2L(atoi(temp.c_str()));
		temp = "";

		for(int x=pos; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x] !=' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets base2R
		tempBallPark->setBase2R(atoi(temp.c_str()));
		temp = "";

		for(int x=pos; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x] !=' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets base3L
		tempBallPark->setBase3L(atoi(temp.c_str()));
		temp = "";

		for(int x=pos; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x] !=' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets base3R
		tempBallPark->setBase3R(atoi(temp.c_str()));
		temp = "";

		for(int x=pos; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x] !=' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets HRL
		tempBallPark->setHRL(atoi(temp.c_str()));
		temp = "";

		for(int x=pos; x<templine.length();x++){
			if(templine[x]!= '\t' && templine[x] !=' '){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets HRR
		tempBallPark->setHRR(atoi(temp.c_str()));
		temp = "";
		

		BallParks.push_back(*tempBallPark);
	}
	return BallParks;
}


vector<gameOdds> LoadGameOdds(){
	vector<gameOdds> games;
	// make sure odds file is up to date.....
	string fileLocation = "C:\\progData\\odds";
	ifstream myFile(fileLocation);
	string templine ="";
	string temp;
	string home = "";
	string away = "";
	float overUnder = 0;
	int moneyLine = 0;
	int pos = 0;

	while(getline(myFile,templine)){
		if(templine.length()>2){ //lazy....
			gameOdds* tempGameOdds = new gameOdds();
			if(templine[0]!='@'){
				for(int x=0; x< templine.length(); x++){
					if(templine[x]!='/n'){
						temp = temp + templine[x];
					}
					else{
						x = x+templine.length();
						
					}
				}
				temp = trim(temp);
				home = temp;
				tempGameOdds->setAwayTeam(changeTeam(home));
				//cout << home << " ";
				temp = "";
				getline(myFile,templine);
			}

			if(templine[0]=='@'){
				for(int x = 1; x< templine.length();x++){
					if(templine[x]!='-' && isdigit(templine[x])==0){
						temp = temp + templine[x];
					}
					else{
						pos = x;
						x = x+templine.length();
					}
				}// get away team
				temp = trim(temp);
				away = temp;
				tempGameOdds->setHomeTeam(changeTeam(away));
				//cout << away << " ";
				temp = "";

				for(int x = pos; x < templine.length(); x++){
					if(templine[x]!=' '){
						temp = temp + templine[x];
					}
					else{
						pos = x;
						x = x+templine.length();
					}
				}// get overUnder
				temp = trim(temp);
				overUnder = atof(temp.c_str());
				tempGameOdds->setOverUnder(overUnder);
				//cout << "*" << temp << "*";
				temp = "";

				for(int x = pos; x < templine.length(); x++){
					if(templine[x]!='|'){
						temp = temp + templine[x];
					}
					else{
						pos = x;
						x = x+templine.length();
					}
				}// get moneyLine
				temp = trim(temp);
				moneyLine = atoi(temp.c_str());
				tempGameOdds->setMoneyLine(moneyLine);
				//cout << "*" << temp << "*";
				//cout << endl;
				temp = "";
			}
			games.push_back(*tempGameOdds);
		}
		
	}

	myFile.close();
	return games;
}

////
////use file export from http://www.fangraphs.com/leaders.aspx?pos=c&stats=fld&lg=all&qual=10&type=c,4,5,6,17,18&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0
////
vector<Catcher> CatcherStats(){
	vector<Catcher> CatcherList;
	// make sure odds file is up to date.....
	string fileLocation = "C:\\progData\\mlbFactors\\";
	fileLocation = fileLocation + CATCHERFILE;
	cout << fileLocation << endl;
	ifstream myFile(fileLocation);
	string templine ="";
	string temp;
	int pos = 0;

	while(getline(myFile,templine)){
		Catcher* newCatcher = new Catcher();
		for(int x = 0; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//gets name
		newCatcher->setName(temp);
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets team
		newCatcher->setTeam(changeTeam(temp));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets games
		newCatcher->setGamesPlayed(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets games started
		newCatcher->setGameStarted(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets innings
		newCatcher->setTotInnings(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets stolen bases
		newCatcher->setStolenBases(atoi(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets caught stolen
		newCatcher->setCaughtStealing(atoi(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets rSB
		newCatcher->set_rSB(atoi(temp.c_str()));
		temp ="";
		
		CatcherList.push_back(*newCatcher);
	}
	return CatcherList;
}

vector<Pitcher> PitcherStats(){
	vector<Pitcher> PitcherList;
	// make sure odds file is up to date.....
	string fileLocation = "C:\\progData\\mlbFactors\\";
	fileLocation = fileLocation + PITCHERFILE;
	cout << fileLocation << endl;
	ifstream myFile(fileLocation);
	string templine ="";
	string temp;
	int pos = 0;

	while(getline(myFile,templine)){
		Pitcher* newPitcher = new Pitcher();
		for(int x = 0; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//gets name
		newPitcher->setName(temp);
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets team
		newPitcher->setTeam(changeTeam(temp));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets wins
		newPitcher->setWins(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets loses
		newPitcher->setLoses(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets saves
		newPitcher->setSaves(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets games
		newPitcher->setGamesPlayed(atoi(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets games started
		newPitcher->setGameStarted(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets Innings Pitched
		newPitcher->setTotInnings(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets K/9
		newPitcher->setKper9(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets BB/9
		newPitcher->setBBper9(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets HR/9
		newPitcher->setHRper9(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets BABIP
		newPitcher->setBABIP(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets LOB%
		newPitcher->setLOBpercent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets GB%
		newPitcher->setGBpercent(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets HR/FB
		newPitcher->setHRlFB(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets ERA
		newPitcher->setERA(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets FIP
		newPitcher->setFIP(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets XFIP
		newPitcher->setXFIP(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets WAR
		newPitcher->setWAR(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets gb%
		newPitcher->set_gbPercent(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets fb%
		newPitcher->set_fbPercent(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// sets KpBB
		newPitcher->set_KpBB(atof(temp.c_str()));
		temp ="";

		PitcherList.push_back(*newPitcher);
	}
	return PitcherList;
}



string changeTeam(string x){

	if(x.compare("Angels")==0 || x.compare("laa")==0 ||x.compare("LAA")==0 ||x.compare("LA Angels")==0){
		return "LAA";
	}
	else if(x.compare("Orioles")==0 || x.compare("bal")==0 ||x.compare("BAL")==0||x.compare("Baltimore")==0){
		return "BAL";	
	}
	else if(x.compare("RedSox")==0 || x.compare("bos")==0 ||x.compare("BOS")==0||x.compare("Boston")==0 || x.compare("Red Sox")==0){
		return "BOS";
	}
	else if(x.compare("WhiteSox")==0|| x.compare("chw")==0 ||x.compare("CHW")==0||x.compare("Chi. White Sox")==0||x.compare("White Sox")==0){
		return "CHW";
	}
	else if(x.compare("Indians")==0|| x.compare("cle")==0 ||x.compare("CLE")==0 ||x.compare("Cleveland")==0){
		return "CLE";
	}
	else if(x.compare("Tigers")==0|| x.compare("det")==0||x.compare("DET")==0||x.compare("Detroit")==0){
		return "DET";
	}
	else if(x.compare("Royals")==0|| x.compare("kan")==0||x.compare("KAN")==0||x.compare("kc")==0||x.compare("KC")==0||x.compare("Kansas City")==0||x.compare("KCR")==0){
		return "KAN";
	}
	else if(x.compare("Twins")==0|| x.compare("min")==0||x.compare("MIN")==0||x.compare("Minnesota")==0){
		return "MIN";
	}
	else if(x.compare("Yankees")==0|| x.compare("nyy")==0||x.compare("NYY")==0||x.compare("NY Yankees")==0){
		return "NYY";
	}
	else if(x.compare("Athletics")==0|| x.compare("oak")==0||x.compare("OAK")==0||x.compare("Oakland")==0){
		return "OAK";
	}
	else if(x.compare("Mariners")==0|| x.compare("sea")==0||x.compare("SEA")==0||x.compare("Seattle")==0){
		return "SEA";
	}
	else if(x.compare("Rays")==0|| x.compare("tam")==0||x.compare("TAM")==0||x.compare("tb")==0||x.compare("TB")==0||x.compare("Tampa Bay")==0||x.compare("TBR")==0){
		return "TAM";
	}
	else if(x.compare("Rangers")==0|| x.compare("tex")==0||x.compare("TEX")==0||x.compare("Texas")==0){
		return "TEX";
	}
	else if(x.compare("BlueJays")==0|| x.compare("tor")==0||x.compare("TOR")==0||x.compare("Toronto")==0||x.compare("Blue Jays")==0){
		return "TOR";
	}
	else if(x.compare("Diamondbacks")==0|| x.compare("ari")==0||x.compare("ARI")==0||x.compare("Arizona")==0 || x.compare("Dbacks")==0){
		return "ARI";
	}
	else if(x.compare("Braves")==0|| x.compare("atl")==0||x.compare("ATL")==0||x.compare("Atlanta")==0){
		return "ATL";
	}
	else if(x.compare("Cubs")==0|| x.compare("chc")==0||x.compare("CHC")==0||x.compare("Chi. Cubs")==0){
		return "CHC";
	}
	else if(x.compare("Reds")==0|| x.compare("cin")==0||x.compare("CIN")==0||x.compare("Cincinnati")==0){
		return "CIN";
	}
	else if(x.compare("Rockies")==0|| x.compare("col")==0||x.compare("COL")==0||x.compare("Colorado")==0){
		return "COL";
	}
	else if(x.compare("Marlins")==0|| x.compare("mia")==0||x.compare("MIA")==0||x.compare("Miami")==0){
		return "MIA";
	}
	else if(x.compare("Astros")==0|| x.compare("hou")==0||x.compare("HOU")==0||x.compare("Houston")==0){
		return "HOU";
	}
	else if(x.compare("Dodgers")==0|| x.compare("lad")==0||x.compare("LAD")==0||x.compare("LA Dodgers")==0){
		return "LAD";
	}
	else if(x.compare("Brewers")==0|| x.compare("mil")==0||x.compare("MIL")==0||x.compare("Milwaukee")==0){
		return "MIL";
	}
	else if(x.compare("Nationals")==0|| x.compare("was")==0||x.compare("WAS")==0||x.compare("wsh")==0||x.compare("WSH")==0||x.compare("Washington")==0||x.compare("WSN")==0){
		return "WAS";
	}
	else if(x.compare("Mets")==0|| x.compare("nym")==0||x.compare("NYM")==0||x.compare("NY Mets")==0){
		return "NYM";
	}
	else if(x.compare("Phillies")==0|| x.compare("phi")==0||x.compare("PHI")==0 || x.compare("Philadelphia")==0){
		return "PHI";
	}
	else if(x.compare("Pirates")==0|| x.compare("pit")==0||x.compare("PIT")==0||x.compare("Pittsburgh")==0){
		return "PIT";
	}
	else if(x.compare("Cardinals")==0 || x.compare("stl")==0||x.compare("STL")==0||x.compare("St. Louis")==0){
		return "STL";
	}
	else if(x.compare("Padres")==0|| x.compare("sd")==0||x.compare("SDG")==0||x.compare("SD")==0||x.compare("San Diego")==0||x.compare("SDP")==0){
		return "SDG";
	}
	else if(x.compare("Giants")==0|| x.compare("sfg")==0||x.compare("SFO")==0||x.compare("sf")==0||x.compare("SF")==0||x.compare("San Francisco")==0||x.compare("SFG")==0 || x.compare("SFGiants")==0){
		return "SFO";
	}
	else if(x.compare("- - -")==0){
		return "XXX";
	}
	else{
		return "ERR****" + x;
	}

}


// trim from start
static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

//Parse info into vector and class structure from LineUp text file from DraftKings
std::vector<PlayerInfo> LineUpData(string x){
	//PlayerInfo temp;
	string line;
	string fileNumber = x;
	string fileName = "C:\\progData\\LineUps\\"  + fileNumber;
	ifstream infile(fileName);
	string data = "";
	int pos = 0;
	std::vector<PlayerInfo> LineUPS;

	while(getline(infile,line)){
		// get position
		PlayerInfo* temp = new PlayerInfo();
		for(int x = 0; x< line.length(); x++){
			if(line[x]!=' ' && line[x]!='\t'){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setPos(data);
			data = "";
			/// first/lastName
		for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='\t'){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setName(data);
			data = "";
			//// Salary
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='\t'){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setSalary(atoi(data.c_str()));
			data = "";
			//Team1...
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='@' ){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setTeam1(data);
			data = "";
			//Team2...
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!=' ' ){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setTeam2(data);
			data = "";
			//time...
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='\t' ){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setMatchUP(data);
			data = "";
			//get AVGPTS
			for(int x = pos+1;x < line.length(); x++){
			if(line[x]!='\t'){
				data = data + line[x];
			}
			else{
				pos = x;
				x = x + line.length();
			}
		}
			temp->setAVGPTS(atof(data.c_str()));
			data = "";

			LineUPS.push_back(*temp);
	}

	
	return LineUPS;
}

vector<mlbPlayer> StartingPlayer(){
	//C:\progData\mlbFactors\Starting526
	 vector<mlbPlayer> startingPlayers;
	string fileLocation = "C:\\progData\\mlbFactors\\";
	fileLocation = fileLocation + isStartingFile;
	cout << fileLocation << endl;
	ifstream myFile(fileLocation);
	string templine ="";
	string temp;
	string team = "";
	int pos = 0;
	bool teamFlag = false;
	int battingOrder = 1;

	while(getline(myFile,templine)){
		mlbPlayer* newStarter = new mlbPlayer();
		if(isdigit(templine[0])==false && templine[0]!=' '){
			for(int x = 0; x< templine.length(); x++){
				if(templine[x]!=' '){
					temp = temp + templine[x];
				}
				else{
					pos = x+1;
					x = x + templine.length();
				}
			}//gets last name
		}
		else if(isdigit(templine[0])){
			for(int x = 0; x< templine.length(); x++){
				if(teamFlag==true && templine[x]!=' '){
					team = team + templine[x];
				}
				else
					teamFlag = false;
				if(templine[x]=='@'){
					teamFlag=true;
					team = "";
				}
			}
			battingOrder = 1;
		}
		teamFlag = false;
		//cout << team << endl;
		if(temp.compare("More")!=0 && temp.compare("View")!=0 && temp.compare("Reply")!=0 && temp.compare("")!=0){
			newStarter->setLastName(temp);
			newStarter->setBatOrder(battingOrder);
			battingOrder++;
			newStarter->setTeam(changeTeam(team));
			startingPlayers.push_back(*newStarter);
		}
		temp = "";
		
		
	}
	return startingPlayers;
}

vector<mlbPlayer> BatterHand(){
	vector<mlbPlayer> BatterHands;
	string fileLocation = "C:\\progData\\mlbFactors\\";
	fileLocation = fileLocation + BatterHands2015;
	cout << fileLocation << endl;
	ifstream myFile(fileLocation);
	string templine ="";
	string temp;
	string team = "";
	int pos = 0;

	while(getline(myFile,templine)){
		mlbPlayer* newHand = new mlbPlayer();
		for(int x = 0; x< templine.length(); x++){
				if(templine[x]!='+'){
					temp = temp + templine[x];
				}
				else{
					pos = x+1;
					x = x + templine.length();
				}
		}//gets full name
		newHand->setName(temp);
		temp = "";
		for(int x = pos; x< templine.length(); x++){
				if(templine[x]!='\n'){
					temp = temp + templine[x];
				}
				else{
					pos = x+1;
					x = x + templine.length();
				}
		}//gets Hand
		if(temp.compare("LEFT")==0){
			temp = "L";
		}
		else if(temp.compare("RIGHT")==0){
			temp = "R";
		}
		else
			temp = "S";
		newHand->setBatLRS(temp);
		temp = "";

		BatterHands.push_back(*newHand);
	}

	return BatterHands;
}

vector<mlbPlayer> MLBPlayerRosterTT(){
	vector<mlbPlayer> MLBRoster;
	string BvPFile = "C:\\progData\\mlbFactors\\";
	BvPFile = BvPFile + FIXTEAMS; ///Players520"; // replace spaces with a + and remove the %
	cout << BvPFile <<endl;
	ifstream myFile(BvPFile);
	string templine ="";
	string temp = "";
	int pos = 0;
	bool lastNameSpace = false;
	string lastName = "";

	while(getline(myFile,templine)){
		mlbPlayer* newPlayer = new mlbPlayer();
		for(int x = 0; x< templine.length(); x++){
			if(templine[x]!='+'){
				if(lastNameSpace == true){
					lastName = lastName + templine[x];
				}
				if(templine[x]==' '){
					lastNameSpace = true;
				}
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//gets name
		newPlayer->setLastName(lastName);
		newPlayer->setName(temp);
		//cout << temp << " ";
		temp = "";
		lastName = "";
		lastNameSpace = false;
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets team
		
		newPlayer->setTeam(changeTeam(temp));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets games
		newPlayer->setSeasonGames(atoi(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets woba
		newPlayer->setSeasonWOBA(atof(temp.c_str()));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets AVG
		newPlayer->setSeasonAVG(atof(temp.c_str()));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets OBP
		newPlayer->setSeasonOBP(atof(temp.c_str()));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets OPS
		newPlayer->setSeasonOPS(atof(temp.c_str()));
		//cout << temp << " ";
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// SB
		newPlayer->setSeasonSB(atoi(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// getsCS
		newPlayer->setSeasonCS(atoi(temp.c_str()));
		//cout << temp << endl;
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// Home Runs
		newPlayer->setSeasonHR(atoi(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// HR/Flyball ratio
		newPlayer->setSeasonHRrFlyball(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// StrikeOutPercent
		newPlayer->setStrikeOutPercent(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// Walk Percent
		newPlayer->setWalkPercent(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// wSB -- Waited stolen Base Runs 0- average +6 excellent -6 poor
		newPlayer->set_wSB(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// wRC -- Waited runs created
		newPlayer->set_wRC(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// wRAA -- Waited Runs Above Average
		newPlayer->set_wRAA(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gb% -- groundball percent
		newPlayer->set_gbPercent(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// fb% -- flyball%
		newPlayer->set_fbPercent(atof(temp.c_str()));
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// BB/K
		newPlayer->set_BBpK(atof(temp.c_str()));
		temp = "";



		MLBRoster.push_back(*newPlayer);
	}

	return MLBRoster;
}

vector<Pitcher> PitcherTeamFIX(){
	vector<Pitcher> PitcherList;
	// make sure odds file is up to date.....
	string fileLocation = "C:\\progData\\mlbFactors\\";
	fileLocation = fileLocation + PITCHERFIXTEAMS;
	cout << fileLocation << endl;
	ifstream myFile(fileLocation);
	string templine ="";
	string temp;
	int pos = 0;

	while(getline(myFile,templine)){
		Pitcher* newPitcher = new Pitcher();
		for(int x = 0; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//gets name
		newPitcher->setName(temp);
		temp = "";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets team
		newPitcher->setTeam(changeTeam(temp));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets wins
		newPitcher->setWins(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets loses
		newPitcher->setLoses(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets saves
		newPitcher->setSaves(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets games
		newPitcher->setGamesPlayed(atoi(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets games started
		newPitcher->setGameStarted(atoi(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets Innings Pitched
		newPitcher->setTotInnings(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets K/9
		newPitcher->setKper9(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets BB/9
		newPitcher->setBBper9(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets HR/9
		newPitcher->setHRper9(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets BABIP
		newPitcher->setBABIP(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets LOB%
		newPitcher->setLOBpercent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets GB%
		newPitcher->setGBpercent(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets HR/FB
		newPitcher->setHRlFB(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets ERA
		newPitcher->setERA(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets FIP
		newPitcher->setFIP(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets XFIP
		newPitcher->setXFIP(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets WAR
		newPitcher->setWAR(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets gb%
		newPitcher->set_gbPercent(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets fb%
		newPitcher->set_fbPercent(atof(temp.c_str()));
		temp ="";
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// sets KpBB
		newPitcher->set_KpBB(atof(temp.c_str()));
		temp ="";

		PitcherList.push_back(*newPitcher);
	}
	return PitcherList;
}

vector<Pitcher> PitcherDefenseVsSB(){
	vector<Pitcher> PitcherDefense;
	// make sure odds file is up to date.....
	string fileLocation = "C:\\progData\\mlbFactors\\";
	fileLocation = fileLocation + PitcherDefenseFanGRAPHS;
	cout << fileLocation << endl;
	ifstream myFile(fileLocation);
	string templine ="";
	string temp;
	int pos = 0;

	while(getline(myFile,templine)){
		Pitcher* newPitcher = new Pitcher();
		for(int x = 0; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//gets name
		newPitcher->setName(temp);
		temp = "";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets team
		newPitcher->setTeam(changeTeam(temp));
		temp ="";


		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// getsinnings
		newPitcher->setTotInnings(atoi(temp.c_str()));
		temp ="";


		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// sets rSB
		newPitcher->set_rSB(atoi(temp.c_str()));
		temp ="";
		/*
		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//sets SB
		newPitcher->setStolenBases(atoi(temp.c_str()));
		temp =""; */

		// End
		PitcherDefense.push_back(*newPitcher);
	}
	return PitcherDefense;
}

vector<Pitcher> PitcherPitchType(){
	//http://www.fangraphs.com/leaders.aspx?pos=all&stats=pit&lg=all&qual=y&type=c,75,77,79,81,83,85,87,89&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0
	vector<Pitcher> PitcherPitches;
	// make sure odds file is up to date.....
	string fileLocation = "C:\\progData\\mlbFactors\\";
	fileLocation = fileLocation + Pitcher_PitchType;
	std::cout << fileLocation << endl;
	ifstream myFile(fileLocation);
	string templine ="";
	string temp;
	int pos = 0;


	while(getline(myFile,templine)){
		Pitcher* newPitcher = new Pitcher();
		for(int x = 0; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//gets name
		newPitcher->setName(temp);
		temp = "";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets team
		newPitcher->setTeam(changeTeam(temp));
		temp ="";


		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// fb%
		newPitcher->set_fastball_percent(atof(temp.c_str()));
		temp ="";


		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// slider%
		newPitcher->set_slider_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//ct%
		newPitcher->set_ct_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//cb%
		newPitcher->set_curveball_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//ch%
		newPitcher->set_changeup_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//SF
		newPitcher->set_SplitFinger_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//knuckler%
		newPitcher->set_Knuckleball_percent(atof(temp.c_str()));
		temp ="";

		// End
		PitcherPitches.push_back(*newPitcher);
	
	}
	return PitcherPitches;
}

vector<mlbPlayer> Batter_Pitch_Type(){
	//http://www.fangraphs.com/leaders.aspx?pos=all&stats=bat&lg=all&qual=100&type=c,95,96,97,98,99,100,101&season=2015&month=0&season1=2013&ind=0&team=0&rost=0&age=0&filter=&players=0
	// Using wFB, wCB..ect its wieghted so taht Positive is good and negative is poor
	vector<mlbPlayer> batterPitches;
	// make sure odds file is up to date.....
	string fileLocation = "C:\\progData\\mlbFactors\\";
	fileLocation = fileLocation + Batter_PitchType;
	std::cout << fileLocation << endl;
	ifstream myFile(fileLocation);
	string templine ="";
	string temp;
	int pos = 0;


	while(getline(myFile,templine)){
		mlbPlayer* newBatter = new mlbPlayer();
		for(int x = 0; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//gets name
		newBatter->setName(temp);
		temp = "";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// gets team
		newBatter->setTeam(changeTeam(temp));
		temp ="";


		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// fb%
		newBatter->set_fastball_percent(atof(temp.c_str()));
		temp ="";


		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}// slider%
		newBatter->set_slider_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//ct%
		newBatter->set_ct_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//cb%
		newBatter->set_curveball_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//ch%
		newBatter->set_changeup_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//SF
		newBatter->set_SplitFinger_percent(atof(temp.c_str()));
		temp ="";

		for(int x = pos; x< templine.length(); x++){
			if(templine[x]!='+'){
				temp = temp + templine[x];
			}
			else{
				pos = x+1;
				x = x + templine.length();
			}
		}//knuckler%
		newBatter->set_Knuckleball_percent(atof(temp.c_str()));
		temp ="";

		// End
		batterPitches.push_back(*newBatter);
	
	}
	return batterPitches;
}