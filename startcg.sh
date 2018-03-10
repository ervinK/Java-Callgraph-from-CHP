#!/bin/bash




j=1;
mkdir classes
mkdir -p build/resources/main
mkdir -p build/dependency-cache
#1 arg to app: the project folder
#2 arg to app: full path to bin folder
#3 arg to app: full path to src folder

#1 arg to cpp: the file path to where javap filter is executed
#2 arg to cpp: the full path to a classfile
#3 arg to cpp: full path to bin folder
#4 arg to cpp: full path to src folder

touch out.txt
#gradle -q showClasspath > this.classpath
chmod +x javaphandle.cpp
chmod +x tabu.cpp
chmod +x out.txt
c++ javaphandle.cpp -o main
c++ tabu.cpp -o tab
for i in $(ls $1 -R); do
  if [[ $i = *":"* ]]; 
  then
    rootval=${i//[:]//}
  else
    if [[ $i = *".class"  ]]; 
    then
      fajlok[$j]=$i 
      cval1=${fajlok[$j]}
      concat=$rootval$cval1

      javap $concat > classes/$j.txt
      #echo $j
      arg=classes/$j.txt
      #echo $rootval
      
      #echo $concat
      ./main $arg $concat $2 $3
      
      j=$((j+1))

    fi
    

  fi
  
done
rm -r classes
./tab out.txt
rm -r out.txt
echo 'Callgraph is printed to the output.txt'
