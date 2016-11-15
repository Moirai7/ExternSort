#!/bin/bash

m=1125899906842679

hn=0

cat result_show | while read line
do
	yn=$line
	hn=$[ (3*$hn+$yn)%$m ]
	echo $hn
done
