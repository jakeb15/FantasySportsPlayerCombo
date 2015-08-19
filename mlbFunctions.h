#include "mlbPlayer.h"
#include "BallPark.h"
#include "gameOdds.h"
#include "PlayerInfo.h"
#include "catcher.h"
#include "Pitcher.h"
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <vector>
#include <iomanip>
#include <fstream>


using namespace std;

vector<mlbPlayer> parseData(int dateXXXX);// the int x will be used to determin which spot the data is saved to
vector<mlbPlayer> BvPParse();
void CalcPlayerProjections(vector<mlbPlayer> x, vector<BallPark> y);
void MLBProjectionsCSV();
vector<BallPark> BallParkParse();
vector<mlbPlayer> MLBPlayerRosterTT(); // Fix for teams .. grabs last 7 days from fangraphs so players are on 1 team not traded.
string changeTeam(string x);
vector<gameOdds> LoadGameOdds();
vector<Catcher> CatcherStats();
vector<Pitcher> PitcherStats();
vector<mlbPlayer> StartingPlayer();
vector<mlbPlayer> MLBPlayerRoster();
vector<mlbPlayer> BatterHand();
vector<Pitcher> PitcherTeamFIX();
vector<Pitcher> PitcherDefenseVsSB();
vector<Pitcher> PitcherPitchType();
vector<mlbPlayer> Batter_Pitch_Type();


std::vector<PlayerInfo> LineUpData(string x);
static inline std::string &ltrim(std::string &s);
static inline std::string &rtrim(std::string &s);
static inline std::string &trim(std::string &s);