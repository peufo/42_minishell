# /bin/echo hi >./log/outfile01 | /bin/echo bye
# /bin/echo <123 <456 hi | /bin/echo 42
# |ls | ls

export NEW=42
env | grep NEW | grep -v GLIB