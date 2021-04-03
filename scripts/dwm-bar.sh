#!/bin/zsh
#this script show netspeed as kb/s and mb/s for archlinux , EDITED BY DARKLORD
#ArchLinux YES

#get raw bytes
function get_bytes {
	interface=$(ip route get 8.8.8.8 2>/dev/null| awk '{print $5}')
	received_bytes_old=$(grep $interface /proc/net/dev | cut -d ':' -f 2 | awk '{print $1}')
	transmitted_bytes_old=$(grep $interface /proc/net/dev | cut -d ':' -f 2 | awk '{print $9}')
	
	sleep 1
	clear
	
	received_bytes_new=$(grep $interface /proc/net/dev | cut -d ':' -f 2 | awk '{print $1}')
	transmitted_bytes_new=$(grep $interface /proc/net/dev | cut -d ':' -f 2 | awk '{print $9}')
	
	upload1=${transmitted_bytes_old}
	upload2=${transmitted_bytes_new}
	download1=${received_bytes_old}
	download2=${received_bytes_new}
	
	((upload=$upload2-$upload1))
	((download=$download2-$download1))	
}

#
function get_speed {
	value=$1
	
	if test "$value" -gt 1048576 # aka 1024*1024 , for MB/S
	then
		data=$(echo "scale=4; $value/1024" |bc)
		echo $(echo "scale=2; $data/1024" |bc) MB/s
	else
		echo $(echo "$value/(1024)" |bc)KB/s
	fi
}

dwm_backlight () {
    max=`cat /sys/class/backlight/intel_backlight/max_brightness`
    current=`cat /sys/class/backlight/intel_backlight/actual_brightness`
    rate_origin=`echo "scale=1;$current/$max"|bc`
    rate_final_1=`echo "$rate_origin* 10"|bc`
	rate_final_2=`echo $rate_final_1|cut -f1 -d"."`
}

#!/bin/zsh

LOC=$(readlink -f "$0")
DIR=$(dirname "$LOC")

. "$DIR/bar-functions/dwm_rainbarf.sh"
. "$DIR/bar-functions/dwm_resources.sh"
. "$DIR/bar-functions/dwm_battery.sh"
. "$DIR/bar-functions/dwm_alsa.sh"
. "$DIR/bar-functions/dwm_date.sh"
#. "$DIR/bar-functions/dwm_weather.sh"

while true; do
	dwm_resources
done &

while true; do
	get_bytes
	download_speed=$(get_speed $download)
	upload_speed=$(get_speed $upload)
	
	dwm_backlight
	
	xsetroot -name "[$(< .resources)] [↑ $upload_speed ↓ $download_speed] [☀ $rate_final_2] [$(dwm_battery)] [$(dwm_alsa)] [$(dwm_date)]"
	sleep 1
done
