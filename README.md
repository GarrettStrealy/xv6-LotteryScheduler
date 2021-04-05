# xv6-LotteryScheduler

In this project, I replaced the round robin scheduler in xv6 with a lottery 
scheduler. The basic idea is simple: assign each running process a slice of the processor in proportion 
to the number of tickets it has. The more tickets a process has, the more it runs. Each 
time slice, a randomized lottery determines the winner of the lottery; that winning 
process is the one that runs for that time slice.

The objectives for this project:
- To gain further knowledge of a real kernel, xv6.
- To familiarize yourself with a scheduler.
- To change that scheduler to a new algorithm.
- To make a graph to show your project behaves appropriately.


