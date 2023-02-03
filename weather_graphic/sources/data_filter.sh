#!bin/bash


#################
###date et lon###
#################

##############
###FUNCTION###
##############


verif_coordinates()
{
	echo $1 $2
	if ! [[ $1 =~ ^[+-]?[0-9]+([.][0-9]+)?$ ]];then
      		echo "ERROR fInput contains letters"
      		return 0
	fi
	
	if ! [[ $2 =~ ^[+-]?[0-9]+([.][0-9]+)?$ ]];then
      		echo "ERROR Input contains letters"
      		return 0
      	fi
      	
	if ! [ $1 -gt -100 -a $1 -lt 100 ] && [ $2 -gt -100 -a $2 -lt 100 ]
		then echo "error you must put correct values" 
		return 0
	fi
	echo "All is good mf"
	return 1
}

verif_date()
{
	echo $1 $2
	if ! [[ $1 =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ]] || ! date -d "$1" >/dev/null 
      		then echo "ERROR with the $1 date"
      		return 0
      		
	fi
	
	if ! [[ $2 =~ ^[0-9]{4}-[0-9]{2}-[0-9]{2}$ ]] || ! date -d "$2" >/dev/null
      		then echo "ERROR with the $2 date"
      		return 0
	fi
	
	if [[ "$2" < "$1" ]] ;
		then echo "You must put dates in chronological order and put two different dates"
		return 0
	fi
		
	echo "All is good"
	return 1
}

compares_date()
{
	d1=${1%%*T}
	d2=${2%%*T}
	if [[ "$d1" -gt "$d2" ]] ;
	then return 1
	fi
	return 0
}

##############
#### MAIN ####
##############

k=1
o='c'

while [ $# -gt 0 ] 
do 
	case $1 in
		"--help") 		cat resources/manual.txt
					exit 1
					shift;;
		"-A") 			region=A 
					shift;;
		"-O") 			region=O 
					shift;;
		"-F") 			region=F 
					shift;;
		"-G") 			region=G 
					shift;;
		"-S") 			region=S 
					shift;;
		"-Q") 			region=Q 
					shift;;
		"-g<"*"><"*">")	l=$1 
					lon=1
					shift;;
		"-a<"*"><"*">")	l=$1 
					lat=1
					shift;;
		"-d<"*"><"*">") 	d=$1
					dat=1
					shift;;
		"-f")			f=$2
					shift 2;;
		"-t1")			opt[k]=$1
					k=$((k+1)) 
					shift;;
		"-t2")			opt[k]=$1
					k=$((k+1)) 
					shift;;
		"-t3")			opt[k]=$1
					k=$((k+1)) 
					shift;;
		"-p1")			opt[k]=$1
					k=$((k+1)) 
					shift;;
		"-p2")			opt[k]=$1
					k=$((k+1)) 
					shift;;
		"-p3")			opt[k]=$1
					k=$((k+1)) 
					shift;;
		"-w")			opt[k]=$1
					k=$((k+1)) 
					shift;;
		"-m")			opt[k]=$1
					k=$((k+1)) 
					shift;;
		"-h")			opt[k]=$1
					k=$((k+1)) 
					shift;;
		"-r")			o=${1#*-}
					shift;;
		*) 			echo "Error with the $1 argument "
					exit 1;;

	esac
done
echo $o
if ! [[ -f "resources/$f" ]] || [[ ${f#*.} != "csv" ]]
	then echo "Your file must be a csv file and placed in the ressources directory"
	exit 1;
fi

case $region in
   "F")
   	echo generating file for France...
   	awk -F ';' '8000 > $1 && NR>1' resources/$f > temporary_files/filtered_data.csv
   	;;
   "G") 
   	echo generating file for Guyana...
   	awk -F ';' '$1 >= 81000 && $1 < 82000 && NR>1' resources/$f > temporary_files/filtered_data.csv
   	;;
   "S") 
   	echo generating file for Saint Pierre et Miquelon...
   	awk -F ';' '$1 == 71805 && NR>1' resources/$f > temporary_files/filtered_data.csv
   	;;
   "A") 
   	echo generating file for Antilles...
   	awk -F ';' '$1 >= 78000 && $1 < 79000 && NR>1' resources/$f > temporary_files/filtered_data.csv
   	;;
   "O") 
   	echo generating file for Ocean Indien...
   	awk -F ';' '$1 >= 60000 && $1 < 70000 && NR>1' resources/$f > temporary_files/filtered_data.csv
   	;;
   "Q") 
   	echo generating file for Antarctica...
   	awk -F ';' '$1 == 89642 && NR>1' resources/$f > temporary_files/filtered_data.csv
   	;;
   *)	awk 'NR>1' resources/$f > temporary_files/filtered_data.csv
   	;;
esac

if [[ $lon -eq 1 ]] || [[ $lat -eq 1 ]] ; then	
	l2=${l##*<}
	l2=${l2%*>}
	l1=${l#*a<}
	l1=${l1%%>*}
	verif_coordinates $l1 $l2
	if [[ $? -eq 0 ]] ; then 
		echo "Error with the coordinates"
		exit 1
	elif [[ $lon -eq 1 ]] ; then 
		awk '$10 >= '$l1' && $10 <= '$l2'' temporary_files/filtered_data.csv >  temporary_files/filtered_data.csv
	else 
		awk '$11 >= '$l1' && $11 <= '$l2'' temporary_files/filtered_data.csv >  temporary_files/filtered_data.csv
	fi
fi

if [[ $dat -eq 1 ]]
then 	d2=${d##*<}
	d2=${d2%*>}
	d1=${d#*d<}
	d1=${d1%%>*}
	verif_date $d1 $d2 
	if [[ $? -eq 0 ]]
		then echo "Error with the dates"
		exit 1
	else 	
		T='T00:00:00+00:00'
		date1=$d1$T
		date2=$d2$T
		echo $date1 $date2
		awk -F ';' 'if($(compares $date1 $2) == 0) {print $1}' temporary_files/filtered_data.csv > temporary_files/filtered_data.csv
	fi
fi
echo=${opt[@]}
for i in $(seq 1 $k); 
do
	case ${opt[i]} in 
		"-t1")			awk -F ";|," '{
							if($1 != "" && $12 != "")
								print $1, $12;
							else  
								print "$1";
							}'  temporary_files/filtered_data.csv > temporary_files/temp1.csv
					#system(exe temp1.csv temp_1_data.csv t1 "$o") 
					;;
		"-t2")			awk -F ";|," '{
							if($2 != "" && $12 != "")
								print $2, $12;
							}'  temporary_files/filtered_data.csv > temporary_files/temp2.csv;;
		"-t3")			awk -F ";|," '{
							if($1 != "" && $2 != "" && $12 != "")
								print $1, $2, $12;
							}'  temporary_files/filtered_data.csv > temporary_files/temp3.csv;;
		"-p1")			awk -F ";|," '{
							if($1 != "" && $7 != "")
								print $1, $7;
							}'  temporary_files/filtered_data.csv > temporary_files/pres1.csv;;
		"-p2")			awk -F ";|," '{
							if($2 != "" && $7 != "")
								print $1, $7;
							}'  temporary_files/filtered_data.csv > temporary_files/pres2.csv;;
		"-p3")			awk -F ";|," '{
							if($1 != "" && $2 != "" && $12 != "")
								print $1, $2, $7;
							}'  temporary_files/filtered_data.csv > temporary_files/pres3.csv;;
		"-w")			awk -F ";|," '{
							if($1 != "" && $10 != "" && $11 != "" && $4 != "" && $5 != "")
								print $1, $10, $11, $4, $5;
							}'  temporary_files/filtered_data.csv > temporary_files/wind.csv;;
		"-m")			awk -F ";|," '{
							if($1 != "" && $10 != "" && $11 != "" && $6 != "")
								print $1, $10, $11, $6;
							}'  temporary_files/filtered_data.csv > temporary_files/moisture.csv;;
		"-h")			awk -F ";|," '{
							if($1 != "" && $10 != "" && $11 != "" && $15 != "")
								print $1, $10, $11, $15;
							}'  temporary_files/filtered_data.csv > temporary_files/height.csv;;
	esac
done
echo "Done !"

rm filtered_data.csv

