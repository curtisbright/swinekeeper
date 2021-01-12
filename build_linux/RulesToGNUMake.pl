# Creates a makefile from a 'rules' file.
# It takes the output from DirToRules.pl in stdin. 
# It can read a file that contains the dependencies to 
# the headers and insert the approriate dependencies. 

$config = "debug"; 
$compiler = "linux"; 

# Open the file with the header dependencies. 
# this file is usually created by calling the 
# makefile created by this script with 'make depends'.
# If there is no such file, it is ignored. 
if (open DEP, "depends.inc") 
{
   while (<DEP>) {
      chop; 
      ($projfile, $incls) = split /=/; 
      $dependant{$projfile} = $incls; 
   }
}

print "# Automagically generated makefile \n"; 
print "include CompilerSettings.inc\n"; 
print "\n"; 

@files_orig = <>; 

print "default: debug\n\n"; 

print "all: debug release copydata\n\n"; 
foreach ("clean", "library", "mineui_ptc", "mineui_glut", "minetest", "mkdirs", "copydata") 
{
   print "$_: ".$_."_debug ".$_."_release\n\n"; 
}


foreach $config ("debug", "release") 
{

$cflags_var = "\$(CFLAGS_".uc($config).")"; 
$linkflags_var = "\$(LINKFLAGS_".uc($config).")"; 

$linkflags_projvar{"mineui_ptc"} = "\$(LINK_PTC_".uc($config).")"; 
$libraries_projvar{"mineui_ptc"} = "\$(LIBRARIES_PTC_".uc($config).")"; 
$cflags_projvar{"mineui_ptc"} = "\$(CFLAGS_PTC_".uc($config).")"; 

$linkflags_projvar{"mineui_glut"} = "\$(LINK_GLUT_".uc($config).")"; 
$libraries_projvar{"mineui_glut"} = "\$(LIBRARIES_GLUT_".uc($config).")"; 
$cflags_projvar{"mineui_glut"} = "\$(CFLAGS_GLUT_".uc($config).")"; 


@files = @files_orig; 

foreach (@files) 
{
   s/CONFIG/$config/g; 
   s/COMPILER/$compiler/g; 
}

# main targets, build all executables & libaries 
print "$config:mkdirs_$config"; 
foreach (@files) 
{
   if (/^LINKLIB:(.*?):(.*)/) {
      $lib = $1; 
      print " $lib"; 
   }
   if (/^BUILD:(.*?):(.*)/) {
      $exe = $1; 
      print " $exe"; 
   }      
}  
print "\n\n"; 

# create a target for each executable and target file 
foreach (@files) 
{
   if (/^LINKLIB:(.*?):(.*)/) {
      $lib = $1; 
      $files = $2; 
      $files =~ s/\+/ /g; 
      ($libname) = ($lib =~ m#/(\w+\.\w+)#); 
      print "library_$config: mkdirs_$config $lib\n\n"; 
      print "$lib:$files\n"; 
      print "\techo \"Creating library $libname\"\n"; 
      print "\tar -r \$@ \$^\n\n"; 
   }
   if (/^BUILD:(.*?):(.*)/) {
      $exe = $1; 
      $files = $2; 
      $files =~ s/\+/ /g; 
      ($exename) = ($exe =~ m#/(\w+)$#); 
      print "${exename}_$config: $exe\n\n"; 
      print "$exe:$files\n"; 
      print "\techo \"Creating executable $exename\"\n"; 
      print "\t\$(CC) $linkflags_var ".$linkflags_projvar{$exename}." -o $exe\$(EXE_POSTFIX) \$^ ".$libraries_projvar{$exename}."\n\n"; 
  
   }
}

# make the directories for the targets and executables 
print "mkdirs_$config:\n"; 
foreach (@files) 
{
   if (/^MKDIR:(.*)/) { 
      $dir = $1; 
      # $dir =~ s:/:\\:g; 
      print "\t-mkdir -p $dir\n"; 
   }
}
print "\n"; 

# compile each c++ file 
foreach (@files) 
{
   if (/^COMPILE:(.*?):(.*)/) {
      $obj = $1; 
      $file = $2; 
      if ($obj=~m#/(\w+)/\w+/(\w+)\.o#) {
         $fileid = "$1;$2"; 
      }
      else {
         $fileid ="NON"; 
      }
      ($filename) = ($file =~ m#/(\w+/\w+\.\w+)#); 
      ($proj) = ($filename =~ m#^(\w+)/#); 
      print "$obj:$file ".$dependant{$fileid}."\n"; 
      print "\techo \"Compiling $filename\"\n"; 
      print "\t\$(CC) $cflags_var ".$cflags_projvar{$proj}." -c \$< -o \$@\n\n"; 
   }
}

print "copydata_$config:\n"; 
print "\tcp ../resources/*.bmp ../bin_${compiler}/${config}/\n\n";  

# make clean targets 
print "clean_$config:\n"; 
foreach (@files) 
{
   if (/^COMPILE:(.*?):/ || /^BUILD:(.*?):/ || /^LINKLIB:(.*?):/ ) {
      print "\t-rm $1\n"; 
   }
}
print "\n"; 

} # foreach $config 

@files = @files_orig; 

foreach (@files) 
{
   s/CONFIG/debug/g; 
   s/COMPILER/$compiler/g; 
}

# creating the dependencies with the header files 

$cflags_var = "\$(CFLAGS_DEBUG)"; 
$cflags_projvar{"mineui_ptc"} = "\$(CFLAGS_PTC_DEBUG)"; 

$depends_inc = "depends.inc"; 
$depends_tmp = "dependstmp.txt"; 
print "depends:\n"; 
print "\t-rm $depends_inc\n"; 
foreach (@files) 
{
   if (/^COMPILE:(.*?):(.*)/) {
      $obj = $1; 
      $file = $2; 
      if ($obj=~m#/(\w+)/\w+/(\w+)\.o#) {
         $fileid = "$1;$2"; 
      }
      else {
         $fileid ="XXX"; 
      }
      ($filename) = ($file =~ m#/(\w+/\w+\.\w+)#); 
      ($proj) = ($filename =~ m#^(\w+)/#); 
      print "\t-\$(CC) $cflags_var ".$cflags_projvar{$proj}." -M -c $file -o $depends_tmp\n";
      print "\tperl addtodepend.pl \"$fileid\" $depends_tmp $depends_inc\n"; 
   }
}
print "\t-rm $depends_tmp\n\n"; 


