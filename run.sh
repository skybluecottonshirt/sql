if [ -f ./a.out ]
then 
	rm ./a.out 
fi 
# begin build 
yacc parser.y 
lex lex.l

clang -g -O0 lex.yy.c y.tab.c


# test

./a.out < test.sql
