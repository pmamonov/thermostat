import serial
from serial import Serial

class Thermostat:
  def __init__(self, device=None):
    """
    Searh for valid serial port with thermostat attached (not implemented)
    or use one specified by device string. Then open connection to it.

    ARGUMENTS
      device: string, valid OS serial device name (passed to pySerial)

    RETURN
      none
    """
    if not device: raise NameError, "Device search not implemented"
    self.sr = Serial(device, timeout=1, baudrate=115200)
#    self.sr = Serial(device, timeout=1)
    self.temp_init()

  def cmd(self, s, newln=True):
    self.sr.flushInput()
    if newln: self.sr.write(s+'\n')
    else: self.sr.write(s)
    r1,r2=self.sr.readline(),self.sr.readline()
    print "%s -> %s [%s]" % tuple( map(lambda x: x.strip(), (s,r1,r2)))
    if not r2: raise NameError, "No reply from device"
    if r2.strip()[:3] == "ERR": raise NameError, "Device communication error"
    if r2.strip() == "OK": return r1.strip()
    raise NameError, "Device reply not understood"

  def temp_init(self):
    """
    Initialize temperature sensors.
    
    ARGUMENTS
      none

    RETURNS
      List of ID's of detected sensors
    """
    r = int(self.cmd("snsi"))
    s=[]
    for i in xrange(8):
      if (r & (1<<i)): s.append(i)
#      else: s.append(False)
    self.sens_avail = s
    return s


  def temp_get(self):
    """
    Return dictionary of temperature values acquired by sensors. 
    Only values of detected sensors are returned

    ARGUMENTS
      none

    RETURN
      dictinary of temperature values: {ID1:T1, ID2:T2, ...}
    """
    r = self.cmd("temp").split(' ')
    temp = {}
    for iv in r: 
      i,v = map(int, iv.split(":"))
#      if self.sens_avail[i]: 
      temp[i] = v/256.
    return temp


  def TEM_set(self, tem_id, state, duration):
    """
    Enable TEM specified by tem_id for a given amount of time 
    or disable it immediately.

    ARGUMENTS
 
      tem_id: TEM ID number (0-3)

      state: integer number, 0 - OFF, positive value - heat, negative - cool (-32767 - 32767)

      duration: state duration in ms

    RETURN
      none
    """
    self.cmd("tem %d %d %d"%(tem_id, state, duration))


  def TEM_get(self, tem_id):
    """
    Returns current state of TEM identified by `tem_id`

    ARGUMENTS

      tem_id: TEM ID number (0-3)

    RETURN
      TEM's state
    """
    r = self.cmd("temq %d"%tem_id)
    return int(r)
    #return ((1,-1)[ r&2 == 0],0)[ r&1 ]


  def lswitch_get(self):
    """
      Get limit switches states

      ARGUMENTS
        none

      RETURN
        list of integers, corresponding to limit switches states
    """
    x = int(self.cmd("lsq"))
    return map(lambda i: (1,0)[x & (1<<i) == 0], range(8))

  def serial_setup(self, baudrate=9600, bytesize=8, parity='N', stopbits=1, rtscts=False):
    """
      Setup serial communication with scales.

      ARGUMENTS

        baudrate: speed of communication
        bytesize: number of bits per data word
        parity: enable parity checking
        stopbits: number of stop bits
        rtscts: enable hardware flow control

      RETURN 
        none
    """
    self.cmd("comi %d %d %s %d %d"%(baudrate, bytesize, parity, stopbits, (0,1)[rtscts] ))

  def serial_start(self):
    """
    Start scales communication session. Call it before using serial_send()/serial_recv()

    ARGUMENTS
      none

    RETURN
      none
    """
    self.cmd("com")

  def serial_end(self):
    """
    Finish scales communication session.

    ARGUMENTS
      none

    RETURN
      none
    """
    self.cmd('\xff',False)

  def serial_send(self, s):
    """
      Send string to scales. A call to serial_start() 
      is required before use of this function.

      ARGUMENTS
      
        string: string to send

      RETURN

        none
    """
    self.sr.write(s)

  def serial_recv(self, l=1):
    """
      Receive up to `length` bytes from scales. A call is blocking. 
      Timeout is set in __init__() function.
      A call to serial_start() is required before use of this function.

      ARGUMENTS

        l: number of bytes to recieve.

      RETURN
        string containing up to `length` bytes
    """
    return self.sr.read(l)

  def serial_readline(self):
    """
      Receive string from scales. A call is blocking. 
      Timeout is set in __init__() function.
      A call to serial_start() is required before use of this function.
      
      ARGUMENTS
        none

      RETURN
        string contining up to `length` bytes
    """
    return self.sr.readline(1)
