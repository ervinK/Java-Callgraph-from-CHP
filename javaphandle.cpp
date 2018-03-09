#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;



int isMatch(string str, string str2){ // isMatch is to search and locate the end of a substring in a string 
	int i = 0;
	while(i < str.length()-str2.length()){ // ascertain about we don't overindexing
		int j = 0;
		int match = 0;
		while(str2[j] != '\0'){
			if(str[i+j] == str2[j]){
				match++;
			}
			
			j++;
		}
		if(match == str2.length()){
			return i+j;     /*return with the character after the last letter of the found substring
							this not able to cause error, because the substring is a directory in the
							path of the package and it is impossible to be the last substring. if it's, 
							the given input is wrong*/
		}
		i++;
	}
	return -1;
}

string cutRoot(string retStr){
	if(retStr.find(".") != std::string::npos){
		int dot = 0;
		int count = 0;
		int begin;
		for(int j = 0; j < retStr.length(); j++){
			if(dot == 1){
				count++;
			}
			if(retStr[j] == '.'){
				dot = 1;
				begin = j+1;
			}
		}
		char securedReturn[count];
		count = 0;
		for(begin; begin < retStr.length(); begin++){
			securedReturn[count] = retStr[begin];
			count++;
		}
		securedReturn[count] = '\0';
		string secStr(securedReturn);
		return(secStr);
	}else{
		return retStr;
	}
}

string getClassName(string str){ /* handling the nested classes too, where 
									is a $ mark in the compiled classname */
	if(isMatch(str,"class ") != 1){
		if(str.find("$") != std::string::npos){
			int i = isMatch(str,"$");
			int count = 0;
			while(str[i] != ' ' && str[i] != '{'){ i++; count++;}
			i = isMatch(str,"$");
			char toStr[count];
			count = 0;
			while(str[i] != ' ' && str[i] != '{'){ toStr[count] = str[i]; i++; count++;}
			toStr[count] = '\0';
			string retStr(toStr);
			return cutRoot(retStr);
		}else{
			int i = isMatch(str,"class ");
			int count = 0;
			while(str[i] != ' ' && str[i] != '{'){ i++; count++;}
			i = isMatch(str,"class ");
			char toStr[count];
			count = 0;
			while(str[i] != ' ' && str[i] != '{'){ toStr[count] = str[i]; i++; count++;}
			toStr[count] = '\0';
			string retStr(toStr);
			return cutRoot(retStr);

		}
	}else{
		cout << "Bad given datas!" << endl;
		exit(0);
	}
	
}


string isFunction(string str, string className){
	if((str.find("(") != std::string::npos && str.find(")") != std::string::npos) && (str.find("$") == std::string::npos)){
		int i = str.length()-1;
		while(str[i] != '('){ i--; }
		i--;
		int num = 0;
		while(str[i] != '.' && str[i] != ' '){ num++; i--; }
		char functionName[num];
		i++;
		int j = 0;
		while(str[i] != '('){ functionName[j] = str[i]; i++; j++;}
		functionName[j] = '\0';
		string rstr(functionName);
		//cout << rstr << endl;
		if(rstr != className){
			return rstr;
		}
		
	}
	return ".$failur{e}";
	
	
	
}


string transformToCall(string arg1, string arg2){
	
	int i = arg1.length()-1;
	while(arg1[i] != '/'){
		arg1[i] = '?';
		i--;
	}
	
	int j = isMatch(arg1,arg2);
	
	if(j != -1){
		while(j >= 0){
			arg1[j] = '?';
			j--;
		}
		int count = 0;
		for(int k = 0; k < arg1.length(); k++){
			if(arg1[k] != '?'){
				count++;
			}
		}
		if(count == 0){
			return "";
		}
		char retStr[count];
		count = 0;
		for(int k = 0; k < arg1.length(); k++){
			if(arg1[k] != '?'){
				if(arg1[k] == '/'){
					retStr[count] = '.';
				}else{
					retStr[count] = arg1[k];
				}
				count++;
			}
		}
		if(count == 0){
			return "";
		}
		
		retStr[count] = '\0';
		string rStr(retStr); 
		return rStr;
		
	}else{
		exit(0);
	}
	return arg1;
	
	
}


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

	ifstream myfile;
	string txt = "txt";
	string argvar = argv[1];
	string path = argv[2];
	string bin = argv[3];
	string src = argv[4];
	myfile.open (argvar.c_str());
	string line;
	int i = 1;
	string className;
	while (getline(myfile, line)) {
		if(i == 2){
			className = getClassName(line);
		}

		if(isFunction(line,className) != ".$failur{e}"){
			string methodName = isFunction(line,className);
			string classPath = transformToCall(path, bin);
			cout << "src: " << src << endl;
			cout << "classpathToSrc: " << classPath << endl;
			cout << "className: " << className << endl;
			cout << "functName: " << methodName << endl;

			system(("java -jar org.chp-1.0.jar -s " + src + " -m " + classPath + className + "." + methodName + " --classpath-file this.classpath >> out.txt").c_str());
			
		}
		
			
		
		
			
		i++;
			
	}

	
	myfile.close();

	return 0;
}
