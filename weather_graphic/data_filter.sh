#!bin/bash

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
j='1'
o='c'

##################
#checks arguments#
##################

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
		"--ABR")		j='1'
					shift;;
		"--AVL")		j='2'
					shift;;
		"--tab")		j='3'
					shift;;
		*) 			echo "Error with the $1 argument "
					exit 1;;

	esac
done

if ! [[ -f "resources/$f" ]] || [[ ${f#*.} != "csv" ]]
	then echo "Your file must be a csv file and placed in the ressources directory"
	exit 1;
fi

###############
#region filter#
###############

case $region in
   "F")
   	echo generating file for France...
   	awk -F ';' '$1 < 08000 && NR>1' resources/$f > temporary_files/filtered_data.csv
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
   *)	awk 'NR>1' resources/$f > temporary_files/filtered_data.csv;;
esac


#############
#date filter#
#############

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
		awk -F ';' '$(compares $date1 $2 == 0)' filtered_data.csv >  filtered_data_2.csv
		rm filtered_data.csv
		mv filtered_data_2.csv filtered_data.csv
	fi
fi


##################
#data type filter#
##################

# announces first step
# copies collumns related to data type
# calls C program
# generates graphic from sorted file

for i in $(seq 1 $k); 
do
	case ${opt[i]} in 
		"-t1")			echo sorting temperature 1 data...
					awk -F ";|," '{
							if($1 != "" && $12 != "")
								print $1, $12;
							}'  temporary_files/filtered_data.csv > temporary_files/temp1.csv
					./exe temp1.csv temp_1_data.csv 1 "$j" "$o"
					`gnuplot sources/graph_generation/temperature_1.gpt`
					;;
					
		"-t2")			echo sorting temperature 2 data...
					awk -F ";|," '{
							if($2 != "" && $12 != "")
								print $2, $12;
							}'  temporary_files/filtered_data.csv > temporary_files/temp2.csv
					./exe temp2.csv temp_2_data.csv 2 "$j" "$o"
					`gnuplot sources/graph_generation/temperature_2.gpt`
					;;
					
		"-t3")			echo sorting temperature 3 data...
					awk -F ";|," '{
							if($1 != "" && $2 != "" && $12 != "")
								print $1, $2, $12;
							}'  temporary_files/filtered_data.csv > temporary_files/temp3.csv
					./exe temp3.csv temp_3_data.csv 3 "$j" "$o"
					;;
					
		"-p1")			echo sorting pression 1 data...
					awk -F ";|," '{
							if($1 != "" && $7 != "")
								print $1, $7;
							}'  temporary_files/filtered_data.csv > temporary_files/pres1.csv
					./exe pres1.csv press_1_data.csv 1 "$j" "$o"
					`gnuplot sources/graph_generation/pression_1.gpt`
					;;
					
		"-p2")			echo sorting pression 2 data...
					awk -F ";|," '{
							if($2 != "" && $7 != "")
								print $1, $7;
							}'  temporary_files/filtered_data.csv > temporary_files/pres2.csv
					./exe pres2.csv press_2_data.csv 2 "$j" "$o"
					`gnuplot sources/graph_generation/pression_2.gpt`
					;;
					
		"-p3")			echo sorting pression 3 data...
					awk -F ";|," '{
							if($1 != "" && $2 != "" && $12 != "")
								print $1, $2, $7;
							}'  temporary_files/filtered_data.csv > temporary_files/pres3.csv
					./exe pres3.csv press_3_data.csv 3 "$j" "$o"
					;;
					
		"-w")			echo sorting wind data...
					awk -F ";|," '{
							if($1 != "" && $10 != "" && $11 != "" && $4 != "" && $5 != "")
								print $1, $10, $11, $4, $5;
							}'  temporary_files/filtered_data.csv > temporary_files/wind.csv
					./exe wind.csv wind_data.csv w "$j" "$o"
					`gnuplot sources/graph_generation/wind.gpt`
					;;
					
		"-m")			echo sorting moisture data...
					awk -F ";|," '{
							if($1 != "" && $10 != "" && $11 != "" && $6 != "")
								print $1, $10, $11, $6;
							}'  temporary_files/filtered_data.csv > temporary_files/moisture.csv
					./exe moisture.csv moisture_data.csv m "$j" "$o"
					`gnuplot sources/graph_generation/moisture.gpt`
					;;
					
		"-h")			echo sorting altitude data...
					awk -F ";|," '{
							if($1 != "" && $10 != "" && $11 != "" && $15 != "")
								print $1, $10, $11, $15;
							}'  temporary_files/filtered_data.csv > temporary_files/altitude.csv
					./exe altitude.csv altitude_data.csv h "$j" "$o"
					`gnuplot sources/graph_generation/altitude.gpt`
					;;
	esac
done

rm temporary_files/*

