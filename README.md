T1t1t-Analysis
=============

Note: These codes are old and buggy.
  An updated version is located in the VBF_H repository, labelled ExampleT1t1tAnalysis.C and ExampleT1t1tAnalysis.h
  
  
  
MyClass.h and MyClass.c files for a test T1t1t scan

The scan involved is the gluino pair production resulting in the production of 4 tops and 2 LSPs. The input files 
were .lhe and were read through Delphes -  the detector response simulation (see repository Delphes-3.10) 
After running through Delphes, the output were ROOT files and were TTree structured. 
The .h and .c MyClass files are used to analyse the Delphes tree and extract the kinematic properties of the particles involved.
