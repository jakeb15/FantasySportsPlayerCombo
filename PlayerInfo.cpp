#include "stdafx.h"
#include <iostream>
#include <string>
#include "PlayerInfo.h"

using namespace std;

PlayerInfo::PlayerInfo(){
	Name = "";
	Salary = 0;
	matchUP = "";
	AveragePts = 0;
	Pos = "";
	Trigger ="";
	team1 = "";
	team2 = "";
	prevGameData = "";
	atBats = 0;
}

void PlayerInfo::setName(string pName){
	Name = pName;
}

string PlayerInfo::getName(){
	return Name;
}

void PlayerInfo::setSalary(int sal){
	Salary = sal;
}

int PlayerInfo::getSalary(){
	return Salary;
}

void PlayerInfo::setPos(string pPos){
	Pos = pPos;
}

string PlayerInfo::getPos(){
	return Pos;
}

void PlayerInfo::setMatchUP(string match){
	matchUP = match;
}

string PlayerInfo::getMatchUP(){
	return matchUP;
}

void PlayerInfo::setAVGPTS(float avg){
	AveragePts = avg;
}

float PlayerInfo::getAVGPTS(){
	return AveragePts;
}

void PlayerInfo::setTeam1(string teamOne){
	team1 = teamOne;
}
void PlayerInfo::setTeam2(string teamTwo){
	team2 = teamTwo;
}
string PlayerInfo::getTeam1(){
	return team1;
}
string PlayerInfo::getTeam2(){
	return team2;
}

void PlayerInfo::setprevGameData(string s){
	prevGameData = s;
}
string PlayerInfo::getprevGameData(){
	return prevGameData;
}

string PlayerInfo::getBvPinfo(){
	return BvPinfo;
}
void PlayerInfo::setBvPinfo(string x){
	BvPinfo = x;
}

void PlayerInfo::setAtBats(int x){
	atBats = x;
}
int PlayerInfo::getAtBats(){
	return atBats;
}