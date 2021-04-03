# Understanding and analyzing trade-offs in software design
**Motivation**:
When we build software, accuracy of the output or utility might not be the only metric to optimize. 
Sure, if we are estimating traffic density on road, we should output the correct density values. 
But maybe latency is also an important metric, that for a given input frame, we get output within a small time. 
Maybe throughput is an important metric, that every unit time, the code generates high number of outputs. 
Maybe keeping the processor temperature under control is necessary, if the software is deployed on a roadside 
embedded board, where there is no AC and ambient temperatures in Delhi shoots to 45 degree Celsius in summer. 
Maybe energy is an important metric, if the roadside embedded board is solar-powered, and can generate only a 
limited amount of energy. Maybe we want to protect the software from hackers, and therefore security is vital too.
These metrics might be at conflict with each other. 
E.g. for higher throughput, processors might run at a higher frequency, thereby draining more power and heating up more. 
Putting security checks against hackers might make the code run slower. This aspect of having multiple metrics to 
optimize, which conflict with each other, is called trade-off. Software design might need careful trade-off analyses.
In addition to metrics, we have to understand three more terms (i) benchmark, (ii) baseline, and 
(iii) methods/parameters, for trade-off analysis. Benchmark is the dataset on which we analyze the trade-offs. 
The video that we used for Assignment 1 part(b), can be benchmark for Assignment 1 part(c). Baseline is the method 
against which we compare other methods/parameters, and see whether we are getting a better or worse trade-off. 
Here we will do an utility-runtime tradeoff analysis for queue density estimation (using background subtraction). 
You need to define your utility metric --- maybe the difference in queue per unit time, compared to baseline, take the 
absolute or squared value of that as error. The lower this error, the higher is your utility. You can take the average/median
of that error over the whole video, to get a single value for utility. Similarly for runtime, you can take the time for 
processing the whole video. You can have a plot, where x-axis is utility and y-axis is runtime, and different points in
that plot will come from different methods/parameters.
For this task's utility-runtime trade-off analysis, we can have the following methods/parameters
**Method1**: sub-sampling frames -- processing every x frame i.e. process frame N and then frame N+x, and for all intermediate 
frames just use the value obtained for N - total processing time will reduce, but utility might decrease as intermediate frames
values might differ from baseline. Parameter for this method is x, how many frames you drop.
**Method2**: reduce resolution for each frame. Lower resolution frames might be processed faster, but having higher errors.
Parameter can be resolution XxY.
**Method3**: split work spatially across threads (application level pthreads) by giving each thread part of a frame to process.
Parameter can be number of splits i.e. number of threads, if each thread gets one split. You might need to take care of 
boundary pixels that different threads process for utility.
**Method4**: split work temporally across threads (application level pthreads), by giving consecutive frames to different 
threads for processing. Parameter can be number of threads.
//---------------------------------------------------------------------------------//
code folder contains our src codes, makefile, and readme to help build the executables.
analysis folder contains some scripts for post-processing analysis.
//---------------------------------------------------------------------------------//
