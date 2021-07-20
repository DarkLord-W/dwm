#! /bin/bash

function read_history {
	cat /home/darklord/.zsh_history |while read line
	do
		res=$(echo $line |grep "sudo pacman -Syyu")
		if [ "$res" != "" ]
		then
			raw_time=`echo $line|grep -Eo ":.*:"|tr -cd "[0-9]"`
			result=$(echo /Data/File/.syyu.log | grep "${raw_time}")
			if [ "$result" = "" ]
			then
				echo $raw_time >> /Data/File/.syyu.log
			fi
		fi
	done
}

function calculate_date {
	last=`tail -n 1 /Data/File/.syyu.log`
	last1=`date -d @$last +"%Y-%m-%d"`
	today=`date +%s`
	today1=`date -d @$today +"%Y-%m-%d"`
	if [ "$last" != "" ]
	then
		time_final=`python3 calculate_date.py $today1 $last1`
	else
		time_final=NULL
	fi
}
function syyu {
	read_history
	calculate_date
}



