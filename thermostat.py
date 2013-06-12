class Thermostat:
  def __init__(self, device=None):
    """
    Searh for valid serial port with thermostat attached
    or use one specified by device string. Then open connection to it.

      device: string, valid OS serial device name (passed to pySerial)
    """
    pass

  def temp_get(self):
    """
    Return tuple of temperature values acquired by sensors. 
    Negative value means the sensor is absent.

    Returns: list of temperature values
    """
    temp=map(lambda i: -1, range(8))
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
        bytesize: number of bits per character
        parity: parity bit
        stopbits: number of stop bits
        rtscts: enable hardware flow control

        Returns: none
    """
    pass

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
