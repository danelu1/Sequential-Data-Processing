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
-> "--st<delta>"(where delta is an "int"), for finding out data frequency on intervals of the form [p*delta, (p+1)*delta], with "p" a whole number.

For the first task of the homework I had to divide an input formed of "timestamp" and "data" in lists formed of only "k" elements for each window(where "k" is 5 in the homework) and check if the middle element for each list is in the interval [mean-sigma, mean + sigma] where "mean" is computed for each iteration through the input and represents the average value of the data(same for "sigma", which is the standard deviation of the data). I considered some adjacent lists that point to the initial one received as input and started iterating. For each iteration I added the first "k" nodes of the list in other list, for which I computed the "mean" and "standard deviation" using functions implemented in "linked_list.h" and searched for the middle node. I checked than if the data from the middle node is in the range specified previously. If not, I add it in a list to keep track of the nodes that must be permanently removed. The iterations stop when a counter defined at the beginning of the function reaches the "len-k+1" value, because we can not iterate more than this. At the end, I remove each node that doesn't fit the problem from the initial list.

For the first part of the second task, I had to do something similar with the first one, but this time I extracted for each iteration the median element of each window that contains "k" consecutive elements, after firstly sorting the initial list.

For the second part of the second task, I did the same, but this time the filtering of the data is done based on the mean value for each window of "k" consecutive elements.

For the third task, I had to check for each two consecutive nodes in the input list if their timestamp difference is in the interval [100, 1000] (ms), to see if an uniformization is needed between the two nodes. If so, than I change the timestamp of the cutrent node in the average between its timestamp and the previous nodes' timestamp and its data in a similar way and then add the new node to a final list. Otherwise, I just add the node in the final list.

For the fourth task, I had to complete gaps between two nodes(with the timestamp difference greater than 1000) with new data, generated using certain methods. For each node that satisfies the previous condition, I extract the first "k"(in our case 3) elements before the first node and the first "k" elements after the last node(first and last node with timestamp difference greater than 1000) and add these elememts in two sepparate lists. Than, while the timestamp of the first element is less than or equal to the timestamp of the last element, I have some certain cases in which I add the generated data in the final list, the most important being the ones where I compute a scaling factor for each interval, a "weight" function and the data generated with the help of the previous functions, using the formulas provided in the homework description. I raise the timestamp with 200 for each iteration.