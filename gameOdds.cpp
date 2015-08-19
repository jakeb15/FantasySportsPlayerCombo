#include "stdafx.h"
#include <iostream>
#include <string>
#include "gameOdds.h"	

gameOdds::gameOdds(){
	 
	HomeTeam = "";
	AwayTeam = "";
	overUnder = 0;
	moneyLine = 0; 

}

void gameOdds::setHomeTeam(string x){
	HomeTeam = x;
}
void gameOdds::setAwayTeam(string x){
	AwayTeam = x;
}
void gameOdds::setOverUnder(float x){
	overUnder = x;
}
void gameOdds::setMoneyLine(int x){
	moneyLine = x;
}
string gameOdds::getHomeTeam(){
	return HomeTeam;
}
string gameOdds::getAwayTeam(){
	return AwayTeam;
}
float gameOdds::getOverUnder(){
	return overUnder;
}
int gameOdds::getMoneyLine(){
	return moneyLine;
}