
#include "stdafx.h"
#include <iostream>
#include <string>
#include "Catcher.h"	

Catcher::Catcher(){
	 
	name = "";
	team = "";
	gamesPlayed = 0;
	gamesStarted = 0;
	Tot_innings = 0;
	stolenBases = 0;
	caughtStealing = 0;
	rSB = 0;
}

void Catcher::setName(string x){
	name = x;
}
	
void Catcher::setTeam(string x){
	team = x;
}

void Catcher::setGamesPlayed(int x){
	gamesPlayed = x;
}

void Catcher::setGameStarted(int x){
	gamesStarted = x; 
}

void Catcher::setTotInnings(float x){
	Tot_innings = x;
}

void Catcher::setStolenBases(int x){
	stolenBases = x;
}

void Catcher::setCaughtStealing(int x){
	caughtStealing = x;
}

string Catcher::getName(){
	return name;
}

string Catcher::getTeam(){
	return team;
}
	
int Catcher::getGamesPlayed(){
	return gamesPlayed;
}
	
int Catcher::getGamesStarted(){
	return gamesStarted;
}
float Catcher::getTotInnings(){
	return Tot_innings;
}

int Catcher::getStolenbases(){
	return stolenBases;
}

int Catcher::getCaughtStealing(){
	return caughtStealing;
}

int Catcher::get_rSB(){
	return rSB;
}
void Catcher::set_rSB(int x){
	rSB = x;
}