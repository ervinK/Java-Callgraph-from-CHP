#!/bin/bash

j=0;
k=0;
for i in $(ls src -R); do
  if [[ $i = *":"* ]]; 
  then
    
    cval=${i//['/':]/.}
  else
    if [[ $i = *".java"*  ]]; 
    then
      fajlok[$j]=$i 
      concat=$cval${fajlok[$j]}
      echo  $concat
      j=$((j+1))

    fi
    

  fi
  
done
