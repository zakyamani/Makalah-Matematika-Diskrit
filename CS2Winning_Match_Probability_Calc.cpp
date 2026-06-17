#include <bits/stdc++.h>

using namespace std;

const int initMoney = 4000; // Initial money for the first round of the first half and second half (800 * 5 = 4000)
const int winBonus = 16250; // Additional money after a team win a round
const int lossBonus = 12000; // Additional money after a team lose a round
const int CTFullBuy = 22000; // Money that a CT team needed to full buy
const int TFullBuy = 20000; // Money that a T team needed to full buy

void teamInisiation(string *teamA, string *teamB, int *moneyA, int *moneyB, int *scoreA, int *scoreB){
    cout << "Insert the first team (First half playing as CT): ";
    cin >> *teamA;
    cout << "Insert the second team (First half playing as T): ";
    cin >> *teamB;
    cout << "Insert the current score of " << *teamA << ": ";
    cin >> *scoreA;
    cout << "Insert the current score of " << *teamB << ": ";
    cin >> *scoreB;
    if((*scoreA + *scoreB == 0) || (*scoreA + *scoreB == 12)){
        *moneyA = initMoney;
        *moneyB = initMoney;
    }else{
        cout << "Insert the current total money of " << *teamA << ": ";
        cin >> *moneyA;
        cout << "Insert the current total money of " << *teamB << ": ";
        cin >> *moneyB;
    }
}

double calculate_win_probability(bool team, int moneyA, int moneyB, int scoreA, int scoreB){
    if((scoreA == 15) && (scoreB == 15)){
        return 0;
    }
    if(((scoreA == 13) && (scoreB < 12)) || (scoreA == 16)){
        return team;
    }
    if(((scoreB == 13) && (scoreA < 12)) || (scoreB == 16)){
        return !team;
    }
    
    if(scoreA + scoreB < 12){
        if((moneyA >= CTFullBuy) && (moneyB >= TFullBuy)){
            return 0.5 * calculate_win_probability(team, moneyA - CTFullBuy + winBonus, moneyB - TFullBuy + lossBonus, scoreA + 1, scoreB) + 0.5 * calculate_win_probability(team, moneyA - CTFullBuy + lossBonus, moneyB - TFullBuy + winBonus, scoreA, scoreB + 1);
        }else if((moneyA >= CTFullBuy) && (moneyB < TFullBuy)){
            return 0.9 * calculate_win_probability(team, moneyA - CTFullBuy + winBonus, moneyB + lossBonus, scoreA + 1, scoreB) + 0.1 * calculate_win_probability(team, moneyA - CTFullBuy + lossBonus, moneyB + winBonus, scoreA, scoreB + 1);
        }else if((moneyA < CTFullBuy) && (moneyB >= TFullBuy)){
            return 0.1 * calculate_win_probability(team, moneyA + winBonus, moneyB - TFullBuy + lossBonus, scoreA + 1, scoreB) + 0.9 * calculate_win_probability(team, moneyA + lossBonus, moneyB - TFullBuy + winBonus, scoreA, scoreB + 1);
        }else{
            return 0.5 * calculate_win_probability(team, moneyA + winBonus, moneyB + lossBonus, scoreA + 1, scoreB) + 0.5 * calculate_win_probability(team, moneyA + lossBonus, moneyB  + winBonus, scoreA, scoreB + 1);
        }
    }else if(scoreA + scoreB == 12){ // at the second half, each team's money back to the initial money
        return 0.5 * calculate_win_probability(team, initMoney + winBonus, initMoney + lossBonus, scoreA + 1, scoreB) + 0.5 * calculate_win_probability(team, initMoney + lossBonus, initMoney + winBonus, scoreA, scoreB + 1);
    }else{
        if((moneyA >= TFullBuy) && (moneyB >= CTFullBuy)){
            return 0.5 * calculate_win_probability(team, moneyA - TFullBuy + winBonus, moneyB - CTFullBuy + lossBonus, scoreA + 1, scoreB) + 0.5 * calculate_win_probability(team, moneyA - TFullBuy + lossBonus, moneyB - CTFullBuy + winBonus, scoreA, scoreB + 1);
        }else if((moneyA >= TFullBuy) && (moneyB < CTFullBuy)){
            return 0.9 * calculate_win_probability(team, moneyA - TFullBuy + winBonus, moneyB + lossBonus, scoreA + 1, scoreB) + 0.1 * calculate_win_probability(team, moneyA - TFullBuy + lossBonus, moneyB + winBonus, scoreA, scoreB + 1);
        }else if((moneyA < TFullBuy) && (moneyB >= CTFullBuy)){
            return 0.1 * calculate_win_probability(team, moneyA + winBonus, moneyB - CTFullBuy + lossBonus, scoreA + 1, scoreB) + 0.9 * calculate_win_probability(team, moneyA + lossBonus, moneyB - CTFullBuy + winBonus, scoreA, scoreB + 1);
        }else{
            return 0.5 * calculate_win_probability(team, moneyA + winBonus, moneyB + lossBonus, scoreA + 1, scoreB) + 0.5 * calculate_win_probability(team, moneyA + lossBonus, moneyB  + winBonus, scoreA, scoreB + 1);
        }
    }

}

int main(){
    string teamA, teamB;
    int moneyA, moneyB, scoreA, scoreB;
    teamInisiation(&teamA,&teamB,&moneyA,&moneyB,&scoreA,&scoreB);
    double AWin = calculate_win_probability(1, moneyA, moneyB, scoreA, scoreB) * 100;
    double BWin = calculate_win_probability(0, moneyA, moneyB, scoreA, scoreB) * 100;
    cout << "The probability of " << teamA << " win the game is " << AWin << "%" << endl;
    cout << "The probability of " << teamB << " win the game is " << BWin << "%" << endl;
    cout << "The probability of the game end ties is " << 100 - AWin - BWin << "%";
}