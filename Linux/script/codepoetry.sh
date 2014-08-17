#!/bin/bash

birthyead=1988
deadyear=1992
currentyear=$((birthyead))
plan_num=0

while [ $currentyear -lt $deadyear ]
do 
	let currentyear=currentyear+1
	let age=currentyear-birthyear
	echo ""
	echo "When you was $age year old:"
	read -p "Did you get a plan? (y/n) " plan_choice

	if [ "$plan_choice" = "y" ] || [ "$plan_choice" = "Y" ];then
		let plan_num=plan_num+1
		echo " You was doing the "$plan_num"th plan ..."
		read -p"   What was the result of the plan? (lose/fall/success)  " plan_result

		case $plan_result in
		'lose'|'l'|'L')
		echo "       A little pity!"
		continue   		;;
		'fall'|'f'|'F')
		echo "		Stand up and go on!" ;;
		'success'|'s'|'S')
		echo "		What a beautiful a day!" ;;
		*);;
		esac
		fi
done
echo 'No regret'
