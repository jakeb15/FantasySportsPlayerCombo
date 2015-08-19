#include "stdafx.h"
#include "MLBprojectionsCSV.h"
#include <sstream>
void MLBProjectionsCSV(){


	bool compFlag = false;
	bool pitcherInFlag = false;
	static bool noPitcher = false;
	static bool noHand = true;
	static bool noPos = true;

	ofstream pitchingToday;
	ofstream battingToday;
	ofstream BvPToday;

	stringstream ss;

	pitchingToday.open("C:\\progData\\PitchingToday.csv",std::ofstream::out);
	battingToday.open("C:\\progData\\BattingToday.csv",std::ofstream::out);
	BvPToday.open("C:\\progData\\BvP.csv",std::ofstream::out);
	
	vector<PlayerInfo> playerLU = LineUpData("DKroster818"); //Data found from Draftkings supplied CSV - exports possible players/salaries
	vector<Pitcher> PitcherMLB = PitcherStats(); //Data found from Fan Graphs - Last 3 years of pitcher data
	//http://www.fangraphs.com/leaders.aspx?pos=all&stats=pit&lg=all&qual=0&type=c,4,5,11,7,8,13,-1,36,37,40,43,44,48,51,-1,6,45,62,-1,59,48,49,38&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0&sort=8,d
	// Link above is the pitcher data that is parsed using PitcherStats(), Some pitchers may not be on the same team they are now. So grabbing a current roster from the above link and assigning them their team might be needed

	vector<mlbPlayer> playerHands = BatterHand(); //A file with players and thier known batting hand, LEFTY, RIGHTY, SWITCH
	vector<mlbPlayer> mlbRoster = MLBPlayerRoster();//imports the players stats from the last 3 years, data grabbed off FanGraphs.com
	//http://www.fangraphs.com/leaders.aspx?pos=all&stats=bat&lg=all&qual=10&type=c,4,50,23,37,39,21,22,11,47,35,34,200,52,51,44,45,36&season=2015&month=0&season1=2015&ind=0&team=0&rost=0&age=0&filter=&players=0
	//Before using File Remove all Tab spaces and replace with +,  Then % characters delete and replace with nothing.

	vector<mlbPlayer> MLB_Player_TeamFix = MLBPlayerRosterTT();//Takes an updated stats from the link above and puts it into this array. 
	// We now compare MLB_PLAYER_TeamFIX with mlbRoster and assign mlbRoster players with thier current team.

	vector<Pitcher> PitcherFIX = PitcherTeamFIX(); // Same thing as we did with MLB_PLAYER_TeamFIX
	//Assign pitchers with thier current team by comparing this vector with PitcherMLB

	vector<Pitcher> isPitching; // Useto store Pitchers that are pitching today
	vector<mlbPlayer> probablePitcher; // temp storage

	vector<gameOdds> OddsIN = LoadGameOdds(); //gets GameOdds using Covers.com - Grabs Opening lines

	vector<mlbPlayer> PlayersIN = BvPParse(); //BvP FIle Taken From - http://rotoguru.net/

	vector<BallPark> ParkIN = BallParkParse(); //BallPark Information

	vector<mlbPlayer> Starters = StartingPlayer(); // Starting Players Parsed off Twitter Handle...www.twitter.com/mlblineups

	vector<Pitcher> PitcherDefense = PitcherDefenseVsSB();

	vector<Catcher> CatcherData = CatcherStats();

	vector<Pitcher> PitchType = PitcherPitchType();

	vector<mlbPlayer> BatterPitches = Batter_Pitch_Type();

	cout << "finished Parsing data..." << endl;
	///////////////////////////////////////////TESTing VECTORS////////////////////////////////////////////////////////////////////////////
	for(std::vector<mlbPlayer>::iterator LU = BatterPitches.begin(); LU != BatterPitches.end(); LU++){
		cout <<  LU->getName() << " fb% " << LU->get_fastball_percent() << " changeup%" << LU->get_changeup_percent() << endl;
	}




	////
	cout << "Getting and Attaching Player Salary/Positions..." <<endl;
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<PlayerInfo>::iterator PI = playerLU.begin(); PI != playerLU.end(); PI++){
			if(PI->getName().compare(LU->getName())==0){
				LU->setDKsal(PI->getSalary());
				LU->setDkPosn(PI->getPos());
				noPos = false;
			}
			else if(noPos == true){
				LU->setDkPosn("?");
			}
		}
		noPos = true;
	}

	cout << "ReAttach Team Data...." << endl;
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<mlbPlayer>::iterator TF = MLB_Player_TeamFix.begin(); TF != MLB_Player_TeamFix.end(); TF++){
			if(LU->getName().compare(TF->getName())==0){
				LU->setTeam(TF->getTeam());
			}
		}
	}

	// attach player's hands data
	cout << "attaching Player's....hands" << endl;
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<mlbPlayer>::iterator hands = playerHands.begin(); hands != playerHands.end(); hands++){
			if(LU->getName().compare(hands->getName())==0){
				LU->setBatLRS(hands->getBatLRS());
				noHand = false;
			}
			else if(noHand == true){
				LU->setBatLRS("?");
			}
		}
		noHand = true;
	}

	// Attaching Starter Status
	cout << "attaching starter Status..." << endl;
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<mlbPlayer>::iterator str = Starters.begin(); str != Starters.end(); str++){
			if(LU->getLastName().compare(str->getLastName())==0 && LU->getTeam().compare(str->getTeam())==0){
				LU->setStarter(1);
				LU->setBatOrder(str->getBatOrder());
			}
		}
	}

	// Attach Pitcher team to record
	cout << "Attach Pitcher Team Data...." << endl;
	for(std::vector<Pitcher>::iterator LU = PitcherMLB.begin(); LU != PitcherMLB.end(); LU++){
		for(std::vector<Pitcher>::iterator TF = PitcherFIX.begin(); TF != PitcherFIX.end(); TF++){
			if(LU->getName().compare(TF->getName())==0){
				LU->setTeam(TF->getTeam());
			}
		}
	}

	//gets probable pitchers from bvp and puts them into its own vector called probable pitchers
	cout << "Grabbing todays probable pitchers from BvP file..." <<endl;
	for(std::vector<mlbPlayer>::iterator ptc = PlayersIN.begin(); ptc != PlayersIN.end(); ptc++){
		for(std::vector<mlbPlayer>::iterator ttt = probablePitcher.begin(); ttt != probablePitcher.end(); ttt++){
			if(ptc->getStartingPitcher().compare(ttt->getStartingPitcher())==0){
				pitcherInFlag = true;
			}
		}
		if(pitcherInFlag == false){
			
			probablePitcher.push_back(*ptc);
		}
		pitcherInFlag  = false;
	}

	cout << "Filtering out Non-Pitchers.." <<endl;
	for(std::vector<Pitcher>::iterator ptc = PitcherMLB.begin(); ptc != PitcherMLB.end(); ptc++){
		for(std::vector<mlbPlayer>::iterator ttt = probablePitcher.begin(); ttt != probablePitcher.end(); ttt++){
			if(ptc->getName().compare(ttt->getStartingPitcher())==0){
				ptc->setPitchingHand(ttt->getPitcherHand());
				ptc->setTeam(ttt->getOppt());// added
				if(ptc->getTeam().compare("")==0 || ptc->getTeam().compare("XXX")==0)
					ptc->setTeam(ttt->getOppt());
				isPitching.push_back(*ptc);
			}
			
		}
	}

	cout << "assigning Probable Pitchers an Opponent" << endl;
	for(std::vector<Pitcher>::iterator LU = isPitching.begin(); LU != isPitching.end(); LU++){
		//assign H/A
		for(std::vector<gameOdds>::iterator odds = OddsIN.begin(); odds != OddsIN.end(); odds++){
			if(LU->getTeam().compare(odds->getAwayTeam())==0){
				LU->setOpponent(odds->getHomeTeam());
			}
			else if(LU->getTeam().compare(odds->getHomeTeam())==0){
				LU->setOpponent(odds->getAwayTeam());
			}
			else if(LU->getTeam().compare("XXX")==0)
				LU->setOpponent("XXX");
		}
	}

	cout << "assigning Starting Batters an Opponent" << endl;
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		//assign H/A
		for(std::vector<gameOdds>::iterator odds = OddsIN.begin(); odds != OddsIN.end(); odds++){
			if(LU->getTeam().compare(odds->getAwayTeam())==0){
				LU->setOppt(odds->getHomeTeam());
			}
			else if(LU->getTeam().compare(odds->getHomeTeam())==0){
				LU->setOppt(odds->getAwayTeam());
			}
			else if(LU->getTeam().compare("XXX")==0)
				LU->setOppt("XXX");
		}
	}

	cout << "attaching pitcher to batter.. " << endl;
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<Pitcher>::iterator tt = isPitching.begin(); tt != isPitching.end(); tt++){
			if(LU->getOppt().compare(tt->getTeam())==0 && tt->getTeam().compare("")!=0){
				LU->setStartingPitcher(tt->getName());
				LU->setPitcherHand(tt->getPitchingHand());
				noPitcher = true;
			}
			else if(LU->getTeam().compare("XXX")==0){
				LU->setStartingPitcher("XXX");
				LU->setPitcherHand("?");
				noPitcher = true;
			}
			else if(noPitcher == false){
				LU->setPitcherHand("?");
				LU->setStartingPitcher("Error");
			}
		}
		noPitcher = false;
	}
	
	// attach pitching rSB to isPitching pitcher
	for(std::vector<Pitcher>::iterator tt = isPitching.begin(); tt != isPitching.end(); tt++){
		for(std::vector<Pitcher>::iterator zz = PitcherDefense.begin(); zz != PitcherDefense.end(); zz++){
			if(tt->getName().compare(zz->getName())==0){
				tt->set_rSB(zz->get_rSB());
			}
		}
	}

	// attach pitch type to pitcher
	for(std::vector<Pitcher>::iterator tt = isPitching.begin(); tt != isPitching.end(); tt++){
		for(std::vector<Pitcher>::iterator zz = PitchType.begin(); zz != PitchType.end(); zz++){
			if(tt->getName().compare(zz->getName())==0){
				tt->set_changeup_percent(zz->get_changeup_percent());
				tt->set_fastball_percent(zz->get_fastball_percent());
				tt->set_curveball_percent(zz->get_curveball_percent());
				tt->set_slider_percent(zz->get_slider_percent());
				tt->set_SplitFinger_percent(zz->get_SplitFinger_percent());
				tt->set_ct_percent(zz->get_ct_percent());
				tt->set_Knuckleball_percent(zz->get_Knuckleball_percent());
			}
		}
	}

	// attach Pitch Type to batter . this attaches wFB, wCB, wSL ect weighted values +/- where 0 is average
	for(std::vector<mlbPlayer>::iterator tt = mlbRoster.begin(); tt != mlbRoster.end(); tt++){
		for(std::vector<mlbPlayer>::iterator zz = BatterPitches.begin(); zz != BatterPitches.end(); zz++){
			if(tt->getName().compare(zz->getName())==0){
				tt->set_changeup_percent(zz->get_changeup_percent());
				tt->set_fastball_percent(zz->get_fastball_percent());
				tt->set_curveball_percent(zz->get_curveball_percent());
				tt->set_slider_percent(zz->get_slider_percent());
				tt->set_SplitFinger_percent(zz->get_SplitFinger_percent());
				tt->set_ct_percent(zz->get_ct_percent());
				tt->set_Knuckleball_percent(zz->get_Knuckleball_percent());
			}
		}
	}
	float CatcherSBrate =0;
	

	//attach Catcher data to mlb Roster
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<Catcher>::iterator Ctch = CatcherData.begin(); Ctch != CatcherData.end(); Ctch++){
			if(LU->isStarter()==1 && LU->getName().compare(Ctch->getName())==0){
				LU->set_rSB(Ctch->get_rSB());
				CatcherSBrate = Ctch->getTotInnings()/(Ctch->getCaughtStealing() + Ctch->getStolenbases());
				ss << CatcherSBrate;
				LU->setDebug("SB:attempt: " + ss.str() );
				ss.str("");
				CatcherSBrate=0;
			}
		}
	}

	
	CatcherSBrate =0;

	// attach Catcher rSB to isPitching pitcher
	for(std::vector<Pitcher>::iterator tt = isPitching.begin(); tt != isPitching.end(); tt++){
		for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
			if(LU->isStarter()==1 && LU->getTeam().compare(tt->getTeam())==0){
				tt->set_Catcher_rSB(LU->get_rSB());
			}
		}
	}

	///small stolen base projection//
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		if(LU->get_wSB() > 0){
			LU->set_SB_Projection(LU->get_SB_Projection()+1);
		}

		for(std::vector<Pitcher>::iterator Pt = isPitching.begin(); Pt != isPitching.end(); Pt++){
			if(LU->getOppt().compare(Pt->getTeam())==0 && Pt->get_rSB() < -2){
				LU->set_SB_Projection(LU->get_SB_Projection()+1);
			}
		}

	}
	
	//////////////////////////////////////////////////////// up To this Point isPitching and mlbRoster should be complete /////////////////////////////

	cout << "Creating Pitcher CSV file..."<< endl;
	pitchingToday << "\"Name\", \"Team\",\"Tot_Innings\",\"K/9\",\"rSB\",\"ERA\",\"FIP\",\"BABIP\",\"GB%\",\"FB%\",\"K/B\",\"hr/FB\",\"wFB\",\"wCH\",\"wSL\",\"wSF\",\"wCB\",\"wCT\",\"wKnuckler\",\"Opponent\"" << endl;
	for(std::vector<Pitcher>::iterator ptc = isPitching.begin(); ptc != isPitching.end(); ptc++){
		pitchingToday << "\"" << ptc->getName() << "\",\"" << ptc->getTeam() << "\",\""<< ptc->getTotInnings()<<"\",\"" << ptc->getKper9() <<
			"\",\"" << ptc->get_rSB() << "\",\"" << ptc->getERA() <<  "\",\"" << ptc->getFIP() << "\",\"" << ptc->getBABIP() << "\",\"" << ptc->get_gbPercent()
			<<  "\",\"" << ptc->get_fbPercent() << "\",\"" <<  ptc->get_KpBB() << "\",\""<< ptc->getHRlFB() << "\",\"" <<  ptc->get_fastball_percent() 
				<< "\",\"" <<  ptc->get_changeup_percent() << "\",\"" <<  ptc->get_slider_percent() << "\",\"" <<  ptc->get_SplitFinger_percent()<< "\",\"" <<  ptc->get_curveball_percent()<< "\",\"" 
				<<  ptc->get_ct_percent() << "\",\"" <<  ptc->get_Knuckleball_percent()<<"\",\"" << ptc->getOpponent() << "\"" <<endl;
	}

	cout << "Creating Batter CSV file..." << endl;

	battingToday << "\"Salary\",\"Name\",\"Team\",\"Vs\",\"SB_Projection\",\"Pitcher\",\"Starting\",\"wFB\",\"wCH\",\"wSL\",\"wSF\",\"wCB\",\"wCT\",\"wKnuckler\"" << endl;
	for(std::vector<mlbPlayer>::iterator ptc = mlbRoster.begin(); ptc != mlbRoster.end(); ptc++){
		if(ptc->getDKsal()!=0){
			battingToday << "\"" << ptc->getDKsal() << "\",\"" << ptc->getName() << "\",\"" << ptc->getTeam() << "\",\"" << ptc->getOppt() <<
				"\"," << ptc->get_SB_Projection() << "\",\"" << ptc->getStartingPitcher() << "\",\"" <<  ptc->isStarter()<< "\",\"" <<  ptc->get_fastball_percent() 
				<< "\",\"" <<  ptc->get_changeup_percent() << "\",\"" <<  ptc->get_slider_percent() << "\",\"" <<  ptc->get_SplitFinger_percent()<< "\",\"" <<  ptc->get_curveball_percent()<< "\",\"" 
				<<  ptc->get_ct_percent() << "\",\"" <<  ptc->get_Knuckleball_percent()<<"\""<< endl;
		}
	}

	///Sort By Team//
	std::sort(mlbRoster.begin(),mlbRoster.end(),mlbPlayer::SortTeam());
	cout << "Creating Team vs Pitcher CSV..." << endl;
	BvPToday << "\"Salary\",\"Name\",\"Team\",\"Hand\",\"BatOrder\",\"K%\",\"wOBA\",\"HomeRuns\",\"Games\",\"wSB\",\"Position\",\"Pitcher\",\"PitcherHand\",\"BatterFB%\",\"wRC\",\"rSB_ifCatcher\",\"Other Data\""  << endl;
	for(std::vector<mlbPlayer>::iterator ptc = mlbRoster.begin(); ptc != mlbRoster.end(); ptc++){
		if( ptc->isStarter() == 1){ //&& ptc->getDKsal() !=0){
			BvPToday << "\"" << ptc->getDKsal() << "\",\"" << ptc->getName() << "\",\"" << ptc->getTeam() << "\",\"" << ptc->getBatLRS() <<
				"\"," << ptc->getBatOrder() <<"\"," << ptc->getStrikeOutPerecent() << "\",\"" << ptc->getSeasonWOBA() << "\",\"" << (float)ptc->getSeasonHR()/(float)ptc->getSeasonGames()<< "\",\""<<
				ptc->getSeasonGames()<< "\",\""<< ptc->get_wSB() << "\",\""<< ptc->getDkPosn()  << "\",\"" <<
				ptc->getStartingPitcher()<< "\",\""<<ptc->getPitcherHand()<< "\",\""<<ptc->get_fbPercent() << "\",\""<<ptc->get_wRC()<<"\",\"";
			if(ptc->get_rSB() <5000){
				BvPToday << ptc->get_rSB() <<"\",\""<< ptc->getDebug()<<"\""  << endl;

			}
			else
				BvPToday << "n/a" << "\",\"" <<"n/a" <<"\"" << endl;
		}
	}

	pitchingToday.close();
	battingToday.close();
}