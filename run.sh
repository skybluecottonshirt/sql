# cleanup
if [ -f ./a.out ]
then 
	rm ./a.out 
fi 

# begin build 
yacc parser.y 
lex lex.l
clang -g -O0 common.c lex.yy.c y.tab.c 2>/dev/null


# test
./a.out < test.sql
