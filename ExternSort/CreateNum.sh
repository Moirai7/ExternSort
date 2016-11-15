#!/bin/bash

x1=2016213633

size=2147483648

m=1125899906842679

for ((index=0;index<$size;++index))
do 
	echo $x1
	x1=$[ ($x1*3+5)%1125899906842679 ]
done
echo $x1
