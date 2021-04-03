In the analysis folder we have our report in pdf format. We have the m12.csv and m34.csv files
which contains the data of our analysis and we plotted them using the plot12.py and plot34.py.
Each .py files produces two plots- one of error vs parameter and other is runtime vs parameter.
These file can be runned using the command:
$python3 plot12.py
-----or-----
$python3 plot34.py

We also have our .sh files which gives input to the methods to a list of parameters. This produces 
us the output of runtime metric. The above can be runned in the terminal using the commmand:
$run.sh

To get the error metric we can run the error.cpp file by running the following command:
$g++ error.cpp
$./a.out <filename1.txt> <filename2.txt>

here filename1 can be the base12 or base34,
and filename2 can be one of {m1,m2} or {m3,m4} respectively.

This will display the error metric of the method which has been defined in the report.

Lastly we have the report which contains the analysis of subtask3. It contains the graph plotted
using plot12.py and plot34.py. It also contains the trade-off analysis between runtime and utility
and also gives an explanation of the behaviour and trend of the plots we get for each methods.

----note: We did not do the extra credit part------
