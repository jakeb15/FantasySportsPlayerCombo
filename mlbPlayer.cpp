#include "stdafx.h"
#include <iostream>
#include <string>
#include "mlbPlayer.h"	

mlbPlayer::mlbPlayer(){
	 Date = "";
	 GID =0;
	 MLB_ID =0;
	 Name ="";
	 Starter =0;
	 Batorder=0;
	 DKposn="";
	 DKpts = 0;
	 DKsal = 0;
	 Team ="";
	 Oppt ="";
	 dblhdr=0;
	 TmRuns=0;
	 OppRuns=0;
	 Statline ="";
	 BvP = "";
	 atBats = 0;
	 Hits = 0;
	 base2 = 0;
	 base3 = 0;
	 HomeRuns = 0;
	 RBI = 0;
	 BB = 0;
	 SO = 0;
	 SB = 0;
	 CS = 0;
	 AVG = 0;
	 OBP = 0;
	 SLG = 0;
	 OPS = 0;
	 batLHS = "";
	 homeaway ="";
	 ProjectionScore = 0;
	 pitcherHand = "";
	 debug = "";
	 wOBA = 0;
	seasonAVG = 0;
	seasonOPS = 0;
	seasonOBP = 0;
	seasonWOBA = 0;
	seasonSB = 0;
	seasonCS = 0;
	seasonGames =0;
	FinalPts = 0;
	seasonHomeRuns = 0;
	HRrFlyballs = 0;
	startingPitcher = "";
	strikeOutPerecent = 0;
	walkPercent = 0;
	wSB = 0;
	wRC = 0;
	wRAA = 0;
	LastName = "";
	gbPercent = 0;
	fbPercent = 0;
	BBpK = 0;
	age = 0;
	RE24 =0;
	rSB = 5000;
	fastball_percent = 0;
	curveball_percent = 0;
	slider_percent = 0;
	ChangeUp_percent = 0;
	ct_percent = 0;
	sf_percent = 0;
	Knuckle_percent = 0;
	SB_Projection =0;
}
	
void mlbPlayer::setDate(string d){
	Date = d;
}

string mlbPlayer::getDate(){
	return Date;
}

void mlbPlayer::setGID(int ID){
	GID = ID;
}

int mlbPlayer::getGID(){
	return GID;
}

void mlbPlayer::setMLB_ID(int id){
	MLB_ID = id;
}

int mlbPlayer::getMLB_ID(){
	return MLB_ID;
}

void mlbPlayer::setName(string s){
	Name = s;
}

string mlbPlayer::getName(){
	return Name;
}

void mlbPlayer::setLastName(string name){
	LastName = name;
}
string mlbPlayer::getLastName(){
	return LastName;
}

void mlbPlayer::setStarter(bool x){
	Starter = x;
}

bool mlbPlayer::isStarter(){
	return Starter;
}

void mlbPlayer::setBatOrder(int x){
	Batorder = x;
}

int mlbPlayer::getBatOrder(){
	return Batorder;
}


void mlbPlayer::setDkPosn(string x){
	DKposn = x;
}

string mlbPlayer::getDkPosn(){
	return DKposn;
}

void mlbPlayer::setDkpts(float x){
	DKpts = x;
}

float mlbPlayer::getDkpts(){
	return DKpts;
}

void mlbPlayer::setDKsal(int x){
	DKsal = x;
}

int mlbPlayer::getDKsal(){
	return DKsal;
}
void mlbPlayer::setTeam(string x){
	Team = x;
}
string mlbPlayer::getTeam(){
	return Team;
}
void mlbPlayer::setOppt(string x){
	Oppt = x;
}

string mlbPlayer::getOppt(){
	return Oppt;
}

void mlbPlayer::doubleHeader(bool x){
	dblhdr = x;
}

bool mlbPlayer::isDoubleHeader(){
	return dblhdr;
}

void mlbPlayer::setTeamRuns(int x){
	TmRuns = x;
}
int mlbPlayer::getTeamRuns(){
	return TmRuns;
}

void mlbPlayer::setOpptRuns(int x){
	OppRuns = x;
}
	
int mlbPlayer::getOpptRuns(){
	return OppRuns;
}
void mlbPlayer::setStatLine(string x){
	Statline = x;
}
string mlbPlayer::getStateLine(){
	return Statline;
}
string mlbPlayer::getBvP(){
	return BvP;
}
void mlbPlayer::setBvP(string x){
	BvP = x;
}


void mlbPlayer::setShortBvP(string x){
	shortBvP = x;
}

string mlbPlayer::getShortBvP(){
	return shortBvP;
}

void mlbPlayer::setAtBats(int x){
	atBats = x;
}
int mlbPlayer::getAtBats(){
	return atBats;
}

float mlbPlayer::getProjectionScore(){
	return ProjectionScore;
}
void mlbPlayer::setProjectionScore(float x){
	ProjectionScore =  x;
}

void mlbPlayer::setHits(int x){
	Hits = x;
}
int mlbPlayer::getHits(){
	return Hits;
}
void mlbPlayer::setDoubles(int x){
	base2 = x;
}
int mlbPlayer::getDoubles(){
	return base2;
}
void mlbPlayer::setTriples(int x){
	base3 = x;
}
int mlbPlayer::getTriples(){
	return base3;
}
void mlbPlayer::setHomeRuns(int x){
	HomeRuns = x;
}
int mlbPlayer::getHomeRuns(){
	return HomeRuns;
}
void mlbPlayer::setRBI(int x){
	RBI = x;
}
int mlbPlayer::getRBI(){
	return RBI;
}
void mlbPlayer::setBB(int x){
	BB = x;
}
int mlbPlayer::getBB(){
	return BB;
}
void mlbPlayer::setSO(int x){
	SO = x;
}
int mlbPlayer::getSO(){
	return SO;
}
void mlbPlayer::setSB(int x){
	SB = x;
}
int mlbPlayer::getSB(){
	return SB;
}
void mlbPlayer::setCS(int x){
	CS = x;
}
int mlbPlayer::getCS(){
	return CS;
}
void mlbPlayer::setAVG(float x){
	AVG = x;
}
float mlbPlayer::getAVG(){
	return AVG;
}
void mlbPlayer::setOBP(float x){
	OBP = x;
}
float mlbPlayer::getOBP(){
	return OBP;
}
void mlbPlayer::setSLG(float x){
	SLG = x;
}
float mlbPlayer::getSLG(){
	return SLG;
}
void mlbPlayer::setOPS(float x){
	OPS = x;
}
float mlbPlayer::getOPS(){
	return OPS;
}

void mlbPlayer::setHomeAway(string x){
	homeaway = x;
}

string mlbPlayer::getHomeAway(){
	return homeaway;
}

void mlbPlayer::setBatLRS(string x){
	batLHS = x;
}

string mlbPlayer::getBatLRS(){
	return batLHS;
}

string mlbPlayer::getPitcherHand(){
	return pitcherHand;
}

void mlbPlayer::setPitcherHand(string x){
	pitcherHand = x;
}

void mlbPlayer::setGame1Pts(int x){
	game1Pts = x;
}
int mlbPlayer::getGame1Pts(){
	return game1Pts;
}
void mlbPlayer::setGame2Pts(int x){
	game2Pts = x;
}
int mlbPlayer::getGame2Pts(){
	return game2Pts;
}
void mlbPlayer::setGame3Pts(int x){
	game3Pts = x;
}
int mlbPlayer::getGame3Pts(){
	return game3Pts;
}
void mlbPlayer::setGame4Pts(int x){
	game4Pts = x;
}
int mlbPlayer::getGame4Pts(){
	return game4Pts;
}

string mlbPlayer::getDebug(){
	return debug;
}

void mlbPlayer::setDebug(string x){
	debug = x;
}

void mlbPlayer::setSeasonWOBA(float x){
	wOBA = x;
}
float mlbPlayer::getSeasonWOBA(){
	return wOBA;
}

void mlbPlayer::setSeasonAVG(float x){
	seasonAVG = x;
}
	
float mlbPlayer::getSeasonAVG(){
	return seasonAVG;
}

void mlbPlayer::setSeasonOBP(float x){
	seasonOBP = x;
}

float mlbPlayer::getSeasonOBP(){
	return seasonOBP;
}

void mlbPlayer::setSeasonOPS(float x){
	seasonOPS = x;
}
	
float mlbPlayer::getSeasonOPS(){
	return seasonOPS;
}
void mlbPlayer::setSeasonSB(int x){
	seasonSB = x;
}
void mlbPlayer::setSeasonCS(int x){
   seasonCS = x;
}
int mlbPlayer::getSeasonSB(){
	return seasonSB;
}
int mlbPlayer::getSeasonCS(){
	return seasonCS;
}

void mlbPlayer::setSeasonGames(int x){
	seasonGames = x;
}
int mlbPlayer::getSeasonGames(){
	return seasonGames;
}

int mlbPlayer::getFinalPts(){
	return FinalPts;
}
void mlbPlayer::setFinalPts(int x){
	FinalPts = x;
}

int mlbPlayer::getSeasonHR(){
	return seasonHomeRuns;
}
void mlbPlayer::setSeasonHR(int x){
	seasonHomeRuns = x;
}
float mlbPlayer::getSeasonHRrFlyball(){
	return HRrFlyballs;
}

void mlbPlayer::setSeasonHRrFlyball(float x){
	HRrFlyballs = x;
}

void mlbPlayer::setStartingPitcher(string x){
	startingPitcher = x;
}
string mlbPlayer::getStartingPitcher(){
	return startingPitcher;
}

float mlbPlayer::getWalkPercent(){
	return walkPercent;
}

void mlbPlayer::setWalkPercent(float x){
	walkPercent = x;
}
	
float mlbPlayer::getStrikeOutPerecent(){
	return strikeOutPerecent;
}

void mlbPlayer::setStrikeOutPercent(float x){
	strikeOutPerecent = x;
}

void mlbPlayer::set_wRC(float x){
	wRC = x;
}
float mlbPlayer::get_wRC(){
	return wRC;
}
void mlbPlayer::set_wRAA(float x){
	wRAA = x;
}
float mlbPlayer::get_wRAA(){
	return wRAA;
}
void mlbPlayer::set_wSB(float x){
	wSB = x;
}
float mlbPlayer::get_wSB(){
	return wSB;
}

void mlbPlayer::set_gbPercent(float x){
	gbPercent = x;
}
float mlbPlayer::get_gbPercent(){
	return gbPercent;
}
void mlbPlayer::set_fbPercent(float x){
	fbPercent = x;
}
float mlbPlayer::get_fbPercent(){
	return fbPercent;
}

float mlbPlayer::get_BBpK(){
	return BBpK;
}
void mlbPlayer::set_BBpK(float x){
	BBpK = x;
}

void mlbPlayer::setAGE(int x){
	age = x;
}
int mlbPlayer::getAGE(){
	return age;
}
float mlbPlayer::getRE24(){
	return RE24;
}
void mlbPlayer::setRE24(float x){
	RE24 = x;
}

void mlbPlayer::set_rSB(int x){
	rSB = x;
}

int mlbPlayer::get_rSB(){
	return rSB;
}

float mlbPlayer::get_fastball_percent(){
	return fastball_percent;
}

float mlbPlayer::get_changeup_percent(){
	return ChangeUp_percent;
}

float mlbPlayer::get_curveball_percent(){
	return curveball_percent;
}

float mlbPlayer::get_Knuckleball_percent(){
	return Knuckle_percent;
}

float mlbPlayer::get_ct_percent(){
	return ct_percent;
}

float mlbPlayer::get_SplitFinger_percent(){
	return sf_percent;
}

float mlbPlayer::get_slider_percent(){
	return slider_percent;
}

void mlbPlayer::set_fastball_percent(float x){
	fastball_percent = x;
}
void mlbPlayer::set_changeup_percent(float x){
	ChangeUp_percent = x;
}
void mlbPlayer::set_curveball_percent(float x){
	curveball_percent = x;
}
void mlbPlayer::set_Knuckleball_percent(float x){
	Knuckle_percent = x;
}
void mlbPlayer::set_ct_percent(float x){
	ct_percent = x;
}
void mlbPlayer::set_SplitFinger_percent(float x){
	sf_percent = x;
}
void mlbPlayer::set_slider_percent(float x){
	slider_percent = x;
}

void mlbPlayer::set_SB_Projection(int x){
	SB_Projection = x;
}
int mlbPlayer::get_SB_Projection(){
	return SB_Projection;
}