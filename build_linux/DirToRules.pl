# takes a list of all cpp files of the 
# project. It accepts output from 
# dir /s /b ..\*.cpp or find .. -name "*.cpp". 
# Creates a list of rules how to build 
# binaries from these files. 

$dirPrefix = "minesweeper/"; 

$projDirs{"gamecontrol"} = 1; 
$projDirs{"minebase"} = 1; 
$projDirs{"minesolver"} = 1; 
$projDirs{"mineui_ptc"} = 1; 
$projDirs{"mineui_glut"} = 1; 
$projDirs{"mineuibase"} = 1; 
$projDirs{"minetest"} = 1; 
$projDirs{"mineui_common"} = 1; 
$projDirs{"storage"} = 1; 
$projDirs{"mineui_qt"} = 1; 

$binDirs{"mineui_ptc"} = 1; 
$binDirs{"minetest"} = 1; 
$binDirs{"mineui_glut"} = 1; 

# open FILES, "dir /s /b ..\\*.cpp |" or die; 
# open FILES, "find .. -name \"*.cpp\" |" or die; 

@files = <>; 

sub beginProj; 
sub beginFile; 
sub buildFinal; 

foreach (@files) 
{
   s:\\:/:g;
   if (m:$dirPrefix([\w_]+)/(\w+\.cpp): || m:\.\./([\w_]+)/(\w+\.cpp):) 
   {
      $proj = $1; 
      $file = $2; 
      if ($projDirs{$proj}) {
         if ($proj ne $curProj) {
            $curProj = $proj; 
            beginProj($proj); 
         }
         beginFile ($proj, $file); 
      }
   }
}
buildFinal(); 
   
$intermediateDir = ""; 
$sourceDir = ""; 

sub beginProj {
   my $proj = $_[0]; 
   $sourceDir = "../${proj}/"; 
   $intermediateDir = "../obj_COMPILER/${proj}/CONFIG/"; 
   # print "MKDIR:../obj_COMPILER/${proj}/\n"; 
   print "MKDIR:$intermediateDir\n"; 
   @projobjects = ();
}

sub beginFile {
   my ($proj, $file) = @_; 
   ($name) = split /\./, $file; 

   $objFile = $intermediateDir.$name.".o"; 
   
   $projObjects{$proj} .= $objFile."+"; 
   $libObjects .= $objFile."+" unless $binDirs{$proj}; 

   print "COMPILE:".$objFile.":".$sourceDir.$file."\n"; 
}

sub buildFinal {
   my $libraryDir = "../obj_COMPILER/lib/CONFIG/"; 
   my $executableDir = "../bin_COMPILER/CONFIG/"; 

   chop $libObjects; 
   chop $projObjects{"minetest"}; 
   chop $projObjects{"mineui_ptc"}; 

   $lib = $libraryDir."minesweeper.a"; 
   print "MKDIR:$libraryDir\n"; 
   print "LINKLIB:".$lib.":".$libObjects."\n"; 


   print "MKDIR:$executableDir\n";   
   foreach $binDir (keys %binDirs) {
      print "BUILD:".$executableDir.$binDir.":".$projObjects{$binDir}."+".$lib."\n"; 
   }
}




