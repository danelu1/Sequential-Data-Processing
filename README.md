# Sequential-Data-Processing
First homework for the data structures course.
An implementation of some machine learning methods used for correction of errors, data uniformization and data completion. The only data structure that I used was a doubly linked list.
The code can be run by executing:
./tema1 "command", where "command" can be each of the following:
-> "--e1", for data correction using statistics methods;
-> "--e2", for data correction using median filter;
-> "--e3", for data correction using the mean value of the segmented sample;
-> "--u", for data uniformization;
-> "--c", for data completion;
-> "--st"<delta>(where delta is an "int"), for finding out data frequency on intervals of the form [p*delta, (p+1)*delta], with "p" a whole number.