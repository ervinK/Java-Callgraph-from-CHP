#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

vector<string> lines;
int numberOfLines = 0;

int tabszaml(string str){
	int count = 0;
	for(int i = 0; i < str.length(); i++){
		if(str[i] == '\t'){
			count++;
		}
	}	
	if(count > 1){
		return 0;
	}
	return 1;
}


int main(int argc, char** argv){

	string argvar = argv[1];
	ifstream myfile;
	string line;
	myfile.open (argvar.c_str());
	int i = 1;
	while (getline(myfile, line)) {
		if(tabszaml(line) == 1) {
			lines.push_back(line);
			numberOfLines++;
		}
		i++;
			
	}
	
	ofstream outfile;
	outfile.open ("output.txt");
	for(int i = 0; i < numberOfLines; i++){
		outfile << lines[i] << endl;
		//cout <<lines[i] << endl;
		
	}
	

	return 0;
}
