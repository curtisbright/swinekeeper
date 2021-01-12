dir /s /b ..\*.cpp | perl dirtorules.pl > rules.txt
perl rulestognumake.pl rules.txt > makefile
make depends
perl rulestognumake.pl rules.txt > makefile
