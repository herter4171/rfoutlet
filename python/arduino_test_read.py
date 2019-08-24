import serial
ser = serial.Serial('/dev/ttyACM0', 9600)


def line_to_list(line):
    good_line = True
    req_len = 3
    
    try:
        line = line.strip()
        line = [int(x) for x in line.split(',')]
        
        if not len(line) == req_len:
            msg = "ERROR: Expect {} ints.  Got {}".format(req_len, line)
            raise ValueError(msg)
    except ValueError:
        good_line = False
    finally:
        return [good_line, line]

msg_str = "Light: {}, Moisture {}, Reserve Level: {}"

while 1: 
    if(ser.in_waiting > 0):
        line = ser.readline()
        [good_line, line] = line_to_list(line)
        if good_line:
            print(msg_str.format(*line))
