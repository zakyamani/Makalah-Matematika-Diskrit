#include <bits/stdc++.h>

using namespace std;

const int initMoney = 4000; 
const int initOTMoney = 50000; 
const int maxMoney = 80000; 
const int winBonus = 16250; 
const int lossBonus = 12000; 
const int CTFullBuy = 24000; 
const int TFullBuy = 21000; 

map<tuple<bool, int, int, int, int>, double> memo;

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
    // Recurrence Base (if the game ends tie)
    if((scoreA == 15) && (scoreB == 15)){ 
        return 0;
    }
    // Recurrence Base (if the game ends on A win the game)
    if(((scoreA == 13) && (scoreB < 12)) || (scoreA == 16)){ 
        return team;
    }
    // Recurrence Base (if the game ends on B win the game)
    if(((scoreB == 13) && (scoreA < 12)) || (scoreB == 16)){ 
        return !team;
    }

    if(scoreA + scoreB == 12){
        moneyA = initMoney;
        moneyB = initMoney;
    }
    if((scoreA + scoreB == 24) || (scoreA + scoreB == 27)){
        moneyA = initOTMoney;
        moneyB = initOTMoney;
    }
    if(moneyA > maxMoney){
        moneyA = maxMoney;
    }
    if(moneyB > maxMoney){
        moneyB = maxMoney;
    }

    auto currentState = make_tuple(team, moneyA, moneyB, scoreA, scoreB);
    if(memo.count(currentState)){
        return memo[currentState];
    }

    double prob = 0;

    if((scoreA + scoreB < 12) || ((scoreA + scoreB >= 24) && (scoreA + scoreB < 27))){
        if((moneyA >= CTFullBuy) && (moneyB >= TFullBuy)){
            prob = 0.488 * calculate_win_probability(team, moneyA - (CTFullBuy/5)*3 + winBonus, moneyB - TFullBuy + lossBonus, scoreA + 1, scoreB) + 0.512 * calculate_win_probability(team, moneyA - CTFullBuy + lossBonus, moneyB - (TFullBuy/5)*3 + winBonus, scoreA, scoreB + 1);
        }else if((moneyA >= CTFullBuy) && (moneyB < TFullBuy)){
            prob = 0.96 * calculate_win_probability(team, moneyA - (CTFullBuy/5)*3 + winBonus, moneyB + lossBonus, scoreA + 1, scoreB) + 0.04 * calculate_win_probability(team, moneyA - CTFullBuy + lossBonus, moneyB + winBonus, scoreA, scoreB + 1);
        }else if((moneyA < CTFullBuy) && (moneyB >= TFullBuy)){
            prob = 0.04 * calculate_win_probability(team, moneyA + winBonus, moneyB - TFullBuy + lossBonus, scoreA + 1, scoreB) + 0.96 * calculate_win_probability(team, moneyA + lossBonus, moneyB - (TFullBuy/5)*3 + winBonus, scoreA, scoreB + 1);
        }else{
            prob = 0.488 * calculate_win_probability(team, moneyA + winBonus, moneyB + lossBonus, scoreA + 1, scoreB) + 0.512 * calculate_win_probability(team, moneyA + lossBonus, moneyB  + winBonus, scoreA, scoreB + 1);
        }
    }else{
        if((moneyA >= TFullBuy) && (moneyB >= CTFullBuy)){
            prob = 0.512 * calculate_win_probability(team, moneyA - (TFullBuy/5)*3 + winBonus, moneyB - CTFullBuy + lossBonus, scoreA + 1, scoreB) + 0.488 * calculate_win_probability(team, moneyA - TFullBuy + lossBonus, moneyB - (CTFullBuy/5)*3 + winBonus, scoreA, scoreB + 1);
        }else if((moneyA >= TFullBuy) && (moneyB < CTFullBuy)){
            prob = 0.96 * calculate_win_probability(team, moneyA - (TFullBuy/5)*3 + winBonus, moneyB + lossBonus, scoreA + 1, scoreB) + 0.04 * calculate_win_probability(team, moneyA - TFullBuy + lossBonus, moneyB + winBonus, scoreA, scoreB + 1);
        }else if((moneyA < TFullBuy) && (moneyB >= CTFullBuy)){
            prob = 0.04 * calculate_win_probability(team, moneyA + winBonus, moneyB - CTFullBuy + lossBonus, scoreA + 1, scoreB) + 0.96 * calculate_win_probability(team, moneyA + lossBonus, moneyB - (CTFullBuy/5)*3 + winBonus, scoreA, scoreB + 1);
        }else{
            prob = 0.512 * calculate_win_probability(team, moneyA + winBonus, moneyB + lossBonus, scoreA + 1, scoreB) + 0.488 * calculate_win_probability(team, moneyA + lossBonus, moneyB  + winBonus, scoreA, scoreB + 1);
        }
    }
    memo[currentState] = prob; 
    return prob;
}

void printCalculation(string teamA, string teamB, double AWin, double BWin){
    cout << "The probability of " << teamA << " win the game is " << AWin << "%" << endl;
    cout << "The probability of " << teamB << " win the game is " << BWin << "%" << endl;
    cout << "The probability of the game ends tie is " << 100 - AWin - BWin << "%";
}

int main(){
    string teamA, teamB;
    int moneyA, moneyB, scoreA, scoreB;
    teamInisiation(&teamA,&teamB,&moneyA,&moneyB,&scoreA,&scoreB);
    auto start = chrono::high_resolution_clock::now();
    memo.clear();
    double AWin = calculate_win_probability(1, moneyA, moneyB, scoreA, scoreB) * 100;
    memo.clear();
    double BWin = calculate_win_probability(0, moneyA, moneyB, scoreA, scoreB) * 100;
    auto end = chrono::high_resolution_clock::now(); 
    chrono::duration<double, std::milli> duration = end - start;
    cout << endl << "Waktu eksekusi DP: " << fixed << setprecision(4) << duration.count() << " milidetik." << endl;
    printCalculation(teamA, teamB, AWin, BWin);
}