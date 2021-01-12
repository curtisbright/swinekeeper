find .. -name "*.cpp" | perl DirToRules.pl > rules.txt
perl RulesToGNUMake.pl rules.txt > makefile
make depends
perl RulesToGNUMake.pl rules.txt > makefile

