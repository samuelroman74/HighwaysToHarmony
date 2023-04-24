#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;

int main() {

string genres [] = {"pop", "rap", "jazz", "hip hop", "country", "EDM", "indie", "alternative", "rock"};
int genreCount = 9;
const int titleIndex = 1;
const int artIndex = 0;
const int valenceIndex = 3;
const int eraIndex = 13;
const int danceIndex = 5;
const int energyIndex = 7;
const int tempoIndex = 12;
const int yearIndex = 2;
const int genreIndex = 14;

int calcIndices[] = {valenceIndex, eraIndex, danceIndex, energyIndex, tempoIndex};
int otherIndices[] = {4, 8, 9, 10, 11};

cout << "Welcome to Highways to Harmony! Please choose a genre you'd like to explore:" << "\n";
//cout << " 1. Pop \n 2. Rap \n 3. Jazz \n 4. Hip-Hop \n 5. Country \n 6. EDM \n 7. Indie \n 8. Alternative \n 9. Rock \n";
for (int i = 0; i < genreCount; i++) {
    cout << i+1 << ". " << genres[i] << "\n";
}

string run;
string extraString;
getline(cin, run);
int genreChoice = stoi(run) - 1; 
vector<vector<string>> content;
vector<string> row;

ifstream myData ("MusicData.csv");
string line, word;

vector<int> thisSong;
while(getline(myData, line)) {
    row.clear();
    stringstream str(line);
        while(getline(str, word, ',')) 
			row.push_back(word);
	content.push_back(row);
}


string name;
int matchingTitles = 0;
int songIndex = 0;

while(matchingTitles == 0){
cout << "Input the title of the song you like:\n";
getline(cin, name);


for(int i = 0; i < content.size(); i++){
    if(stricmp(content[i][titleIndex].c_str(), name.c_str()) == 0){
    thisSong.push_back(i);
    matchingTitles++;
    }
}
if (matchingTitles == 0){
    cout << "Whoopsies! Couldn't find that song. Try again! \n";
}
else if(matchingTitles > 1) {
    cout << "Whoopsies! Multiple songs have that title. Did you mean:\n";
    int j = 1;
    for(auto iter: thisSong) {
        cout << j << ": \"" << content[iter][titleIndex] << "\" by " << content[iter][artIndex] << " in " << content[iter][yearIndex] << "\n";
        j++;
    } 
    string choice;
    getline(cin, choice);
    songIndex = thisSong[stoi(choice) - 1];
    //This can definitely be optimized (just get rid of the iter)!
}
else 
    songIndex = thisSong[0];
}



cout << "Ooh, yes! I love that one. Last thing: What's most important to you about this song?\n";
cout << "1. Positivity\n2. Era\n3. Danceability\n4. Energy\n5. Tempo\n"; 
string priorityInput;
getline(cin, priorityInput);
int priority = stoi(priorityInput);
    switch(priority) {
        case 1:
        priority = valenceIndex;
        break;
        case 2:
        priority = eraIndex;
        break;
        case 3:
        priority = danceIndex;
        break;
        case 4:
        priority = energyIndex;
        break;
        case 5:
        priority = tempoIndex;
        break;
    }
    //can probably do something here with indices array

int leftOver[4];
int j = 0;
for(int i = 0; i < 5; i++){
    if(priority != calcIndices[i]){
        leftOver[j] = calcIndices[i];
        j++;
    }
}

j = 0;
map<float, int> songs;

for(int i = 1; i < content.size(); i++) {
    float value1 = 0.0;
    float value2 = 0.0;
    float value3 = 0.0;
    for(int j = 0; j < 4; j++){
        value1 += stof(content[i][leftOver[j]]);
    }
    for (int k = 0; k < 5; k++){
        value2 += abs(stof(content[i][otherIndices[k]]));
    }
    value1 = value1/4.0;
    value2 = value2/5.0;
    value3 = (stof(content[i][priority]) + value1 + value2)/3.0; 
    songs[value3] = i;
}

    float value1 = 0.0;
    float value2 = 0.0;
    float songValue = 0.0;
    for(int j = 0; j < 4; j++){
        value1 += stof(content[songIndex][leftOver[j]]);
    }
    for (int k = 0; k < 5; k++){
        value2 += abs(stof(content[songIndex][otherIndices[k]]));
    }
    value1 = value1/4.0;
    value2 = value2/5.0;
    songValue = (stof(content[songIndex][priority]) + value1 + value2)/3.0; 
  
    int breakOut = 0;
    int i = 0;
    vector<int> relevantSongs;




 while(breakOut != 1) {
    auto it = songs.find(songValue);
    map<float, int>::reverse_iterator iter(it);
    for(it; it != songs.end(); it++) {
        int index1 = (*it).second;
        int index2 = (*iter).second;


        if(content[index1][genreIndex].find(genres[genreChoice]) != string::npos){
                vector<int> genreNum;
                for(int ex = 0; ex < genreCount; ex++) {
                    int found = 0;
                    int sum = 0;
                    while(content[index1][genreIndex].find(genres[ex], found) != string::npos){
                    sum++;
                    found = content[index1][genreIndex].find(genres[ex], found) + 1;
                    }
                    genreNum.push_back(sum);
                }
                pair<int, int> max (0, 0);
             for(int vecIt = 0; vecIt < genreNum.size(); vecIt++) {
                if(genreNum[vecIt] > max.second) {
                    max.first = vecIt;
                    max.second = genreNum[vecIt];
                     }
                else if (genreNum[vecIt] == max.second && vecIt == genreChoice) {
                    max.first = vecIt;
                    max.second = genreNum[vecIt];
                }
                 }
            if(max.first == genreChoice) {
                //Everything from this to above (the large overarching if statement) can be deleted
            relevantSongs.push_back(index1);
            if(relevantSongs.size() >= 10){
                breakOut = 1;
                break;
            }
              }
        }
              //God this is a mess! Essentially makes sure that it doesn't put a genre that really belonds to something else her
        if(content[index2][genreIndex].find(genres[genreChoice]) != string::npos){
                vector<int> genreNum;
                for(int ex = 0; ex < genreCount; ex++) {
                    int found = 0;
                    int sum = 0;
                    while(content[index2][genreIndex].find(genres[ex], found) != string::npos){
                    sum++;
                    found = content[index2][genreIndex].find(genres[ex], found) + 1;
                    }
                    genreNum.push_back(sum);
                }
                pair<int, int> max (0, 0);
             for(int vecIt = 0; vecIt < genreNum.size(); vecIt++) {
                if(genreNum[vecIt] > max.second) {
                    max.first = vecIt;
                    max.second = genreNum[vecIt];
                    }
                else if (genreNum[vecIt] == max.second && vecIt == genreChoice) {
                    max.first = vecIt;
                    max.second = genreNum[vecIt];
                }
                 }
            if(max.first == genreChoice) {
                //Everything from this to above (the large overarching if statement) can be deleted
            relevantSongs.push_back(index2);
            if(relevantSongs.size() >= 10){
                breakOut = 1;
                break;
            }
              }
              //God this is a mess! Essentially makes sure that it doesn't put a genre that really belonds to something else here
        }
        if(iter != songs.rend()){
        iter++;
        }
    }
    
  }


for(auto iter: relevantSongs){
    cout << content[iter][titleIndex] << " by " << content[iter][artIndex] << " in " << content[iter][yearIndex] << "\n";
}


/*
for (auto iter = songs.find(songValue); iter != songs.end(); iter++){
    cout << (*iter).first << " " << (*iter).second << "\n";
}
*/
}