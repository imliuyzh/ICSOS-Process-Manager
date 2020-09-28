# 143BManager
This project develops a simple process and resource manager. The manager provides the basic operations invoked by processes to create and destroy processes, and to request and release resources. A manually invoked timeout function mimics the behavior of preemptive scheduling. 

## Background
### Process
A process can be in one of three states: ready, running, blocked. It typically cycles through the states many times throughout its lifetime:

<img src="https://i.ibb.co/3MX25Vf/ch1img1v2.png" />
<br />

Each process is represented by a data structure called the process control block (PCB). The PCBs are organized as a fixed-size array, PCB[n], where n is the maximum number of processes that can be created. Each process is uniquely identified by the PCB index:

<img src="https://i.ibb.co/ZcrjMhr/ch1img2v2.png" />
<br />

Each PCB only consists of the following fields, organized as a structure:

<img src="https://i.ibb.co/wWmkNp7/ch1img3v2.png" />
<br />

* State: The current state of the process i
* Parent: Index of the process that created process i
* Children: A linked list of processes that process i has created
* Resources: A linked list of resources that process i is holding

For scheduling purposes, the manager maintains all PCBs on one of several lists. Blocked processes are kept on waiting lists. All ready processes are kept on a Ready List (RL).

### Resource
Processes may request, acquire, and later release a fixed set of resources. When a process requests a resource that is unavailable, the process becomes blocked.

Each resource is represented by a data structure called the resource control block (RCB). Analogous to the PCBs, the RCBs are organized as a fixed-size array, RCB[m], where m is the number of resources in the system. Each resource is uniquely identified by the RCB index. Each RCB consists only of the following fields, organized as a structure:

<img src="https://i.ibb.co/w0QqfFG/ch1img5v2.png" />
<br />

* State: The current state of the resource r (free/allocated)
* Waitlist: A linked list of processes blocked on the resource