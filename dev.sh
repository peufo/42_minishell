#!/bin/bash

SRC_DIR="./src"
PROG="./minishell"
ARGS="./test.sh"
LEAKS_CHECK=true
OUTPUT_FILE=./dev.log

if [ $(uname) = "Linux" ]; then
	LEAKS_CMD="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=leaks.log -s"
else
	#LEAKS_CMD="leaks -quiet --atExit --"
	LEAKS_CMD=""
fi

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
				warning "COMPILATION\ERROR"
			else
				success "COMPILATION\tOK\n"
				info "───────────────────────────────────────────────────\n"
				COMMAND="$PROG $ARGS"
				if $LEAKS_CHECK ; then
					COMMAND="$LEAKS_CMD $COMMAND"
				fi
				if [[ $OUTPUT_FILE != "" ]] ; then
					$COMMAND > "$OUTPUT_FILE" &
					echo "See output file: $OUTPUT_FILE"
				else
					$COMMAND
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