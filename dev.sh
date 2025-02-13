#!/bin/bash

SRC_DIR="./src"
LOG_DIR="./log"
PROG="./minishell"
ARGS="./test.sh"
LEAKS_CHECK=true

make fclean

if [ $(uname) = "Linux" ]; then
	LEAKS_CMD="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=log/leaks.log -s"
else
	LEAKS_CMD="leaks -quiet --atExit --"
fi

watch() {
	STATE_A=""
	PROG_PID=""
	while [[ true ]]
	do
		STATE_B=$(get_state)
		if [[ $STATE_A != $STATE_B ]]; then
			STATE_A=$STATE_B
			clear
			info "───────── $(date) ─────────"
			sync_sources
			norminette_pretty $SRC_DIR
			
			rm -f "$PROG"
			make
			if [ ! -f "$PROG" ]; then
				warning "COMPILATION\ERROR"
			else
				success "COMPILATION\tOK\n"
				info "───────────────────────────────────────────────────\n"

				for TEST_FILE in ./test/*.sh ; do 
					COMMAND="$PROG $TEST_FILE"
					if $LEAKS_CHECK ; then
						COMMAND="$LEAKS_CMD $COMMAND"
					fi
					mkdir -p "$LOG_DIR/$(basename $TEST_FILE .sh)"
					LOG_FILE="$LOG_DIR/$(basename $TEST_FILE .sh)/mini.log"
					$COMMAND > "$LOG_FILE"
					echo -e "log minishell:\t\t $LOG_FILE"
					get_diff $TEST_FILE $LOG_FILE
					echo
				done
				
				check_leaks
			fi
		fi
		sleep 0.1
	done
}

get_diff() {
	TEST_FILE=$1
	LOG_FILE_MINI=$2
	LOG_FILE_BASH="$LOG_DIR/$(basename $TEST_FILE .sh)/bash.log"
	LOG_FILE_DIFF="$LOG_DIR/$(basename $TEST_FILE .sh)/diff.diff"
	bash $TEST_FILE > $LOG_FILE_BASH
	diff -u $LOG_FILE_BASH $LOG_FILE_MINI > $LOG_FILE_DIFF
	echo -e "log bash:\t\t $LOG_FILE_BASH"
	echo -e "log diff:\t\t $LOG_FILE_DIFF"
}

get_state() {
	if [[ $(uname) == "Linux" ]];  then
		MD5="md5sum"
	else
		MD5="md5"
	fi
	SRC_STATE=$(find -L $SRC_DIR -type f -name "*.[ch]" -exec $MD5 {} \;)
	TEST_STATE=$(find -L ./test -type f -name "*.sh" -exec $MD5 {} \;)
	echo "$SRC_STATE $TEST_STATE"
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
		success "\nNORMINETTE\tOK\n"
	else
		warning "\nNORMINETTE\tERROR"
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

check_leaks() {
	LEAKS_DETECTED=$(cat ./log/leaks.log | grep "ERROR SUMMARY" | awk '{printf "%s", $4}' | tr -d "0")
	if [[ $LEAKS_DETECTED == "" ]] ; then
		success "NO LEAKS 💃💃💃"
	else
		warning "LEAKS DETECTED"
		info "./log/leaks.log"
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