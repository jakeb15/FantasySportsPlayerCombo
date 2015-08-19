#include "stdafx.h"
#include <iostream>
#include <string>
#include "BallPark.h"	

BallPark::BallPark(){
	 
	year = 0;
	team = "";
	base1L= 0;
	base1R =0;
	base2L =0;
	base2R =0;
	base3L =0;
	base3R =0;
	HRL =0;
	HRR =0;

}


int BallPark::getYear(){
	return year;
}
string BallPark::getTeam(){
	return team;
}
int BallPark::getBase1L(){
	return base1L;
}
int BallPark::getBase1R(){
	return base1R;
}
int BallPark::getBase2L(){
	return base2L;
}
int BallPark::getBase2R(){
	return base2R;
}
int BallPark::getBase3L(){
	return base3L;
}
int BallPark::getBase3R(){
	return base3R;
}
int BallPark::getHRL(){
	return HRL;
}
int BallPark::getHRR(){
	return HRR;
}
void BallPark::setYear(int x){
	year = x;
}
void BallPark::setTeam(string x){
	team = x;
}
void BallPark::setBase1L(int x){
	base1L = x;
}
void BallPark::setBase1R(int x){
	base1R = x;
}
void BallPark::setBase2L(int x){
	base2L = x;
}
void BallPark::setBase2R(int x){
	base2R = x;
}
void BallPark::setBase3L(int x){
	base3L = x;
}
void BallPark::setBase3R(int x){
	base3R = x;
}
void BallPark::setHRL(int x){
	HRL = x;
}
void BallPark::setHRR(int x){
	HRR = x;
}