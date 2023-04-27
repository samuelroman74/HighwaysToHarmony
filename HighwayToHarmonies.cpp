#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <algorithm>

using namespace std;


void sortQuickly(vector<pair<float, int>> &hectorTheVector, int left, int right) {
    if (left >= right) {
        return;
    }
    float pivot = hectorTheVector[left].first;
    int i = left + 1;
    int j = right;
    while (i <= j) {
        while (i <= j && hectorTheVector[i].first < pivot) {
            i++;
        }
        while (i <= j && hectorTheVector[j].first > pivot) {
            j--;
        }
        if (i <= j) {
            swap(hectorTheVector[i], hectorTheVector[j]);
            i++;
            j--;
        }
    }
    swap(hectorTheVector[left], hectorTheVector[j]);
    sortQuickly(hectorTheVector, left, j - 1);
    sortQuickly(hectorTheVector, j + 1, right);
}





int main() {

string genres [] = {"pop", "rap", "jazz", "hip hop", "country", "edm", "indie", "alternative", "rock"};
//Adding genres here might make this work better actually
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
//Where everything is (the important stuff that we'll use multiple times)

int calcIndices[] = {valenceIndex, eraIndex, danceIndex, energyIndex, tempoIndex};
int otherIndices[] = {4, 8, 9, 10, 11};
//Other indices are the non important stuff

cout << "Welcome to Highways to Harmony! Please choose a genre you'd like to explore:" << "\n";
for (int i = 0; i < genreCount; i++) {
    cout << i+1 << ". " << genres[i] << "\n";
}
//Outputs all the choices

string run;
string extraString;
getline(cin, run);
int genreChoice = stoi(run) - 1; 
vector<vector<string>> content;
vector<string> row;

ifstream myData ("MusicData.csv");
string line, word;


while(getline(myData, line)) {
    row.clear();
    stringstream str(line);
        while(getline(str, word, ',')) 
			row.push_back(word);
	content.push_back(row);
}
//Gets input for genre choice and the overall data



int songIndex = 0;
int keepGoing = 0;
int priority = 0;

while (keepGoing == 0){
int matchingTitles = 0;
vector<int> thisSong;
while(matchingTitles == 0){
keepGoing = 1;
cout << "Input the title of a song you like from ANY genre:\n";
string name;
getline(cin, name);
//Allows user to pick choice

for(int i = 0; i < content.size(); i++){
    
    //std::transform(content[i][titleIndex].begin(), content[i][titleIndex].end(), content[i][titleIndex].begin(), ::tolower);
    // Convert complete given Sub String to lower case
    //std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    
    if(stricmp(content[i][titleIndex].c_str(), name.c_str()) == 0){
    //if(content[i][titleIndex].find(name) != string::npos){
    thisSong.push_back(i);
    matchingTitles++;
    }
    //}
    //Counts how many titles there are
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
    cout << j << ". None of the above\n";
    string choice;
    getline(cin, choice);
    if(stoi(choice) != j)
    songIndex = thisSong[stoi(choice) - 1];
    else {
        cout << "Sorry to hear that! The song is either not in our database or requires you to be more specific. \nLet's try this again. ";
        keepGoing = 0;
    }
    //This can definitely be optimized (just get rid of the iter)!
}
else 
    songIndex = thisSong[0];
}

if(keepGoing != 0) {

cout << "Ooh, yes! " << content[songIndex][titleIndex] << " by " << content[songIndex][artIndex] << "? I love that one. \nLast thing: What's most important to you about this song?\n";
cout << "1. Positivity\n2. Era\n3. Danceability\n4. Energy\n5. Tempo\n6. That's not the song I wanted.\n"; 
string priorityInput;
getline(cin, priorityInput);
priority = stoi(priorityInput);
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
        case 6:
        cout << "Oh, my bad! Let's try it again. ";
        keepGoing = 0;
        break;
    }
}
    //Gets input for whatever they want to focus on.
    //can probably do something here with indices array
}

int leftOver[4];
int j = 0;
for(int i = 0; i < 5; i++){
    if(priority != calcIndices[i]){
        leftOver[j] = calcIndices[i];
        j++;
    }
}
//Puts the thing they don't want to focus on in an array

j = 0;
vector<pair<float, int>> songs;
//Finally we get to our maps! The main map

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
    songs.push_back(make_pair(value3, i));
    //Gets the average of the value of the thing they want, the average of the other important stuff, and the average of everything else
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
        //Does that one more time for the song they chose

    int breakOut = 0;
    int i = 0;
    vector<int> relevantSongs;
    sort(songs.begin(), songs.end());
    //sortQuickly(songs, 0, songs.size() - 1);

    int findIndex = 0;

    for(int i = 0; i < songs.size(); i++){
        if(songs[i].first == songValue) {
            findIndex = i;
            cout << "Succesful! " << i << songs[i].second << "\n";
            break; 
        }
    }


 while(breakOut != 1) {
    int k = findIndex;
    int l = findIndex;
    for(k; k < songs.size(); k++) {
        int j = songs[l].second;
        int i = songs[k].second;
    //Sets up so we can iterate backwards AND forwards from the value we want
        if(content[i][genreIndex].find(genres[genreChoice]) != string::npos && songs[k].first != songValue){
                vector<int> genreNum;
                for(int ex = 0; ex < genreCount; ex++) {
                    int found = 0;
                    int sum = 0;
                    while(content[i][genreIndex].find(genres[ex], found) != string::npos){
                    sum++;
                    found = content[i][genreIndex].find(genres[ex], found) + 1;
                    }
                    genreNum.push_back(sum);
                }
                //If the selected genre is part of the song, counts how many times EVERY genre shows up in genre descriptions
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
                //Checks whether another genre comes up more often than the selected one for the given song
            if(max.first == genreChoice) {
                //If the selected genre comes up the max amount of times, continues
            relevantSongs.push_back(i);
            if(relevantSongs.size() >= 10){
                breakOut = 1;
                break;
            }
              }
        }
    //Overall, essentially makes sure that it doesn't put a genre that really belonds to something else
    //Below just does the same thing as it iterates backwards
        if(content[j][genreIndex].find(genres[genreChoice]) != string::npos && songs[l].first != songValue){
                vector<int> genreNum;
                for(int ex = 0; ex < genreCount; ex++) {
                    int found = 0;
                    int sum = 0;
                    while(content[j][genreIndex].find(genres[ex], found) != string::npos){
                    sum++;
                    found = content[j][genreIndex].find(genres[ex], found) + 1;
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
            relevantSongs.push_back(j);
            if(relevantSongs.size() >= 10){
                breakOut = 1;
                break;
            }
              }
        }

        if(l != 1){
        l--;
        }
        //Makes the reverse iterator acutally go backwards (as long as it can)
    }
    
  }

cout << "This is what we found! Hope you enjoy rocking out to these tunes.\n";
 i = 1;
for(auto iter: relevantSongs){
    cout << i << ". " << content[iter][titleIndex] << " by " << content[iter][artIndex] << " in " << content[iter][yearIndex] << "\n";
    i++;
}
//Prints out the songs it found


}