# /bin/echo hi >./log/outfile01 | /bin/echo bye
# /bin/echo <123 <456 hi | /bin/echo 42

#	NE MARCHE PAS
#		cat <a ou grep a <a
#	NE MARCHE PAS
### FUCK OFF
# cd log
# export VAR="out.txt prout"
# echo "test" > $VAR
# echo "test" > out.txt prout
# cat out.txt
# rm -rf out.txt

### REORDER EXPANDS [VARNAME -> TILD -> WILDCARD]
# export VAR="*o*"
# echo $VAR

### IDK  Syntax error ?
# |ls | ls
# <| echo ok
# >| echo sure
# | echo -n oui
# | | |

### HANDLE "é"

# echo "$USERéhaha"
