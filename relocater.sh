####################
####  Macro to move PREP / MG root files to another directory for analysis
####  Author :  Dominic Smith, University of Bristol
###   Date : 26/02/2014
####################

Comp_dir=../Comparisons/

if [ -d "$Comp_dir" ]; then
    echo $Comp_dir already exists
fi    


echo Finding your files...


ls | grep "PREP" > FILES.txt



cp `cat FILES.txt` $Comp_dir

echo Files copied to Comparisons directory

cd $Comp_dir