# Lab 4 Skeleton
#
# Based on of_tutorial by James McCauley

from pox.core import core
import pox.openflow.libopenflow_01 as of
import pox.lib.packet as pkt
from pox.lib.packet.ethernet import ethernet

log = core.getLogger()

table = {}
firewall = {}

class Firewall (object):
  """
  A Firewall object is created for each switch that connects.
  A Connection object for that switch is passed to the __init__ function.
  """
  def __init__ (self, connection):
    # Keep track of the connection to the switch so that we can
    # send it messages!
    self.connection = connection

    # This binds our PacketIn event listener
    connection.addListeners(self)

  def addRule(event, dl_type=0x800, nw_proto=1, port=0, src_port=of.OFPP_ALL):
    firewall[(event.connection, dl_type, nw_proto, port, src_port)] = True
  
  def do_firewall (self, packet, packet_in):
    log.info("Firewall is running")
  
    if dst_port is None:
      msg = of.ofp_packet_out(resend = event.ofp)
      msg.actions.append(of.ofp_action_output(port = of.OFPP_ALL))
      msg.send(event.connection)
    else:
      if (packet.type == ethernet.IP_TYPE):
        ipv4_packet = packet_in.find("ipv4")
        src_ip = ipv4_packet.srcip
        src_port = ipv4_packet.dstport
        dst_ip = ipv4_packet.dstip
        dst_port = ipv4_packet.dstport
        msg = of.ofp_flow_mod()
        msg.match.dl_type = packet.dl_type
        msg.match.nw_proto = packet.nw_proto
      if (nw_proto != 1):
        msg.match.tp_src = packet.tp_src
      msg.match.dl_dst = packet.src
      msg.match.dl_src = packet.dst
      msg.idle_timeout = 10
      msg.hard_timeout = 25
      msg.actions.append(of.ofp_action_output(port = event.port))
      msg.send(event.connection)
    
      msg = of.ofp_flowmod()
      msg.match.dl_type = packet.dl_type
      msg.match.dl_src = packet.src
      msg.match.dl_dst = packet.dst
      msg.idle_timeout = 10
      msg.hard_timeout = 25
      msg.actions.append(of.ofp_action_output(port = dst_port))
      msg.send(event.connection, resend = packet_in)

  
    # The code in here will be executed for every packet.

  def _handle_PacketIn (self, event):
    """
    Handles packet in messages from the switch.
    """
    packet = event.parsed # This is the parsed packet data.
    if not packet.parsed:
      log.warning("Ignoring incomplete packet")
      return
    table[(event.connection,packet.src)] = event.port
    dst_port = table.get((event.connection,packet.dst))

    packet_in = event.ofp # The actual ofp_packet_in message.
  
    self.do_firewall(packet, packet_in)

def launch ():
  """
  Starts the component
  """
  def start_switch (event):
    log.debug("Controlling %s" % (event.connection,))
    Firewall(event.connection)
  core.openflow.addListenerByName("ConnectionUp", start_switch)
