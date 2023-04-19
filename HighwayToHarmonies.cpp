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



cout << "Welcome to Highways to Harmony! Please choose a genre you'd like to explore:" << "\n";
cout << " 1. Pop \n 2. Rap \n 3. Jazz \n 4. Hip-Hop \n 5. Country \n 6. EDM \n 7. Indie \n 8. Alternative \n 9. Rock \n";
int run = 0;
cin >> run;

vector<vector<string>> content;
vector<string> row;

ifstream myData ("MusicData.csv");
if(myData.is_open()) {
    cout << "Initial success \n";}
string line, word;

vector<string> thisSong;
while(getline(myData, line)) {
    row.clear();
    stringstream str(line);
        while(getline(str, word, ',')) 
			row.push_back(word);
	content.push_back(row);
}

cout << "Input the title of the song you'd like:\n";
string name;
getline(cin, name);

cout << content[1][12] << "break \n";
cout << name;

/*for(auto iter: content){
    if(strcmpi(iter[12], name) == 0){
    cout << "Did you mean " << iter[12] << " by " << iter[3] << "\n";
    }
}
*/
cout << "Second success";

}