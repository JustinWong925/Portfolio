#!/usr/bin/python

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel
from mininet.cli import CLI
from mininet.node import RemoteController

class lab4_topo(Topo):
  def build(self):
    s1 = self.addSwitch('s1')
    s2 = self.addSwitch('s2')
    s3 = self.addSwitch('s3')
    s4 = self.addSwitch('s4')
    s5 = self.addSwitch('s5')

    h1 = self.addHost('h1',mac='00:00:00:00:00:01',ip='10.0.0.2/8',\
              defaultRoute="h1-eth0")
    h2 = self.addHost('h2',mac='00:00:00:00:00:02',ip='192.168.0.20/24',\
              defaultRoute="h2-eth0")
    h3 = self.addHost('h3',mac='00:00:00:00:00:03',ip='192.168.0.30/24',\
              defaultRoute="h3-eth0")
    h4 = self.addHost('h4',mac='00:00:00:00:00:04',ip='192.168.0.40/24',\
              defaultRoute="h4-eth0")
    h5 = self.addHost('h5',mac='00:00:00:00:00:05',ip='192.168.0.50/24',\
              defaultRoute="h5-eth0")
    h6 = self.addHost('h6',mac='00:00:00:00:00:06',ip='172.16.0.2/16',\
              defaultRoute="h6-eth0")
    h7 = self.addHost('h7',mac='00:00:00:00:00:07',ip='10.10.10.10/8',\
              defaultRoute="h7-eth0")
    h8 = self.addHost('h8',mac='00:00:00:00:00:08',ip='172.16.5.2/16',\
              defaultRoute="h8-eth0")
    h9 = self.addHost('h9',mac='00:00:00:00:00:09',ip='10.20.30.40/8',\
              defaultRoute="h9-eth0")
    h10 = self.addHost('h10',mac='00:00:00:00:00:0A',ip='10.11.12.13/8',\
              defaultRoute="h10-eth0")
    h11 = self.addHost('h11',mac='00:00:00:00:00:0B',ip='172.16.32.64/16',\
              defaultRoute="h11-eth0")
    h12 = self.addHost('h12',mac='00:00:00:00:00:0C',ip='192.168.0.60/24',\
              defaultRoute="h12-eth0")

    self.addLink(h1,s1,port2=2)
    self.addLink(h2,s1,port2=3)
    self.addLink(h3,s1,port2=4)
    self.addLink(h4,s1,port2=5)
    self.addLink(h5,s2,port2=3)
    self.addLink(h6,s2,port2=4)
    self.addLink(h7,s2,port2=5)
    self.addLink(h8,s3,port2=2)
    self.addLink(h9,s4,port2=3)
    self.addLink(h10,s5,port2=2)
    self.addLink(h11,s5,port2=3)
    self.addLink(h12,s5,port2=4)

    self.addLink(s1,s2,port1=1,port2=1)
    self.addLink(s3,s2,port1=1,port2=2)
    self.addLink(s3,s4,port1=10,port2=1)
    self.addLink(s4,s5,port1=10,port2=1)

def configure():
  topo = lab4_topo()
  net = Mininet(topo=topo,controller=RemoteController)
  net.start()
  h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11, h12 = \
      net.get('h1', 'h2', 'h3', 'h4', 'h5', 'h6', 'h7',\
      'h8', 'h9', 'h10', 'h11', 'h12')

  h1.cmd("ifconfig h1-eth0 inet6 del fe80::200:ff:fe00:1/64")
  h2.cmd("ifconfig h2-eth0 inet6 del fe80::200:ff:fe00:2/64")
  h3.cmd("ifconfig h3-eth0 inet6 del fe80::200:ff:fe00:3/64")
  h4.cmd("ifconfig h4-eth0 inet6 del fe80::200:ff:fe00:4/64")
  h5.cmd("ifconfig h5-eth0 inet6 del fe80::200:ff:fe00:5/64")
  h6.cmd("ifconfig h6-eth0 inet6 del fe80::200:ff:fe00:6/64")
  h7.cmd("ifconfig h7-eth0 inet6 del fe80::200:ff:fe00:7/64")
  h8.cmd("ifconfig h8-eth0 inet6 del fe80::200:ff:fe00:8/64")
  h9.cmd("ifconfig h9-eth0 inet6 del fe80::200:ff:fe00:9/64")
  h10.cmd("ifconfig h10-eth0 inet6 del fe80::200:ff:fe00:A/64")
  h11.cmd("ifconfig h11-eth0 inet6 del fe80::200:ff:fe00:B/64")
  h12.cmd("ifconfig h12-eth0 inet6 del fe80::200:ff:fe00:C/64")

  CLI(net)

  net.stop()


if __name__ == '__main__':
  configure()
