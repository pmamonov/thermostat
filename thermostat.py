from serial import Serial

class Thermostat:
  def __init__(self, device=None):
    """
    Searh for valid serial port with thermostat attached
    or use one specified by device string. Then open connection to it.

      device: string, valid OS serial device name (passed to pySerial)
    """
    if not device: raise NameError, "Device search not implemented"
    self.sr = Serial(device, timeout = 0.1)
    self.temp_init()

  def cmd(self, s):
    while self.sr.read(1024): pass
    self.sr.write(s+'\n')
    r=self.sr.readlines()
    if not r: raise NameError, "No reply from device"
#    if r[-1].strip()[:3] == "ERR": raise NameError, "Error %s"%(r[-1].strip()[3:])
    if r[-1].strip()[:3] == "ERR": raise NameError, "Device communication error"
    if r[-1].strip() == "OK": return r[0].strip()
    raise NameError, "Device reply not understood"

  def temp_init(self):
    r = int(self.cmd("snsi"))
    s=[]
    for i in xrange(8):
      if (r & (1<<i)): s.append(True)
      else: s.append(False)
    self.sens_avail = s
    return s


  def temp_get(self):
    """
    Return dictionary of temperature values acquired by sensors. 
    Only values of detected sensors are returned

    Returns: dict of temperature values
    """
    r = self.cmd("temp").split(' ')
    temp = {}
    for iv in r: 
      i,v = map(int, iv.split(":"))
      if self.sens_avail[i]: temp[i] = v/256.
    return temp


  def TEM_set(self, tem_id, state, duration):
    """
    Enable TEM specified by tem_id for a given amount of time 
    or disable it immediately.
 
      tem_id: TEM ID number (0-3)

      state: integer number, 0 - OFF, positive value - heat, negative - cool (-32767 - 32767)

      duration: state duration in ms

      Returns: none

    """
    pass


  def TEM_get(self, tem_id):
    """
    Returns current state of TEM identified by `tem_id`

      tem_id: TEM ID number (0-3)

      Returns: TEM's state value
    """
    curr_state = 0
    return curr_state


  def lswitch_get(self):
    """
      Returns bitmask with limit switches states

        Returns: integer number, bits encode switches states.
    """
    return 0

  def serial_setup(self, baudrate=9600, bytesize=8, parity='N', stopbits=1, rtscts=False):
    """
      Setup serial communication with scales.

        baudrate: speed of communication
        bytesize: number of bits per data word
        parity: enable parity checking
        stopbits: number of stop bits
        rtscts: enable hardware flow control

        Returns: none
    """
    pass

  def serial_start(self):
    self.cmd("com")

  def serial_end(self):
    self.sr.write('\xff')

  def serial_send(self, string):
    """
      Send string to scales.
      
        string: string to send

        Returns: none
    """
    pass

  def serial_recv(self, length=-1):
    """
      Receive up to `length` bytes from scales. Non blocking.

        length: number of bytes to recieve.

        Returns: string contining up to `length` bytes
    """
    return ""
