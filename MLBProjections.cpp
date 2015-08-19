#include "stdafx.h"
#include "MLBProjections.h"

///Items that need to be adjusted.... Catcher games should be greater than half season played games so that The dominate catcher is accounted.
// Catcher File needs to be updated weekly
// MLBPlayerRoster needs to be updated weekly
// Odds needs to be updated daily
// Daily Pts needs to be up to date for hotstreak pts
// DraftKings Player Salary...


//

void CalcPlayerProjections(vector<mlbPlayer> x, vector<BallPark> y){
	// pitcher ERA vs team if era > 3 +1 if era less than 3 -1 ect..
	// Team add points up and see what team is most +/-
	// odds if dog -1 if favorite +1 if o/u > 8 +1 else - 1
	// series score
	// road trip length
	// night/day

	vector<PlayerInfo> playerLU = LineUpData("DKroster818"); // LINE UP FILE
	vector<Catcher> CatcherMLB = CatcherStats();
	vector<Pitcher> PitcherMLB = PitcherStats();
	vector<Pitcher> PitcherFIX = PitcherTeamFIX();
	vector<Pitcher> isPitching;
	vector<mlbPlayer> playerHands = BatterHand();
	vector<mlbPlayer> mlbRoster = MLBPlayerRoster();
	vector<mlbPlayer> TeamFix = MLBPlayerRosterTT();
	vector<gameOdds> OddsIN = LoadGameOdds();
	vector<mlbPlayer> PlayersIN = x; //BvpInfo
	vector<mlbPlayer> probablePitcher;
	vector<Pitcher> CloserPitcher;
	vector<BallPark> ParkIN = y;
	ofstream myFile;
	ofstream pitchingToday;
	vector<mlbPlayer> Starters = StartingPlayer();
	bool compFlag = false;
	bool pitcherInFlag = false;

	string WindyOUT = "";
	string WindyIN = "";

	myFile.open("C:\\progData\\Projection2",std::ofstream::out );
	pitchingToday.open("C:\\progData\\Pitching.csv",std::ofstream::out);

	/*//testing vector
	cout << "Testing Vector info..." << endl;
	for(std::vector<mlbPlayer>::iterator LU = playerHands.begin(); LU != playerHands.end(); LU++){
		cout << LU->getName() << " " << LU->getBatLRS() << endl;
	}
	*/

	//Sets all Players to not starting. 
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		LU->setStarter(0);
		for(std::vector<mlbPlayer>::iterator hands = playerHands.begin(); hands != playerHands.end(); hands++){
			if(LU->getName().compare(hands->getName())==0){
				LU->setBatLRS(hands->getBatLRS());
			}
		}
	}

	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<mlbPlayer>::iterator str = Starters.begin(); str != Starters.end(); str++){
			if(LU->getLastName().compare(str->getLastName())==0 && LU->getTeam().compare(str->getTeam())==0){
				LU->setStarter(1);
				LU->setBatOrder(str->getBatOrder());
			}
		}
	}

	/////////////////////Attach TeamFIx to Pitchers...//////
	cout << "ReAttach Pitcher Team Data...." << endl;
	for(std::vector<Pitcher>::iterator LU = PitcherMLB.begin(); LU != PitcherMLB.end(); LU++){
		for(std::vector<Pitcher>::iterator TF = PitcherFIX.begin(); TF != PitcherFIX.end(); TF++){
			if(LU->getName().compare(TF->getName())==0){
				LU->setTeam(TF->getTeam());
			}
		}
	}

	//gets probable pitchers from bvp and puts them into its own vector called probable pitchers
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

	

	//////testing pitcher and attaching to probable pitchers
	cout << "displaying pitcher stats" <<endl;
	for(std::vector<Pitcher>::iterator ptc = PitcherMLB.begin(); ptc != PitcherMLB.end(); ptc++){
		for(std::vector<mlbPlayer>::iterator ttt = probablePitcher.begin(); ttt != probablePitcher.end(); ttt++){
			if(ptc->getName().compare(ttt->getStartingPitcher())==0){
				ptc->setPitchingHand(ttt->getPitcherHand());
				isPitching.push_back(*ptc);
			}
			
		}
		if(ptc->getSaves() > 0 || ptc->getGamesPlayed() > ptc->getGamesStarted()){
				CloserPitcher.push_back(*ptc);
			}
	}
	
	
	myFile << "----------------------------Batters STARTING-------------------------------------------------------------------" << endl;
	/////DK points from last 3 games ----> looking for hot streaks
	int zz = 1;

	///display odds to make sure they are right
	for(std::vector<gameOdds>::iterator odds = OddsIN.begin(); odds != OddsIN.end(); odds++){
		odds->setAwayTeam(changeTeam(odds->getAwayTeam()));
		odds->setHomeTeam(changeTeam(odds->getHomeTeam()));
		cout << odds->getAwayTeam() << " @ " << odds->getHomeTeam() << " O/U: "<< odds->getOverUnder() <<" ML: " <<odds->getMoneyLine() << endl;
	}


	//increment based on date takes 4 games //// Difference should always be 3 <--- ex 425  428 || 428 431
	for(int x = 584; x<=587;x++){
			vector<mlbPlayer> tempMLB = parseData(x);
			for(std::vector<mlbPlayer>::iterator LU = PlayersIN.begin(); LU != PlayersIN.end(); LU++){
				for(std::vector<mlbPlayer>::iterator TLU = tempMLB.begin(); TLU != tempMLB.end(); TLU++){
					if(LU->getName().compare(TLU->getName())==0){
						if(zz==1){
							LU->setGame1Pts(TLU->getDkpts());
						}
						else if(zz == 2){
							if(TLU->getBatOrder() > 0){
								LU->setBatOrder(TLU->getBatOrder());
							}
							LU->setGame2Pts(TLU->getDkpts());
						}
						else if(zz == 3){
							if(TLU->getBatOrder() > 0){
								LU->setBatOrder(TLU->getBatOrder());
							}
							LU->setGame3Pts(TLU->getDkpts());
						}
						else if(zz == 4){
							if(TLU->getBatOrder() > 0){
								LU->setBatOrder(TLU->getBatOrder());
							}
							LU->setGame4Pts(TLU->getDkpts());
						}
						else{
							cout << "Error @ zz assign dk points";
						}
					}
				}
			}
			zz++;
	}
	cout << "roster->>>geting HS" <<endl;
	zz = 1;
	for(int x = 584; x<=587;x++){
			vector<mlbPlayer> tempMLB = parseData(x);
			for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
				for(std::vector<mlbPlayer>::iterator TLU = tempMLB.begin(); TLU != tempMLB.end(); TLU++){
					if(LU->getName().compare(TLU->getName())==0){
						if(zz==1){
							LU->setGame1Pts(TLU->getDkpts());
						}
						else if(zz == 2){
							LU->setGame2Pts(TLU->getDkpts());
						}
						else if(zz == 3){
							LU->setGame3Pts(TLU->getDkpts());
						}
						else if(zz == 4){
							LU->setGame4Pts(TLU->getDkpts());
						}
						else if(zz==5){
							LU->setFinalPts(TLU->getDkpts());
							//cout << TLU->getDkpts() <<endl;
						}
						else{
							cout << "Error @ zz assign dk points";
						}
					}
				}
			}
			zz++;
	}

		//////////////////////////////////////Creating Player Roster///////////////////////////////////////////////////////////////////
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<mlbPlayer>::iterator BvP = PlayersIN.begin(); BvP != PlayersIN.end(); BvP++){
			if(LU->getName().compare(BvP->getName())==0){
				LU->setAtBats(BvP->getAtBats());
				LU->setAVG(BvP->getAVG());

				if(LU->getBatLRS().compare("")==0)
					LU->setBatLRS(BvP->getBatLRS());

				LU->setBatOrder(BvP->getBatOrder());
				LU->setBB(BvP->getBB());
				LU->setBvP(BvP->getBvP());
				LU->setCS(BvP->getCS());
				LU->setDate(BvP->getDate());
				LU->setDkPosn(BvP->getDkPosn());
				LU->setDkpts(BvP->getDkpts());
				LU->setDoubles(BvP->getDoubles());
				LU->setGame1Pts(BvP->getGame1Pts());
				LU->setGame2Pts(BvP->getGame2Pts());
				LU->setGame3Pts(BvP->getGame3Pts());
				LU->setGame4Pts(BvP->getGame4Pts());
				LU->setGID(BvP->getGID());
				LU->setHits(BvP->getHits());
				LU->setHomeAway(BvP->getHomeAway());
				LU->setHomeRuns(BvP->getHomeRuns());
				LU->setOBP(BvP->getOBP());
				LU->setOppt(BvP->getOppt());
				LU->setOpptRuns(BvP->getOpptRuns());
				LU->setOPS(BvP->getOPS());
				LU->setSLG(BvP->getSLG());
				LU->setSO(BvP->getSO());
				LU->setTeam(BvP->getTeam());
				LU->setTeamRuns(BvP->getTeamRuns());
				LU->setTriples(BvP->getTriples());
				//LU->setPitcherHand(BvP->getPitcherHand());
				//LU->setStartingPitcher(BvP->getStartingPitcher());
			}
		}
	}
	/////////////////////////////ReAttach Team Data...///////////////////////////////////////////
	cout << "ReAttach Team Data...." << endl;
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<mlbPlayer>::iterator TF = TeamFix.begin(); TF != TeamFix.end(); TF++){
			if(LU->getName().compare(TF->getName())==0){
				LU->setTeam(TF->getTeam());
			}
		}
	}


	////////////////Attach Salary from Line up export file taken from DraftKings /////////////////
	cout << "Getting and Attaching Player Salary/Positions..." <<endl;
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		for(std::vector<PlayerInfo>::iterator PI = playerLU.begin(); PI != playerLU.end(); PI++){
			if(PI->getName().compare(LU->getName())==0){
				LU->setDKsal(PI->getSalary());
				LU->setDkPosn(PI->getPos());
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	/////Assigns a H/A to each Player wont Assign anything if they are not playing or in the odds table
	cout << "Assigning Home/Away to players...." <<endl;
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		//assign H/A
		for(std::vector<gameOdds>::iterator odds = OddsIN.begin(); odds != OddsIN.end(); odds++){
			if(LU->getTeam().compare(odds->getAwayTeam())==0){
				LU->setHomeAway("A");
				LU->setOppt(odds->getHomeTeam());
			}
			else if(LU->getTeam().compare(odds->getHomeTeam())==0){
				LU->setHomeAway("H");
				LU->setOppt(odds->getAwayTeam());
			}
		}
	}

	//////////////////////////////////////Assigning Pitchers an Opponent///////////////////////
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
		}
	}

	/////////////////Pitcher Projection/////////////////////////////////////////////
	/* Cycle through all Mlb players and if they are playing said pitcher do some stuff 
	*/
	cout << "Calculating Pitcher Projections" << endl;
	for(std::vector<Pitcher>::iterator PL = isPitching.begin(); PL != isPitching.end(); PL++){
		for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
			
			if(LU->getOppt().compare(PL->getTeam())==0){
				LU->setStartingPitcher(PL->getName());
			}
			
			//If Batter is starting and playing against pitcher
			if(LU->getOppt().compare(PL->getTeam())==0 && LU->isStarter() == 1){
				//batter k%  
				if(LU->getStrikeOutPerecent() > 20){
					PL->setKprojection(PL->getKprojection() + 1);
				}
				//Batter OBP
				if(LU->getSeasonOBP() < .32){
					PL->set_OBP_Projection(PL->get_OBP_Projection() + 1);
				}
				if(LU->getSeasonOPS() < .730){
					PL->set_OPS_Projection(PL->get_OPS_Projection() + 1);
				}
				if(LU->getSeasonWOBA() < .320){
					PL->set_WOBA_Projection(PL->get_WOBA_Projection() + 1);
				}
				PL->setProjection(PL->getProjection() + 1);
			}
		}
	}


	//////////////////////////////////All Roster Start Projection /////////////////////////////////////////////////////
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		if(LU->getHomeAway().compare("H")!=0 && LU->getHomeAway().compare("A")!=0){
			LU->setProjectionScore(LU->getProjectionScore() - 200);
			// not playing today....
		}

		//spread and over under
		//Bring in Odds Vector
		for(std::vector<gameOdds>::iterator odds = OddsIN.begin(); odds != OddsIN.end(); odds++){
			
			if(odds->getAwayTeam().compare(LU->getTeam())==0 || (odds->getHomeTeam().compare(LU->getTeam())==0)){
				// if at home and money line is better than -150 + 2
				if(LU->getTeam().compare(odds->getHomeTeam())==0 && odds->getMoneyLine()<-150){
					LU->setDebug(LU->getDebug() + "*homeFav+2*");
					LU->setProjectionScore(LU->getProjectionScore() + 2);
				}
				// if away and favorite
				else if (LU->getTeam().compare(odds->getAwayTeam())==0 && odds->getMoneyLine()>110){
					LU->setDebug(LU->getDebug() + "*AwayFav-1*");
					LU->setProjectionScore(LU->getProjectionScore() - 1);
				}

				//if home dog by 
				if(LU->getTeam().compare(odds->getHomeTeam())==0 && odds->getMoneyLine() > 135){
					LU->setDebug(LU->getDebug() + "*homeDawg+2*");
					LU->setProjectionScore(LU->getProjectionScore() + 2);
				}

				//over/under
				if((LU->getTeam().compare(odds->getAwayTeam())==0 || LU->getTeam().compare(LU->getHomeAway())==0) && (odds->getOverUnder() > 8) ){
					LU->setDebug(LU->getDebug() + "*O8+2*");
					LU->setProjectionScore(LU->getProjectionScore() + 2);
				}
				else if((LU->getTeam().compare(odds->getAwayTeam())==0 || LU->getTeam().compare(LU->getHomeAway())==0) && (odds->getOverUnder() < 7) ){
					LU->setDebug(LU->getDebug() + "*U7-2*");
					LU->setProjectionScore(LU->getProjectionScore() - 2);
				}
				else{
					LU->setDebug(LU->getDebug() + "O/U+0");
				}

			}

		}//End Odds

		//Pitcher vs Batter 
		for(std::vector<Pitcher>::iterator ptc = isPitching.begin(); ptc != isPitching.end(); ptc++){
			if(LU->getOppt().compare(ptc->getTeam())==0){
				LU->setPitcherHand(ptc->getPitchingHand());


				// Pitcher Hand Vs Batting Hand//////////////////////////////////////////////////////////////
				if(LU->getBatLRS().compare(ptc->getPitchingHand())!=0 && LU->getBatLRS().compare("")!= 0){
					LU->setProjectionScore(LU->getProjectionScore()+1);
					LU->setDebug(LU->getDebug() + "*BHvPH+1*");
				}
				else if(LU->getBatLRS().compare(ptc->getPitchingHand())==0 && LU->getBatLRS().compare("")!=0){
					LU->setProjectionScore(LU->getProjectionScore()-1);
					LU->setDebug(LU->getDebug() + "*BHvPH-1*");
				}
				else if(LU->getBatLRS().compare("")!= 0){
					LU->setProjectionScore(LU->getProjectionScore()+1);
					LU->setDebug(LU->getDebug() + "*BHvPHisSwitch+1*");
				}
				////////////////////////////////////////////////////////////////////////////////////////////

				/// groundBall Pitcher vs GroundBall Batter//////////////////////////////////////
				if(ptc->get_gbPercent() > 50 && LU->get_gbPercent() > 50){
					LU->setProjectionScore(LU->getProjectionScore() - 4);
					LU->setDebug(LU->getDebug() + "GroundBallBatvsGBpitcher");
				}

				if(ptc->get_gbPercent() > 50 && LU->get_fbPercent() > 50){
					LU->setProjectionScore(LU->getProjectionScore() + 1);
					LU->setDebug(LU->getDebug() + "flyBallbattervsGbPitcher");
				}
				/////////////////////////////////////////////////////////////////////////////


				///////Great Control Batter vs Great strike zone Control batter && Bad Strike zone Pitcher/////
				if(ptc->get_KpBB() > 5 && LU->get_BBpK() > .85){
					LU->setProjectionScore(LU->getProjectionScore() + 1);
					LU->setDebug(LU->getDebug() + "gcPvs.gcB");
				}

				if(ptc->get_KpBB() < 3 && LU->get_BBpK() > .85){
					LU->setProjectionScore(LU->getProjectionScore() + 1);
					LU->setDebug(LU->getDebug() + "bcPvs.gcB");
				}
				////////////////////////////////////////////////////////////////////////////////////////////////



				// home run to fly ball % of pitcher
				if(ptc->getHRlFB() > 10 && LU->getSeasonHRrFlyball() > 14){
					LU->setProjectionScore(LU->getProjectionScore() + 2);
					LU->setDebug(LU->getDebug() + "ptchrFB/HR+2");
				}
				else if(ptc->getHRlFB() > 10 && LU->getSeasonHRrFlyball() > 10){
					LU->setProjectionScore(LU->getProjectionScore() + 1);
					LU->setDebug(LU->getDebug() + "ptchrFB/HR+1");
				}

				///Batter vs Pitcher ERA
				if(ptc->getERA() > 4){
					LU->setProjectionScore(LU->getProjectionScore() + 1);
					LU->setDebug(LU->getDebug() + "ERA+1");
				}

				else if(ptc->getERA() < 3){
					LU->setProjectionScore(LU->getProjectionScore() - 1);
					LU->setDebug(LU->getDebug() + "ERA-1");
				}

				// Batter vs PITCHER FIP
				if(ptc->getFIP() < 3.5){
					LU->setProjectionScore(LU->getProjectionScore() - 1);
					LU->setDebug(LU->getDebug() + "FIP-1");
				}
				else{
					LU->setProjectionScore(LU->getProjectionScore() + 1);
					LU->setDebug(LU->getDebug() + "FIP+1");
				}

				// Batter k% vs Pitcher k%
				if(LU->getStrikeOutPerecent() > 20 && ptc->getKper9() > 8.5){
					LU->setProjectionScore(LU->getProjectionScore() - 2);
					LU->setDebug(LU->getDebug() + "BATvsPtchK%-2");
				}

				// batter BB% vs Pitcher BB/9
				if(LU->getWalkPercent() > 12.5 && LU->get_wSB() > .5 && ptc->getBBper9() > 4){
					LU->setProjectionScore(LU->getProjectionScore() + 2);
					LU->setDebug(LU->getDebug() + "BATvsPtchK%+2");
				}

				// Batter HR vs Pitcher K/O
				if(ptc->getKper9() < 5 && LU->getSeasonOPS() > .800){
					LU->setProjectionScore(LU->getProjectionScore() + 4);
					LU->setDebug(LU->getDebug() + "OPSvsPitcherK/9+4!!");
				}

				
			}
		}
		//Batter Performance


		//wRAA
		if(LU->get_wRAA() > 10 && LU->get_wRAA() < 20){
			LU->setProjectionScore(LU->getProjectionScore() + 1);
			LU->setDebug(LU->getDebug() + "*wRAA+1*");
		}
		else if(LU->get_wRAA() < 0){
			LU->setProjectionScore(LU->getProjectionScore() -1);
			LU->setDebug(LU->getDebug() + "*wRAA-1*");
		}
		else if(LU->get_wRAA() > 20){
			LU->setProjectionScore(LU->getProjectionScore() +2);
			LU->setDebug(LU->getDebug() + "*wRAA+2*");
		}

		if(LU->getAtBats() > 20 && LU->getOPS() > .900 && LU->getSB() > 1){
			LU->setProjectionScore(LU->getProjectionScore() + 3);
			LU->setDebug(LU->getDebug() + "*BvP+3*");
		}
		else if(LU->getAtBats() > 10 && LU->getOPS() > .800 && LU->getSB() > 0){
			LU->setProjectionScore(LU->getProjectionScore() + 2);
			LU->setDebug(LU->getDebug() + "*BvP+2*");
		}
		else if(LU->getAtBats() > 10 && LU->getOPS() > 1 && LU->getAVG() > .330){
			LU->setProjectionScore(LU->getProjectionScore() + 2);
			LU->setDebug(LU->getDebug() + "*BvP+2*");
		}
		else if(LU->getAtBats() > 10 && LU->getAVG() < .250){
			LU->setProjectionScore(LU->getProjectionScore() -1);
			LU->setDebug(LU->getDebug() + "*BvP-1*");
		}
		else if(LU->getAtBats() > 20 && LU->getAVG() < .200){
			LU->setProjectionScore(LU->getProjectionScore() -2);
			LU->setDebug(LU->getDebug() + "*BvP-2*");
		}
		else if(LU->getAtBats() == 0){
			LU->setProjectionScore(LU->getProjectionScore() -1);
			LU->setDebug(LU->getDebug() + "*BvP-1*");
		}

		//Stealing bases....
	
		if((LU->getSeasonGames() > 0) && (LU->getSeasonSB() > 0)){
			bool stealpts = false;

			if((LU->getSeasonGames()/LU->getSeasonSB())<3){
				LU->setProjectionScore(LU->getProjectionScore() + 2);
				LU->setDebug(LU->getDebug() + "*steals+2*");
				stealpts = true;
			}
			else if((LU->getSeasonGames()/LU->getSeasonSB())<4){
				LU->setProjectionScore(LU->getProjectionScore() +1);
				LU->setDebug(LU->getDebug() + "*steals+1*");
				stealpts = true;
			}
			
			//using wSB
			if(LU->get_wSB() > .9){
				LU->setProjectionScore(LU->getProjectionScore() +1);
				LU->setDebug(LU->getDebug() + "*wSB+1*");
			}
			else if(LU->get_wSB() < -.5){
				LU->setProjectionScore(LU->getProjectionScore() - 1);
				LU->setDebug(LU->getDebug() + "*wSB-1*");
			}
			
			/// Bonus against certain Catchers... if Player steals and catcher has caught 15+ games do... if sb/cs is > 2 catcher is bad else catcher is good
			for(std::vector<Catcher>::iterator ctch = CatcherMLB.begin(); ctch != CatcherMLB.end(); ctch++){
				if(LU->getOppt().compare(ctch->getTeam())==0 && ctch->getGamesPlayed() > 15 && stealpts == true){
					if((ctch->getStolenbases() / ctch->getCaughtStealing() > 2)){
						LU->setProjectionScore(LU->getProjectionScore() +1);
						LU->setDebug(LU->getDebug() + "*badCatcher+1*");
					}
					else{
						LU->setProjectionScore(LU->getProjectionScore() - 1);
						LU->setDebug(LU->getDebug() + "*GoodCatcher-1*");
					}
				}
			}
		
		}

		// strikeouts and walks %
		if(LU->getStrikeOutPerecent() < 14){
			LU->setProjectionScore(LU->getProjectionScore() + 1);
			LU->setDebug(LU->getDebug() + "*SOu13%+1*");
		}
		else if(LU->getStrikeOutPerecent() > 20){
			LU->setProjectionScore(LU->getProjectionScore() - 1);
			LU->setDebug(LU->getDebug() + "*SOo25%-1*");
		}
		else{
			LU->setProjectionScore(LU->getProjectionScore() + 0);
			LU->setDebug(LU->getDebug() + "*SO%onPar+0*");
		}

		// Walks
		if(LU->getWalkPercent() > 12){
			LU->setProjectionScore(LU->getProjectionScore() + 1);
			LU->setDebug(LU->getDebug() + "*Walko12%+1*");
		}
		else if(LU->getWalkPercent() < 7){
			LU->setProjectionScore(LU->getProjectionScore() - 1);
			LU->setDebug(LU->getDebug() + "*Walku7%-1*");
		}
		else{
			LU->setProjectionScore(LU->getProjectionScore() + 0);
			LU->setDebug(LU->getDebug() + "*walk%Par+0*");
		}

		//BvP OPS
		if(LU->getOPS() > 1){
			LU->setProjectionScore(LU->getProjectionScore() +1);
			LU->setDebug(LU->getDebug() + "*OPS+1*");
		}

		//WOBA
		if(LU->getSeasonWOBA() > .410){
			LU->setProjectionScore(LU->getProjectionScore() +3);
			LU->setDebug(LU->getDebug() + "*Woba+3*");
		}
		else if(LU->getSeasonWOBA() > .375){
			LU->setProjectionScore(LU->getProjectionScore() +2);
			LU->setDebug(LU->getDebug() + "*Woba+2*");
		}
		else if(LU->getSeasonWOBA() > .330){
			LU->setProjectionScore(LU->getProjectionScore() + 1);
			LU->setDebug(LU->getDebug() + "*Woba+1*");
		}
		else{
			LU->setProjectionScore(LU->getProjectionScore() - 1);
			LU->setDebug(LU->getDebug() + "*Woba-1*");
		}

		//HomeRuns
		if(LU->getSeasonGames() > 0 && LU->getSeasonHR() > 0){
			if(LU->getSeasonGames() / LU->getSeasonHR() < 5){
				LU->setProjectionScore(LU->getProjectionScore() + 1);
				LU->setDebug(LU->getDebug() + "HomeRuns+1*");
			}
		}

		if(LU->getSeasonHRrFlyball() > 14){
			LU->setProjectionScore(LU->getProjectionScore() + 1);
			LU->setDebug(LU->getDebug() + "hr/fb+1*");
		}
		else if(LU->getSeasonHRrFlyball() < 9){
			LU->setProjectionScore(LU->getProjectionScore() - 1);
			LU->setDebug(LU->getDebug() + "hr/fb-1*");
		}
		else{
			LU->setDebug(LU->getDebug() + "hr/fb+0*");
		}

		/*////HotStreak Performance
		if(LU->getGame1Pts() > 10   && LU->getGame2Pts() > 10  && LU->getGame3Pts() > 10  && LU->getGame4Pts() > 10){
			LU->setProjectionScore(LU->getProjectionScore() + 3);
			LU->setDebug(LU->getDebug() + "*FIRE+3*");
		}
		else if(LU->getGame1Pts() <= 4   && LU->getGame2Pts() <= 4  && LU->getGame3Pts() <= 4 && LU->getGame4Pts() <= 4){
			LU->setProjectionScore(LU->getProjectionScore() - 5);
			LU->setDebug(LU->getDebug() + "*COLD-5*");
		}
		else if(LU->getGame3Pts() > 10 && LU->getGame4Pts() > 10){
			LU->setProjectionScore(LU->getProjectionScore() + 1);
			LU->setDebug(LU->getDebug() + "*HeatingUP+1*");
		}
		else if(LU->getGame2Pts() > 10 && LU->getGame3Pts() > 10 && LU->getGame4Pts() > 10){
			LU->setProjectionScore(LU->getProjectionScore() + 2);
			LU->setDebug(LU->getDebug() + "*HOT!+2*");
		}
		else if(LU->getGame1Pts() < -100 && LU->getGame2Pts() < -100 && LU->getGame3Pts() < -100 && LU->getGame4Pts() < -100){
			LU->setProjectionScore(LU->getProjectionScore() -2000);
			LU->setDebug(LU->getDebug() + "*HS+-2000NotPlaying*");
		}
		*/
		//pt for posible extra bat if home is up
		if(LU->getHomeAway().compare("A")==0){
			LU->setProjectionScore(LU->getProjectionScore()+1);
			LU->setDebug(LU->getDebug() + "*ExBat+1*");
		}


		if(LU->getTeam().compare(WindyOUT)==0){
			LU->setProjectionScore(LU->getProjectionScore()+1);
			LU->setDebug(LU->getDebug() + "*WINDY+1*");
		}

		if(LU->getTeam().compare(WindyIN)==0){
			LU->setProjectionScore(LU->getProjectionScore()-1);
			LU->setDebug(LU->getDebug() + "*WINDY-1*");
		}

		//Factor Age
		if(LU->getAGE() > 31){
			LU->setProjectionScore(LU->getProjectionScore()-1);
			LU->setDebug(LU->getDebug() + "*OLD-1*");
		}

		if(LU->getAGE() > 21 && LU->getAGE() < 27){
			LU->setProjectionScore(LU->getProjectionScore()+1);
			LU->setDebug(LU->getDebug() + "*Prime+1*");
		}

		if(LU->getAGE() < 28 && LU->get_wSB() > .9){
			LU->setProjectionScore(LU->getProjectionScore()+1);
			LU->setDebug(LU->getDebug() + "*sbPrime+1*");
		}

		//Park info
		for(std::vector<BallPark>::iterator BP = ParkIN.begin(); BP != ParkIN.end(); BP++){
			if(LU->getHomeAway().compare("H")==0 && LU->getTeam().compare(BP->getTeam())==0){
				if(LU->getBatLRS().compare("R")==0){
					if( BP->getBase3R() > 105 || BP->getHRR() >105){
						LU->setProjectionScore(LU->getProjectionScore()+1);
						LU->setDebug(LU->getDebug() + "*hittersPark+1*");
					}
					else if(BP->getBase3R() < 97 || BP->getHRR() >97){
						LU->setProjectionScore(LU->getProjectionScore()-1);
						LU->setDebug(LU->getDebug() + "*BadPark-1*");
					}
				}
				else if(LU->getBatLRS().compare("L")==0){
					if( BP->getBase3L() > 105 || BP->getHRL() >105){
						LU->setProjectionScore(LU->getProjectionScore()+1);
						LU->setDebug(LU->getDebug() + "*hittersPark+1*");
					}
					else if(BP->getBase3L() < 97 || BP->getHRL() >97){
						LU->setDebug(LU->getDebug() + "*badPark-1*");
						LU->setProjectionScore(LU->getProjectionScore()-1);
					}
				}
				
			}
			else if(LU->getHomeAway().compare("A")==0 && LU->getOppt().compare(BP->getTeam())==0){
					if(LU->getBatLRS().compare("R")==0){
						if( BP->getBase3R() > 105 || BP->getHRR() >105){
							LU->setProjectionScore(LU->getProjectionScore()+1);
							LU->setDebug(LU->getDebug() + "*hittersPark+1*");
						}
						else if(BP->getBase3R() < 97 || BP->getHRR() >97){
							LU->setProjectionScore(LU->getProjectionScore()-1);
							LU->setDebug(LU->getDebug() + "*BadPark-1*");
						}
					}

					else if(LU->getBatLRS().compare("L")==0){
						if( BP->getBase3L() > 105 || BP->getHRL() >105){
							LU->setProjectionScore(LU->getProjectionScore()+1);
							LU->setDebug(LU->getDebug() + "*hittersPark+1*");
						}
						else if(BP->getBase3L() < 97 || BP->getHRL() >97){
							LU->setDebug(LU->getDebug() + "*BadPark-1*");
							LU->setProjectionScore(LU->getProjectionScore()-1);
						}
					}
					else{
						LU->setDebug(LU->getDebug() + "*switchHitter+1*");
						LU->setProjectionScore(LU->getProjectionScore()+1);
					}
			}
		}

	}



	// Sorts Player Vector by Highest Projection score To Lowest
	//std::sort(mlbRoster.begin(), mlbRoster.end(),mlbPlayer::SortPosition());
	std::sort(mlbRoster.begin(),mlbRoster.end(),mlbPlayer::compareMyDataFunctor());

	/// Batting OUTPUT
	for(std::vector<mlbPlayer>::iterator LU = mlbRoster.begin(); LU != mlbRoster.end(); LU++){
		//if(LU->getTeam().compare("MIL")==0 ||LU->getTeam().compare("TOR")==0||LU->getTeam().compare("CWS")==0 )
		if(LU->getDkPosn().compare("SP")!=0 && LU->getDkPosn().compare("RP")!=0){ 
			cout <<LU->isStarter() <<" " << LU->getLastName() << " " << LU->getTeam() << " " << LU->getOppt() << " " << LU->getBatLRS()  << " Pitcher: " << LU->getStartingPitcher() << " " << LU->getPitcherHand() << " "<<LU->get_fbPercent() << " " <<LU->get_gbPercent() << endl;  //<< LU->getTeam() <<  " " <<LU->getProjectionScore()  << " " << LU->getDebug() << " " << LU->getDKsal() << " " <<LU->getDkPosn() << " HR:" << LU->getSeasonHR() << " OPS: " << LU->getOPS()<<endl;
			if(LU->getDKsal() != 0){ // IF salary is 0 they are not elgible to be picked in the lineup
				myFile << LU->getDKsal() << " " << LU->getDkPosn() << " "<< LU->getProjectionScore() << " "<< LU->getName() << " " << LU->getTeam() <<  LU->getDebug() << " fb%:"<<LU->get_fbPercent() << " gb%:" <<LU->get_gbPercent()<< " BB/K:" << LU->get_BBpK() << " hand:" <<LU->getBatLRS() << endl; 
				myFile <<" Pitcher:" << LU->getStartingPitcher()<< " hand:" << LU->getPitcherHand()<< " Age:" << LU->getAGE() << endl;
				myFile << "------------------------------------------------------------------------------------" << endl;
			}
		}
	}



	// is pitching today
	 myFile << "----------------------------Probable Starting Pitchers-------------------------------------------------------------------" << endl;
	cout << "**************we be pitching(((((((((((("<< endl;
	pitchingToday << "\"Name\", \"Team\", \"K/9\", \"ERA\",\"FIP\",\"BABIP\",\"GB%\",\"FB%\",\"K/B\",\"Opponent\"" << endl;
	for(std::vector<Pitcher>::iterator ptc = isPitching.begin(); ptc != isPitching.end(); ptc++){
		cout << ptc->getName() << " " << ptc->getERA() << " " << ptc->getTeam() << " " << ptc->getKper9() << endl;
		myFile << ptc->getName() << " " <<ptc->getTeam() << " K/9|| " << ptc->getKper9() << " ERA " << ptc->getERA() << " FIP " << ptc->getFIP() << " BABIP " << ptc->getBABIP() << " Kprojection:" << ptc->getKprojection() << " WOBA: " << ptc->get_WOBA_Projection() << " OPS: "<<ptc->get_OPS_Projection() << " OBP: " << ptc->get_OBP_Projection() << " Projection: " << ptc->getProjection()<< " gb%:" << ptc->get_gbPercent() << " fb%:" << ptc->get_fbPercent() << " K/BB: "<< ptc->get_KpBB() << endl;
		pitchingToday << "\"" << ptc->getName() << "\",\"" << ptc->getTeam() << "\"," << ptc->getKper9() <<
		"," << ptc->getERA() <<  "," << ptc->getFIP() <<  "," << ptc->getBABIP() <<  "," << ptc->get_gbPercent()
		<<  "," << ptc->get_fbPercent() <<  "," <<  ptc->get_KpBB() <<  "\",\"" << ptc->getOpponent() << "\"" <<endl;
	}
	 myFile << "----------------------------Relieve Pitchers STARTING-------------------------------------------------------------------" << endl;

	cout << "closers........." << endl;
	for(std::vector<Pitcher>::iterator ptc = CloserPitcher.begin(); ptc != CloserPitcher.end(); ptc++){
		myFile << ptc->getName() << " " << ptc->getTeam() << " Saves: " << ptc->getSaves() << " GamesPlayed: " << ptc->getGamesPlayed() << " GameStarted: " << ptc->getGamesStarted() << " ERA " << ptc->getERA() << " k/9: " << ptc->getKper9() << " Projection: " << ptc->getProjection()<<endl;
	}
	 myFile.close();
	 pitchingToday.close();
}