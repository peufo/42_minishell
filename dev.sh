#!/bin/bash

SRC_DIR="./src"
PROG="./minishell"

watch() {
	STATE_A=""
	PROG_PID=""
	while [[ true ]]
	do
		STATE_B=$(get_state)
		if [[ $STATE_A != $STATE_B ]]; then
			STATE_A=$STATE_B
			if [ $PROG_PID != "" ]; then
				kill $PROG_PID
			fi
			clear
			info "───────── $(date) ─────────"
			sync_sources
			norminette_pretty $SRC_DIR
			
			rm -f "$PROG"
			make
			if [ ! -f "$PROG" ]; then
				warning "COMPILATION FAILED"
			else
				success "COMPILATION OK\n"
				info "───────────────────────────────────────────────────\n"
				if [ $(uname) = "Linux" ]; then
					valgrind --leak-check=full --track-origins=yes --log-file=leaks.log -s $PROG ./test.sh &
					#valgrind --tool=helgrind --log-file=leaks.log -s $PROG "5" "2500" "1000" "1500" "3" &
				else
					#leaks -quiet --atExit -- $PROG "25" "4000" "1000" "1500" &
					$PROG "5" "1500" "1000" "1400" "3" &
				fi
				PROG_PID=$!
				trap 'kill "$PROG_PID" & return' 2
			fi
		fi
		sleep 0.1
	done
}

get_state() {
	if [[ $(uname) == "Linux" ]];  then
		MD5="md5sum"
	else
		MD5="md5"
	fi
	echo $(find -L $SRC_DIR -type f -name "*.[ch]" -exec $MD5 {} \;)
}

sync_sources() {
	SOURCES=$(ls $SRC_DIR/*.c $SRC_DIR/**/*.c | sed "s;$SRC_DIR/;;g" | tr '\n' ' ')
	SED_COMMAND="s;^SOURCES	.*;SOURCES			=	$SOURCES;"
	if [ $(uname) = "Linux" ];  then
		sed -i -e "$SED_COMMAND" "./Makefile"
	else
		sed -i "" "$SED_COMMAND" "./Makefile"
	fi
}

norminette_pretty() {
	NORM_ERROR=$(sed -e '/.*: OK!/d' <(norminette $1))
	if [[ $NORM_ERROR == "" ]] ; then
		success "\nNORMINETTE OK\n"
	else
		warning "\nNORMINETTE ERROR"
		AWK_SCRIPT='{
			if($2 == "Error!") {
				filename = $1;
				print "";
			} else {
				printf "%s%d:%d\t", filename, $4, $6;
				for(i = 7; i <= NF; i++) {
					printf "%s ", $i;
				};
				printf "\n";
			}
		}'
		echo "$NORM_ERROR" | awk "$AWK_SCRIPT"
		echo -e "\n"
	fi
}

info() {
	echo -e "\033[36m$1\033[0m"
}
warning() {
	echo -e "\033[31m$1\033[0m"
}
success() {
	echo -e "\033[32m$1\033[0m"
}

watch