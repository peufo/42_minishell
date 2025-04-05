#!/bin/bash

VALGRIND="valgrind"
VALGRIND+=" --leak-check=full"
VALGRIND+=" --track-fds=yes"
VALGRIND+=" --show-leak-kinds=all"
VALGRIND+=" --track-origins=yes"
VALGRIND+=" --log-file=leaks.log"
VALGRIND+=" --suppressions=readline.supp"
VALGRIND+=" --trace-children=yes"
# VALGRIND+=" --gen-suppressions=all"

$VALGRIND ./minishell