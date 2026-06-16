#include <bits/stdc++.h>

using namespace std;

const int winBonus = 16250;
const int lossBonus = 12000;
const int CTFullBuy = 22000;
const int TFullBuy = 20000;

void inisiasiTim(string *timA, string *timB, int *moneyA, int *moneyB, int *skorA, int *skorB){
    cout << "Masukkan nama tim 1 (Sekarang sebagai CT): ";
    cin >> *timA;
    cout << "Masukkan nama tim 2 (Sekarang sebagai T): ";
    cin >> *timB;
    cout << "Masukkan total uang yang dimiliki tim " << *timA << ": ";
    cin >> *moneyA;
    cout << "Masukkan total uang yang dimiliki tim " << *timB << ": ";
    cin >> *moneyB;
    cout << "Masukkan skor yang telah dicapai oleh tim " << *timA << ": ";
    cin >> *skorA;
    cout << "Masukkan skor yang telah dicapai oleh tim " << *timB << ": ";
    cin >> *skorB;
}

double calculate_win_probability(int moneyA, int moneyB, int skorA, int skorB){
    if(((skorA == 13) && (skorB < 12)) || (skorA == 15)){
        return 1;
    }
    if(((skorB == 13) && (skorA < 12)) || (skorB == 15)){
        return 0;
    }
    
    if((moneyA >= CTFullBuy) && (moneyB >= TFullBuy)){
        return 0.5 * calculate_win_probability(moneyA - CTFullBuy + winBonus, moneyB - TFullBuy + lossBonus, skorA + 1, skorB) + 0.5 * calculate_win_probability(moneyA - CTFullBuy + lossBonus, moneyB - TFullBuy + winBonus, skorA, skorB + 1);
    }else if((moneyA >= CTFullBuy) && (moneyB < TFullBuy)){
        return 0.9 * calculate_win_probability(moneyA - CTFullBuy + winBonus, moneyB + lossBonus, skorA + 1, skorB) + 0.1 * calculate_win_probability(moneyA - CTFullBuy + lossBonus, moneyB + winBonus, skorA, skorB + 1);
    }else if((moneyA < CTFullBuy) && (moneyB >= TFullBuy)){
        return 0.1 * calculate_win_probability(moneyA + winBonus, moneyB - TFullBuy + lossBonus, skorA + 1, skorB) + 0.9 * calculate_win_probability(moneyA + lossBonus, moneyB - TFullBuy + winBonus, skorA, skorB + 1);
    }else{
        return 0.5 * calculate_win_probability(moneyA + winBonus, moneyB + lossBonus, skorA + 1, skorB) + 0.5 * calculate_win_probability(moneyA + lossBonus, moneyB  + winBonus, skorA, skorB + 1);
    }

}

int main(){
    string timA, timB;
    int moneyA, moneyB, skorA, skorB;
    inisiasiTim(&timA,&timB,&moneyA,&moneyB,&skorA,&skorB);
    cout << timA << " " << timB << " " << moneyA << " " << moneyB << " " << skorA << " " << skorB << endl;
    cout << "Peluang Tim " << timA << " menang adalah " << calculate_win_probability(moneyA, moneyB, skorA, skorB) * 100 << "%";
}