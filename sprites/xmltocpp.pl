#!
use strict;
use warnings;

use Data::Dumper;

my %frames;

while (my $line = <>) {
   my $frame = 1;
   my $height;
   my $width;
   my $xpos;
   my $ypos;
   my $type;
   my $string;
   while ($line  =~ /<(.*?)>/g) {
      if ($1 =~ /([^\\\/]*)\.png/) {
         print "/*****$1*****/\n";
      }
      if ($1 =~ /frame="(.*?)".*?height="(.*?)".*?userdata="(.*?)".*?width="(.*?)".*?x="(.*?)".*?y="(.*?)"/) {
         $frame = $1+1;
         $height = $2;
         $width = $4;
         $xpos = $5;
         $ypos = $6;
         if (defined $3) { $type = $3 }
         else { $type = "nodata" }
         
         $string = $frames {$frame};
         if (defined $string) {
            my $tmp = "\t\t$type.push_back(sf::FloatRect($xpos, $ypos, $width, $height));\n";
            $frames {$frame} = "$tmp$string";
         } else {
            $frames {$frame} = "\t\t$type.push_back(sf::FloatRect($xpos, $ypos, $width, $height));\n";
         }
      }
   }   
}
for my $key ( sort {$a<=>$b} keys %frames) {
   print "/***FRAME $key***/\n $frames{$key}\t\tframeVector.push_back(Frame(hit, hurt, clip));\n\t\thit.clear();\n\t\thurt.clear();\n\t\tclip.clear();\n";
}
 










