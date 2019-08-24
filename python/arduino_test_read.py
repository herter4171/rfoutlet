import serial
ser = serial.Serial('/dev/ttyACM0', 9600)


def line_to_list(line):
    """ Parses line string into a list of three ints."""
    good_line = True
    req_len = 3
    
    try:
        # Remove whitespace and split by comma
        line = line.strip()
        line = [int(x) for x in line.split(',')]
        
        # ValueError will be thrown for non-numbers or wrong length
        if not len(line) == req_len:
            msg = "ERROR: Expect {} ints.  Got {}".format(req_len, line)
            raise ValueError(msg)
    except ValueError:
        good_line = False
    finally:
        # Need validity of the line and the parsed list
        return [good_line, line]

# Simple format to print what each value corresponds to
msg_str = "Light: {}, Moisture {}, Reserve Level: {}"

# Print Arduino sensor data indefinitely (till stopped)
while 1: 
    if(ser.in_waiting > 0):
        line = ser.readline()
        [good_line, line] = line_to_list(line)
        if good_line:
            print(msg_str.format(*line))
