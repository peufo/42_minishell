echo "AAAA" > log/redirect/a.out
grep . log/redirect/a.out
echo "BBBB" > log/redirect/a.out > log/redirect/b.out 
grep . log/redirect/a.out log/redirect/b.out
echo "CCCC" >log/redirect/a.out > log/redirect/b.out 
grep . log/redirect/a.out log/redirect/b.out
echo >log/redirect/a.out "DDDD" > log/redirect/b.out 
grep . log/redirect/a.out log/redirect/b.out
echo > log/redirect/a.out "EEEE" > log/redirect/b.out 
grep . log/redirect/a.out log/redirect/b.out
> log/redirect/a.out echo "FFFF" > log/redirect/b.out 
grep . log/redirect/a.out log/redirect/b.out
> log/redirect/a.out  > log/redirect/b.out  echo "GGGG" > log/redirect/c.out 
grep . log/redirect/a.out log/redirect/b.out log/redirect/c.out

# echo "AAAA" >> log/redirect/a.out
# grep . log/redirect/a.out
# echo "BBBB" >> log/redirect/a.out >> log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# echo "CCCC" >>log/redirect/a.out >> log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# echo >>log/redirect/a.out "DDDD" >> log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# echo >> log/redirect/a.out "EEEE" >> log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# >> log/redirect/a.out echo "FFFF" >> log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# >> log/redirect/a.out  >> log/redirect/b.out  echo "GGGG" >> log/redirect/c.out 
# grep . log/redirect/a.out log/redirect/b.out log/redirect/c.out

# echo "AAAA" < log/redirect/a.out
# grep . log/redirect/a.out
# echo "BBBB" < log/redirect/a.out < log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# echo "CCCC" <log/redirect/a.out < log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# echo <log/redirect/a.out "DDDD" < log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# echo < log/redirect/a.out "EEEE" < log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# < log/redirect/a.out echo "FFFF" < log/redirect/b.out 
# grep . log/redirect/a.out log/redirect/b.out
# < log/redirect/a.out  < log/redirect/b.out  echo "GGGG" < log/redirect/c.out 
# grep . log/redirect/a.out log/redirect/b.out log/redirect/c.out