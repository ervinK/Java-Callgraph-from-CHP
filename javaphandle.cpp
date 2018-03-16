#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*
This sourcefile is executed by startcg.sh and called to one of the txts
created by directed javap command in the bash script.
The given parameters in the arguments of main, are:
1. txtfile path
2. path to the temporary analyzed bin file
3. bin path
4. src path

*/


string eraseSubStr(string & mainStr, const string & toErase)
{
	// Search for the substring in string
	size_t pos = mainStr.find(toErase);
 
	if (pos != std::string::npos)
	{
		// If found then erase it from the string
		mainStr.erase(pos, toErase.length());
	}
	return mainStr;
}

string eraseNumber(string str){
/* in the example: OuterClass$1InnerClass 
the class we should call is InnerClass 
but there is a number 1 in the name after the $
*/

	if(str[0] >= '1' && str[0] <= '9'){
		string delChar;
		delChar.push_back(str[0]);

		eraseSubStr(str,delChar);
	}
	return str;

}

int isMatch(string str, string str2){ // isMatch is to search and locate the end of a substring in a string 
	int i = 0;
	while(i < str.length()-str2.length()){ // ascertain about we don't overindexing
		int j = 0;
		int match = 0;			  //  go until we can find the substring   
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
/* this method is deleting the package path before the class
from the javap text-reading */
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





string getClassName(string str){ 
/*
This method is for get the classname. the second line of javap is always contains
the classname, so it is only called for that.
*/

/*TOOOOOOOOODOOOOOOOOOOO SZAMOK
[java -jar org.cho-1.0.jar -s Istvanparse -m 1Local.foo ]*/


	if(isMatch(str,"class ") != 1){ //if line contains the class
		if(str.find("$") != std::string::npos){ //if it's nested
			int i = isMatch(str,"$");
			int count = 0;
			while(str[i] != ' ' && str[i] != '{' && str[i] != '<'){ i++; count++;}
			/*the < character in the condition is for the classes like this:
				"class Generic1<T extends Interface>"
			*/
			i = isMatch(str,"$");
			char toStr[count];
			count = 0;
			while(str[i] != ' ' && str[i] != '{' && str[i] != '<'){ toStr[count] = str[i]; i++; count++;}
			toStr[count] = '\0';
			string retStr(toStr);
			if(retStr >= "0" && retStr <= "9"){
				return "badcname";
			}
			return eraseNumber(cutRoot(retStr));
		}else{
			int i = isMatch(str,"class ");
			int count = 0;
			while(str[i] != ' ' && str[i] != '{' && str[i] != '<'){ i++; count++;}
			/*the < character in the condition is for the classes like this:
				"class Generic1<T extends Interface>"
			*/
			i = isMatch(str,"class ");
			char toStr[count];
			count = 0;
			while(str[i] != ' ' && str[i] != '{' && str[i] != '<'){ toStr[count] = str[i]; i++; count++;}
			toStr[count] = '\0';
			string retStr(toStr);
			return cutRoot(retStr);

		}
	}else{
		cout << "[  Bad given datas!  ]" << endl;
		return "badcname";
	}
	
}


string isFunction(string str, string className){

	/* It's quiet simply to determine the functions in the javap output.
		only the functions and the methods have () marks, so I check
		in the main function if the method name is characterly same the name of class*/
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
	return ".$failur{e};"; //This return is can't be a classname, and can't be valid return of the true branch.
	
	
	
}



string transformToClassPath(string arg1, string arg2){ 
/* delete the binary path from the path and create 
	this way the package path */
	if(arg1.find(arg2) != std::string::npos){ // ascertain the path really contains the bin's path
		/* first of all, delete the exmpclass.class from
		the end of the path 
		I wan't brave enough to use built-in eraser to delete the .class from the path
		because the name of the bin folder and the classfile name can be the same.
		replace classfile name with ? */
		int i = arg1.length()-1;
		int num = 0;
		while(arg1[i] != '/'){
			arg1[i] = '?';
			num++; 
			i--;
		}
		char withoutClassfile[arg1.length()-num];
		num = 0;
		for(int i = 0; i < arg1.length(); i++){
			if(arg1[i] != '?'){ //create new string without ?s
				withoutClassfile[num] = arg1[i];
				num++;
			}
		}
		if(num == 0){  //if there is no binpath, so all files can be found in 1 dir, package hierarchy isn't needed
			return "";
		}
		withoutClassfile[num] = '\0';
		string strToFormat(withoutClassfile);
		string retStr = eraseSubStr(strToFormat,arg2 + "/");
		for(int i = 0; i < retStr.length(); i++){
			if(retStr[i] == '/'){
				retStr[i] = '.';
			}
		}
		return retStr;
	
	
		
	}else{
		cout << "In path " << arg1 << " can't find the " << arg2 << " binary dir! " << endl;
		return ".$failur{e};";
	}
	
	
}


int main(int argc, char** argv){

	ifstream myfile;
	string txt = "txt";
	//pass args to variables
	string argvar = argv[1];
	string path = argv[2];
	string bin = argv[3];
	string src = argv[4];
	//open current given txt file
	myfile.open (argvar.c_str());
	string line;
	int i = 1;
	string className;
	while (getline(myfile, line)) {
		
		if(i == 2){
			className = getClassName(line);
		//every single javap output, in the second line you can find the classname
		}

		if(isFunction(line,className) != ".$failur{e};"){
			
			string methodName = isFunction(line,className);
			
			string classPath = transformToClassPath(path, bin);
			cout << "src: " << src << endl;
			cout << "classpathToSrc: " << classPath << endl;
			cout << "className: " << className << endl;
			cout << "functName: " << methodName << endl;
			if(className != "badcname" && className != "" && classPath != ".$failur{e};"){
				//cout << "[java -jar org.chp-1.0.jar -s " << src << " -m " << classPath << className << "." << methodName << " ]" << endl;
				if(system(("java -jar org.chp-1.0.jar -s " + src + " -m " + classPath + className + "." + methodName + " --classpath-file this.classpath >> out.txt").c_str()) != 0){
					system(("echo 'There was an error until u tried to run CHP with sourcefolder: " + src + " method: " + classPath + className + "." + methodName + " ' >> out.txt").c_str()); 
				}
			

			}

			
			
		}
		
			
		
		
			
		i++;
			
	}

	
	myfile.close();

	return 0;
}
