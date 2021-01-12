# reformats all error messages in GCCs output, 
# so that the error parser of the MS DevStudio 
# can read it. 
# 
# To use it, you have to add a Tool to the MS DevStudio 
# with the following settings: 
# Command: gmake.EXE   (name of gnu make) 
# Arguments: -s 2>&1 | perl reformaterr.pl
# Initial Directory: $(WkspDir)\..\build_cygwin
# Check the Checkbox 'Use Output Window' 
# 
# Now you can doubleclick on a error message in the output 
# window and DevStudio will jump to the appropriate location. 

$| = 1; 
while (<>) {
   if (m#^(\S*?):(\d+):\s*(.*)$#) 
   {
      print "$1($2): $3\n"; 
   }
   else 
   {
      print;
   }
}