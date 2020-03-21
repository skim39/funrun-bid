#include <iostream> 
#include <vector>
#include <utility>
#include <string>
#include <unordered_set>

using namespace std;

typedef vector<pair<string, vector<pair<string, int>>>> Players;

void updateScore(Players &players, string lostPlayer, int buyin) {
    for (auto &p : players) {
        // case the current player is lost
        if (lostPlayer.compare(p.first) == 0) {
            for (int i = 0; i < p.second.size(); i++) {
                p.second[i].second -= buyin;
            }
        } else {
            for (int i = 0; i < p.second.size(); i++) {
                if (lostPlayer.compare(p.second[i].first) == 0) {
                    p.second[i].second += buyin;
                    break;
                }
            }
        }
    }
}

void printAllScores(Players &players) {
    for (auto &p : players) {
        cout << p.first << "'s pot: ";
        // score = pair<string, int>
        for (auto score : p.second) {
            cout << score.first << " " << score.second << ", ";
        }
        cout << endl;
    }
}

void printStatus(Players &players) {
    for (auto p : players) {
        // score = pair<string, int>
        for (auto score : p.second) {
            if (score.second < 0) {
                cout << p.first << " owes " << score.first 
                     << " " << abs(score.second) << " dollars, " << endl; 
            } 
        }
    }
}

int main(int argc, char *argv[]) {
    int buyin = 0;
    Players players;
    unordered_set<string> allPlayers;

    for (int i = 1; i < argc; i++) {
        players.push_back(make_pair(argv[i], vector<pair<string, int>>()));
        allPlayers.insert(argv[i]);
        for (int j = 1; j < argc; j++) {
            if (strcmp(argv[j], argv[i]) != 0) {
                players.back().second.push_back(make_pair(argv[j], 0));
            }
        }
    }

    while (true) {
        cout << "Buy in for this round:" << endl;

        cin >> buyin;
        while(cin.fail()) {
            cout << "Error" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cout << "not integer" << endl;
            cin >> buyin;
        }
        string lostPlayer = "";
        cin >> lostPlayer;
        while (allPlayers.find(lostPlayer) == allPlayers.end()) {
            cout << lostPlayer << " doesn't exist" << endl;
            cin >> lostPlayer;
        }
        updateScore(players, lostPlayer, buyin);
        printStatus(players);
    }

    return 0;
}

