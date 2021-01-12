# takes the output of 'gcc -M' and 
# appends all usefull entries to file with the dependencies. 
# call as 
# perl addtodepend.pl <FILEID> <GCC_M_OUTPUT> <TARGETFILE>
# see RulesToMake.pl 

undef $/; 
open IN, $ARGV[1] or exit(0); 
open OUT, ">> ".$ARGV[2] or die; 

$_ = <IN>; 

@files = split /[\s\:]+/s; 

print OUT $ARGV[0]."= "; 
foreach $file (@files) 
{
   if ($file =~ /^\.\..*\.h$/)
   { 
      print OUT $file." ";
   }
}
print OUT "\n"; 