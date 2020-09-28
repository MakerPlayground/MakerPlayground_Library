# Error message
ERR_OK=0
ERR_CONNECT_WIFI=1
ERR_CONNECT_SERVER=2
ERR_CLIENT_NOT_READY=3
ERR_CONNECT_DEVICE=4
ERR_CONFIG_DEVICE=5
ERR_INTERNAL_ERROR=6
ERR_CONNECTION_OR_SDCARD=7

ERRORS=["OK", "Can't connect to Wifi", "Can't connect to server", "Client is not ready", "Can't communicate to device", "Can't configure device", "Internal error", "Device connection problem or no SD card"]

# PR (Device Monitor)
def PR_INFO(device):
    print("[[I]] \"" + device + "\" ", end='')

def PR_ERR(device):
    print("[[E]] \"" + device + "\" ", end='')

def PR_VAL(device):
    print("[[V]] \"" + device + "\" ", end='')

def PR_DEVICE(device):
    print("\"" + device + "\" ", end='')

def PR_END():
    print("\0")

# logging
LOG_INTERVAL = 1000

def MP_LOG(device, name):
    PR_INFO(name)
    device.printStatus()
    PR_END()

def MP_LOG_P(device, name):
    MP_LOG(device, name)

def MP_ERR(name, status_code):
    PR_ERR(name)
    print(ERRORS[status_code])
    PR_END()

# utility functions
def map(x, in_min, in_max, out_min, out_max):
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min

def constrain(x, min, max):
    if x < min:
        return min
    elif x > max:
        return max
    else:
        return x
