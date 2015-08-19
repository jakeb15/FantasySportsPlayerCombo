//takes a LINEUP -> get from draftkings.com it the form of a excel spreadsheet. Copy data to a text file named LineUpData.txt.
//Loads textfile into a class called PlayerInfo. 
//
// Input players who I beleive to get value -> loads into a vector and some how display possible line ups that will be as close to possible 50000k salary
//
//
//Notes: on Players.... Enter a line up. When I load a line up check all notes on players
//
//							Team1 @ Team2 GameINfo is time
//  ex: PG Mo Williams 7000 Cha@Mia 8:00PM ET 34.44
//	cout << it->getPos() << " " << it->getName() << " " << it->getSalary() << " " << it->getTeam1() << "@" << it->getTeam2() << " "<< it->getMatchUP() << " " << it->getAVGPTS() <<endl;
//	
// 
//All parse correctly need to work on 

// get the 

#include "stdafx.h"
#include "mlbFunctions.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <istream>
#include <iomanip>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>



using namespace std;

void getWebPage(char* s, char * temp);
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
std::vector<PlayerInfo> InputPlayers(std::vector<PlayerInfo> LU);// Takes Human picks and puts them into a vector and returns

//Notes to self on what to look at before picking
void GeneralInfo();

//determines the salary difference between 2 line ups. No real need to use
void SalaryDiffernce(std::vector<PlayerInfo> LineUpData,std::vector<PlayerInfo> LineUpData2);

// Does nothing at the moment. - Looking to insert a list of guys and have it shoot out a line up
void CreateCombo(std::vector<PlayerInfo> LineUpData);

//attaches a trigger to the player - Note that triggers during specific match up. Example: When Steph Curry plays CP3 they bring their A+ game.
string attachTriggers(string name, string team1, string team2);

//parses live odds from covers.com MLB//NBA//NHL
void LiveOdds(int x);




int _tmain(int argc, _TCHAR* argv[])
{
	////////Settings///////////
	string LUnumber = "1021"; // Current Line UP to import ex. LU6.txt 
	int sportOdds = 3; // sport to get 1 - nba | 2 - mlb | 3-nhl
	GeneralInfo();

	//////////////////////////////////////////////////////////////
	////////// color ////////////////////////
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	//////////////////////////////////////////
	BallParkParse();

	//LoadGameOdds();
	//vector<mlbPlayer> temp = 
	//vector<mlbPlayer> tempMLB = parseData("APR 07");
		
	vector<PlayerInfo> playerLU = LineUpData(LUnumber);
	
	vector<mlbPlayer> BvPinfo = BvPParse(); //parse data from BvP

	////////Testing Area/////////////
	string t;
	cin >> t;
	
	if(t.compare("y")==0){
		MLBProjectionsCSV();
		CalcPlayerProjections(BvPinfo,BallParkParse());
	}
	/////////////////////////////////


	string tempData = "";
	string gottenData = "";
	string x ="";
	int zz = 1;
	cout << "Run BvP and Recent player performance";
	cin >> x;
///////////////////////////////Recent Player Performance/////////////////////////////////////////////////////////////////////////////////////
	
	if(x.compare("y")==0){
		////THis is where the games are
		for(int x = 18; x<=20;x++){
			vector<mlbPlayer> tempMLB = parseData(x);
			for(std::vector<PlayerInfo>::iterator LU = playerLU.begin(); LU != playerLU.end(); LU++){
				if(LU->getPos().compare("SP")==0){}
				else if(LU->getPos().compare("RP")==0){}
				else{
					for (std::vector<mlbPlayer>::iterator it = tempMLB.begin() ; it != tempMLB.end(); ++it){
						if(LU->getName().compare(it->getName())==0){
							gottenData = LU->getprevGameData();
							tempData = "| ";
							tempData = tempData + it->getOppt() + " ";
							tempData = tempData + std::to_string((int)it->getDkpts());
							tempData = tempData + " | ";
							gottenData = gottenData + tempData;
							LU->setprevGameData(gottenData);
							gottenData ="";
							LU->setTeam1(it->getTeam());
							LU->setTeam2(it->getOppt());
						}
					}
				}
			}
			zz++;
		}
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////


		//attaching BvP info to PlayerLine-Up
		for(std::vector<PlayerInfo>::iterator LU = playerLU.begin(); LU != playerLU.end(); LU++){
			for (std::vector<mlbPlayer>::iterator it = BvPinfo.begin() ; it != BvPinfo.end(); ++it){
				if(LU->getName().compare(it->getName())==0){
					LU->setBvPinfo(it->getBvP());
					LU->setAtBats(it->getAtBats());
				}
			}
		}

	
		std::sort(playerLU.begin(), playerLU.end(),PlayerInfo::comparePOS());
		//  || LU->getTeam1().compare("COL")!=0 
		for(std::vector<PlayerInfo>::iterator LU = playerLU.begin(); LU != playerLU.end(); LU++){
			if(LU->getPos().compare("SP")==0 || LU->getPos().compare("RP")==0  ){}
			else{
				cout <<LU->getSalary()<<" " << LU->getPos() << " "<<LU->getTeam1() <<" "<<LU->getName() <<  " ";
				SetConsoleTextAttribute ( h,  FOREGROUND_BLUE  | FOREGROUND_INTENSITY | 12 );
				cout << LU->getprevGameData() << " || ";
				SetConsoleTextAttribute ( h, wOldColorAttrs);

				if(LU->getAtBats() > 10){
					SetConsoleTextAttribute ( h,  FOREGROUND_GREEN  | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY );
				}
					cout << "AB: " << LU->getAtBats() << LU->getBvPinfo() <<endl;
				SetConsoleTextAttribute ( h, wOldColorAttrs);
			}
		}
	}
	///////////////Testing Function/projects in work///////////////////
	//SalaryDiffernce(LineUpData("1"),LineUpData("2"));
	///////////////////////////////////////////////////////////////////
	
	CreateCombo(InputPlayers(LineUpData(LUnumber)));
	
	return 0;
}


std::vector<PlayerInfo> InputPlayers(std::vector<PlayerInfo> LU){
	std::vector<PlayerInfo> lineUPS = LU;
	// Sort LineUP by Decending Salary Order
	std::sort(lineUPS.begin(), lineUPS.end(),PlayerInfo::compareMyDataFunctor());

	////////// color ////////////////////////
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	//////////////////////////////////////////
	
	ofstream triggerFile;
	triggerFile.open("Triggers.txt",std::ofstream::out | std::ofstream::app);

	std::vector<PlayerInfo> enteredPlayers;
	bool Go = true;
	bool playerFound = false;
	bool Reset = false;
	bool EnterPlayer = false;
	string triggerTeam ="";
	string triggerMSG;
	string answer = "";
	string temp = "";
	string position = "";
	string james = "james";
	string PlayerName = "";
	int found;
	int sport;

	while(Go){
		cout << "[a]ll players [o]dds [s]how current list [p]osition [c]lear screen [e]nter Player [Q]uit" <<endl;
		temp = "";
		position = "";
		playerFound = false;
		Reset = false;
		cin >> temp;


		//Show all players eligible to become picked. Color code by Position and sortted by Salary decending
		if(temp.compare("a")==0){
			for (std::vector<PlayerInfo>::iterator it = lineUPS.begin() ; it != lineUPS.end(); ++it){
				if(it->getPos().compare("PG")==0){
					SetConsoleTextAttribute ( h,  FOREGROUND_BLUE  | 61 | BACKGROUND_INTENSITY );
				}
				else if(it->getPos().compare("SG")==0){
					SetConsoleTextAttribute ( h,  52  | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY );
				}
				else if(it->getPos().compare("SF")==0){
					SetConsoleTextAttribute ( h,  FOREGROUND_BLUE  | FOREGROUND_INTENSITY | BACKGROUND_INTENSITY );
				}
				else if(it->getPos().compare("PF")==0){
					SetConsoleTextAttribute ( h,  FOREGROUND_BLUE  | FOREGROUND_INTENSITY | 40 );
				}
				else if(it->getPos().compare("C")==0){
					SetConsoleTextAttribute ( h,  52  | FOREGROUND_INTENSITY | 62 );
				}
					cout <<setw(2)<< it->getPos() << " " <<setw(25) << it->getName() << " "<<setw(5) << it->getSalary() << " " <<setw(3) <<it->getTeam1() << "@" <<setw(3)<< it->getTeam2() << " "<< it->getMatchUP() << " " <<setw(6)<< it->getAVGPTS()<< " ";
					attachTriggers(it->getName(), it->getTeam1() , it->getTeam2());
					cout <<endl;
					SetConsoleTextAttribute ( h, wOldColorAttrs);
			}
		}
		
		if(temp.compare("s")==0){
			for (std::vector<PlayerInfo>::iterator it = enteredPlayers.begin() ; it != enteredPlayers.end(); ++it){
				cout << it->getPos() << " " << it->getName() << " " << it->getSalary() << " " << it->getTeam1() << "@" << it->getTeam2() << " "<< it->getMatchUP() << " " << it->getAVGPTS() <<endl;
			}
			playerFound = true;
		}

		//Exit and submit selected players
		if(temp.compare("Q")==0){
			Go = false;
			playerFound=true;
		}

		if(temp.compare("o")==0){
			cout << "1- NBA 2-MLB 3-NHL" << endl;
			cin >> sport;
			LiveOdds(sport);
			playerFound=true;
		}

		if(temp.compare("c")==0){
			playerFound=true;
			system("cls");
		}

		if(temp.compare("e")==0){
			EnterPlayer = true;
		}

		if(temp.compare("p")==0){
			cout << "what position...? ";
			cin >> position;

			if(position.compare("PG")==0){
				for (std::vector<PlayerInfo>::iterator it = lineUPS.begin() ; it != lineUPS.end() && playerFound == false; ++it){
					if(it->getPos().compare("PG")==0){
						cout << it->getPos() << " " << it->getName() << " " << it->getSalary() << " " << it->getTeam1()<< "@" <<it->getTeam2() << " " << it->getAVGPTS() <<endl;
					}
				}
				
			}

			else if(position.compare("SG")==0){
				for (std::vector<PlayerInfo>::iterator it = lineUPS.begin() ; it != lineUPS.end() && playerFound == false; ++it){
					if(it->getPos().compare("SG")==0){
						cout << it->getPos() << " " << it->getName() << " " << it->getSalary() << " "<< it->getTeam1()<< "@" <<it->getTeam2() <<" " << it->getAVGPTS() <<endl;
					}
				}
				
			}

			else if(position.compare("SF")==0){
				for (std::vector<PlayerInfo>::iterator it = lineUPS.begin() ; it != lineUPS.end() && playerFound == false; ++it){
					if(it->getPos().compare("SF")==0){
						cout << it->getPos() << " " << it->getName() << " " << it->getSalary() << " " << it->getTeam1()<< "@" <<it->getTeam2() << " " << it->getAVGPTS() <<endl;
					}
				}
			}

			else if(position.compare("PF")==0){
				for (std::vector<PlayerInfo>::iterator it = lineUPS.begin() ; it != lineUPS.end() && playerFound == false; ++it){
					if(it->getPos().compare("PF")==0){
						cout << it->getPos() << " " << it->getName() << " " << it->getSalary() << " " << it->getTeam1()<< "@" <<it->getTeam2() <<" " << it->getAVGPTS() <<endl;
					}
				}
			}

			else if(position.compare("C")==0){
				for (std::vector<PlayerInfo>::iterator it = lineUPS.begin() ; it != lineUPS.end() && playerFound == false; ++it){
					if(it->getPos().compare("C")==0){
						cout << it->getPos() << " " << it->getName() << " " << it->getSalary() << " " << it->getTeam1()<< "@" <<it->getTeam2() << " " << it->getAVGPTS() <<endl;
					}
				}
				
			}
		}

		if(EnterPlayer == true){
			cout << "Ready for player... "<<endl;
			cin >> PlayerName;
			for (std::vector<PlayerInfo>::iterator it = lineUPS.begin() ; it != lineUPS.end() && playerFound == false ; ++it){
				found = it->getName().find(PlayerName);
				if (found>-1 && playerFound== false && Reset == false){
					cout << "Did you mean..." << it->getName()<< "?" << " (y)es (n)ext (r)eset (s)et trigger ";
					cin >> answer;
						if(answer.compare("y")==0){
							playerFound = true;
						}
						else if(answer.compare("n")==0){
	
						}
						else if(answer.compare("r")==0){
							Reset = true;
						}
						else if(answer.compare("s")==0){
							cout << "Enter info... ";
							std::getline(std::cin,triggerMSG);
							triggerFile << it->getName() << " " << triggerMSG <<endl;
							Reset = true;
						}
				}
				if(playerFound==true){
					cout << "Player accepted" <<endl;
					enteredPlayers.push_back(*it);
					EnterPlayer = false;
					
				}
			}
		}
	}

	cout << "returning Players selected" <<endl;

	return enteredPlayers;
}

void GeneralInfo(){
	cout << "-Players playing back to back, Be sure to look forward and backwards at schedule" << endl;
	cout <<"-Game info: Dead team playing Playoff bound team - Possible Trap" <<endl;
	cout << "-Odds and Over/Under - Locate Trap games" <<endl;
	cout << "-Get LineUps for next days games up ASAP....More Time for bad players to join your games, Also less people for them to play against at the moment" <<endl;
	cout << "-BumHunt all hours of the day" <<endl;
	cout << "-Use Twitter to see if coach will use certain players" <<endl;
	
}

void SalaryDiffernce(std::vector<PlayerInfo> LineUpData,std::vector<PlayerInfo> LineUpData2){
	std::vector<PlayerInfo> LU1 = LineUpData;
	std::vector<PlayerInfo> LU2 = LineUpData2;
	int x;
	bool playedLastNight = false;
	int SalaryDiff = 0;

	for (std::vector<PlayerInfo>::iterator it = LU1.begin() ; it != LU1.end(); ++it){
		for (std::vector<PlayerInfo>::iterator it2 = LU2.begin() ; it2 != LU2.end(); ++it2){
			if(it->getName().compare(it2->getName())==0){
				cout << it2->getName() << " " << "Played Last Night.." <<endl;
				cout << "salaryDiff: " << it2->getSalary() - it->getSalary() <<endl;
			}
		}
	}


}

void CreateCombo(std::vector<PlayerInfo> LineUpData){
	

}

string attachTriggers(string name, string team1, string team2){
	//open trigger file
	//read line
	//push trigger 
	ifstream infile("Triggers.txt");
	string line ="";
	string pName = "";
	string team = "";
	string MSG = "";
	int pos = 0;

	while(getline(infile,line)){
		// first name
		for(int x =0; x<line.length();x++){
			if(line[x]!=' '){
			 pName = pName + line[x];
			}
			else{
			 pos = x+1;
			 pName = pName + " ";
			 x = x +line.length();
			}
		}
		//Last name
		for(int x = pos; x<line.length();x++){
			if(line[x]!=' '){
			 pName = pName + line[x];
			}
			else{
			 pos = x+1;
			 x = x+line.length();
			}
		}
		///team
		for(int x = pos+1; x<line.length();x++){
			if(line[x]!=' '){
			 team = team + line[x];
			}
			else{
			 pos = x+1;
			 x = x+line.length();
			}
		}
		//MSG
		for(int x = pos; x<line.length();x++){
			if(line[x]!='\n'){
			 MSG = MSG + line[x];
			}
			else{
				x = x +line.length();
			}
		}
		if((name.compare(pName)==0 && team1.compare(team)==0) || (name.compare(pName)==0 && team2.compare(team)==0)){
			cout <<setw(45) <<MSG;
		}
		pName = "";
		team = "";
		MSG = "";
	}

	return MSG;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void getWebPage(char* s, char * temp){
	CURL *curl;
	CURLcode res;
    FILE *fp;
	char *url = s;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen(temp,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
	    curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER, false); // doesnt verify SSL otherwise erro 60
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

void LiveOdds(int x){

	////////// color ////////////////////////
	HANDLE h = GetStdHandle ( STD_OUTPUT_HANDLE );
	WORD wOldColorAttrs;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(h, &csbiInfo);
	wOldColorAttrs = csbiInfo.wAttributes;
	//////////////////////////////////////////
	ofstream oddsOut;
	oddsOut.open("C:\\progData\\odds",std::ofstream::out);

	string sporthtml ="";
	if (x==1)
		sporthtml = "http://www.covers.com/odds/basketball/nba-spreads.aspx";
	else if (x==2)
		sporthtml = "http://www.covers.com/odds/baseball/mlb-odds.aspx";
	else if(x==3)
		sporthtml = "http://www.covers.com/odds/hockey/nhl-puckline-odds.aspx";

	char * temp = new char[sporthtml.size() + 1];
	std::copy(sporthtml.begin(), sporthtml.end(), temp);
	temp[sporthtml.size()] = '\0';

	cout << "Fetching odds..."<<endl;
	getWebPage(temp,"odds.txt");

	ifstream infile("odds.txt");
	string line = "";
	int found;
	int raw;
	int end;
	string data = "";
	string dataOdds = "";
	bool dataBlock = false;
	int count = 0;
	float openSpread = 0;
	float openOU = 0;


	//begin parsing covers.com for live odds
	while(getline(infile,line)){
		found = line.find("<strong>");
		raw = line.find("<");
		end = line.find("</tr>");

		if(raw < 0 && dataBlock ==true){
			for(int x = 0; x< line.length();x++){
				if(line[x]!=' ' && line[x]!='\t'){
					dataOdds = dataOdds + line[x];
				}
			}
			if(dataOdds.compare("")!=0){
				if(count ==4 || count ==5){
					cout << "|";
					SetConsoleTextAttribute ( h,  FOREGROUND_BLUE  | FOREGROUND_INTENSITY | 12 );
					cout << " " <<dataOdds << " ";
					oddsOut << " " <<dataOdds << " ";
					if(count == 4){
						openSpread = atof(dataOdds.c_str());
					}
					else if(count ==5){
						openOU = atof(dataOdds.c_str());
					}
				}
				else if(count > 5  && count%2==0){
					if(atof(dataOdds.c_str()) > openSpread){
						SetConsoleTextAttribute ( h,  FOREGROUND_GREEN  | 0 | 0 );
						cout << "| " <<dataOdds;
						oddsOut << "| " <<dataOdds;
					}
					else if(atoi(dataOdds.c_str()) < openSpread){
						SetConsoleTextAttribute ( h,  FOREGROUND_RED | FOREGROUND_INTENSITY | 12 );
						cout << "| " <<dataOdds;
						oddsOut << "| " <<dataOdds;
					}
					else{
						cout << "| " <<dataOdds;
						oddsOut << "| " <<dataOdds;
					}
				}
				else if(count > 5 ){
					if(atof(dataOdds.c_str()) > openOU){
						SetConsoleTextAttribute ( h,  FOREGROUND_GREEN  | 0 | 0 );
						cout << "| " <<dataOdds;
						oddsOut << "| " <<dataOdds;
					}
					else if(atoi(dataOdds.c_str()) < openOU){
						SetConsoleTextAttribute ( h,  FOREGROUND_RED  | FOREGROUND_INTENSITY | 12 );
						cout << "| " <<dataOdds;
						oddsOut << "| " <<dataOdds;
					}
					else{
						cout << "| " <<dataOdds;
						oddsOut << "| " <<dataOdds;
					}
				}

				count++;
			}
			dataOdds = "";
		}

		if(end > 0){
			cout << endl;
			oddsOut << endl;
			dataBlock = false;
			count = 0;
		}
		if(found  > 0){
			dataBlock = true;
			for(int x = found + 8; x<line.length();x++){ // 8 gets us past strong tag
				if(line[x]!='<'){
					data = data + line[x];
				}
				else{
					x = x+line.length();
				}
			}
		cout << endl <<data;
		oddsOut << endl <<data;
		data = "";
		}

		SetConsoleTextAttribute ( h, wOldColorAttrs);
	}

}

