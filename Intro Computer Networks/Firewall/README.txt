README

Lab4: "Simple" Firewall using OpenFlow
Justin Wong (jujwong@ucsc.edu)

To run: Have 2 terminal windows open in mininet.
The first will go to the pox directory and enter "./pox.py misc.firewall" this will begin the controller.
The second will go to the mininet directory and enter "sudo ./lab4topo" this will assign the topology for mininet.

Lab4.py

The goal of this lab was to set up a simple firewall that would mainly deal with IPv4 packets
if there were IPv4 packets they needed to have a transport layer header with them, this was seen as 
source port and destination port addresses, in addition to their standard source IP and destination IP
addresses. If the packets had IP addresses but not both port numbers they would be dropped. All other types
of packets would be allowed to transfer including ARPs.

This lab also provided an oppurtunity to get more familiar with the Python language as well as using virtual machines
to provide a controlled environment to test networks.

Starting with the lab4_skeleton code:
When this controller is started there is a switch that is activated, meaning all the packets in this network
will have to go through this switch in order to pass information. Anytime there is a connection started, this
is caught with the connectionUp which will go to _handle_PacketIn to see what to do with the packets that come through.
If the packet is unable to be parsed then it will be dropped, otherwise it will be sent to the firewall code to determine
the proper course of action. If the packet does not have a source port, meaning it does not know where to go it will flood
meaning it resends out of all the ports except for the one that it came from. In addition packets that are not of the "IP" type
should be allowed through and sent to their respective destinations.

If the packet is determined to be of the IP-type, and even further, found with the IPv4 protocol, then different actions will be taken.
The firewall is trying to determine if the packet matches the rule that is set, meaning that if the packet has 
an IP source/destination and port number source and destination it will be allowed through. If it does it will take that information
from the packet and use it to determine where to send it to. Else if will be unable to send it since it will not know where to send to and 
the fact that it broke the rule means that it will be dropped. 

The rule is set as having the correct connection, type, port numbers and ip numbers. Ideally each time the packet comes through the 
firewall it will update the rule if necessary. For this lab it is satisfactory to have the one rule, since that is all that was asked.
The rule should only be checked against IPv4 packets, meaning that ARPs which are also in Layer 2 should be able to be transmitted
without issue.

Lab4topo.py

This file is the mininet topology provided to us. It is a single switch with 4 hosts. The hosts
all have their own mac addresses:00:00:00:00:00:01[2,3,4], and IP addresses: 10.0.1.2/24, 10.0.0.2/24,
10.0.0.3/24, and 10.0.1.3/24. H1 and H4 are on the same subnetwork while H2 and H3 are on the same subnetwork,
but the two subnetworks are separate from one another and thus will need to communicate through the switch. 