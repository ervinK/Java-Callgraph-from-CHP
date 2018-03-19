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
touch output.txt
cp /dev/null output.txt
#gradle -q showClasspath > this.classpath
#if this.classpath is not exists, create that
cp=0;
for k in $(ls); do
  if [[ $k = "this.classpath" ]];
  then
	cp=1;
  fi
done

if [[ $cp = 0 ]];
  then
    gradle -q showClasspath > this.classpath
fi


chmod +x javaphandle.cpp
chmod +x out.txt
echo  > out.txt
c++ javaphandle.cpp -o main
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
grep $'^\t[A-Za-z]\|^[A-Za-z]' out.txt >> output.txt
rm -r out.txt
echo 'Callgraph/error executed to the file: output.txt'
