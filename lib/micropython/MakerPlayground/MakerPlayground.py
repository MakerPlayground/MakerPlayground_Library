import sys

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

# Hardware abstraction functions

if sys.platform == 'MaixPy':
    from Maix import GPIO
    from fpioa_manager import fm
    from machine import Timer, PWM

    class GPIO_DIR:
        IN = GPIO.IN
        OUT = GPIO.OUT

    class GPIO_STATE:
        LOW = 0
        HIGH = 1

    class GPIO_PULL:
        PULL_DOWN = GPIO.PULL_DOWN
        PULL_UP =  GPIO.PULL_UP

    gpio_mapping = [(fm.fpioa.GPIOHS0, GPIO.GPIOHS0),
                    (fm.fpioa.GPIOHS1, GPIO.GPIOHS1),
                    (fm.fpioa.GPIOHS2, GPIO.GPIOHS2),
                    (fm.fpioa.GPIOHS3, GPIO.GPIOHS3),
                    (fm.fpioa.GPIOHS6, GPIO.GPIOHS6),
                    (fm.fpioa.GPIOHS7, GPIO.GPIOHS7),
                    (fm.fpioa.GPIOHS8, GPIO.GPIOHS8),
                    (fm.fpioa.GPIOHS9, GPIO.GPIOHS9),
                    (fm.fpioa.GPIOHS10, GPIO.GPIOHS10),
                    (fm.fpioa.GPIOHS11, GPIO.GPIOHS11),
                    (fm.fpioa.GPIOHS12, GPIO.GPIOHS12),
                    (fm.fpioa.GPIOHS13, GPIO.GPIOHS13),
                    (fm.fpioa.GPIOHS14, GPIO.GPIOHS14),
                    (fm.fpioa.GPIOHS15, GPIO.GPIOHS15),
                    (fm.fpioa.GPIOHS16, GPIO.GPIOHS16),
                    (fm.fpioa.GPIOHS17, GPIO.GPIOHS17),
                    (fm.fpioa.GPIOHS18, GPIO.GPIOHS18),
                    (fm.fpioa.GPIOHS19, GPIO.GPIOHS19),
                    (fm.fpioa.GPIOHS20, GPIO.GPIOHS20),
                    (fm.fpioa.GPIOHS21, GPIO.GPIOHS21),
                    (fm.fpioa.GPIOHS22, GPIO.GPIOHS22),
                    (fm.fpioa.GPIOHS23, GPIO.GPIOHS23),
                    (fm.fpioa.GPIOHS24, GPIO.GPIOHS24),
                    (fm.fpioa.GPIOHS25, GPIO.GPIOHS25),
                    (fm.fpioa.GPIOHS26, GPIO.GPIOHS26)]
    gpio_object = {}

    timers = [Timer.TIMER0, Timer.TIMER1, Timer.TIMER2]
    timer_channels = [Timer.CHANNEL0, Timer.CHANNEL1, Timer.CHANNEL2, Timer.CHANNEL3]
    pwm_object = {}

def pinMode(pin, dir, pull=None, enable_pwm=False, pwm_freq=2000):
    if sys.platform == 'MaixPy':
        # try setup the pin as pwm pin if requested and revert to normal GPIO if all channels are fully occupy
        if enable_pwm:
            if (pin not in pwm_object) and (len(pwm_object) < 12):
                num_pwm = len(pwm_object)
                timer = Timer(timers[num_pwm // 4], timer_channels[num_pwm % 4], mode=Timer.MODE_PWM)
                pwm = PWM(timer, freq=pwm_freq, duty=0, pin=pin)
                pwm_object[pin] = pwm
                return True
        if pin in gpio_object:
            gpio = gpio_object[pin]
            gpio.mode(dir)
            gpio.pull(pull if pull else GPIO.PULL_NONE)
            return True
        elif len(gpio_object) < len(gpio_mapping):
            # get available gpio
            mapping = gpio_mapping[len(gpio_object)]
            # register gpio with pin and store the returned gpio object
            fm.register(pin, mapping[0])
            gpio = GPIO(mapping[1], dir, pull if pull else GPIO.PULL_NONE)
            gpio_object[pin] = gpio
            return True
        # TODO: handle case when the pin is switch between pwm and gpio mode

    return False

def digitalWrite(pin, value):
    if sys.platform == 'MaixPy':
        if pin in pwm_object:
            pwm = pwm_object[pin]
            pwm.duty(100 if value == GPIO_STATE.HIGH else 0)
        else:
            if pin not in gpio_object:
                pinMode(pin, GPIO_DIR.OUT)
            # pinMode may fail so we must check again
            if pin in gpio_object:
                gpio = gpio_object[pin]
                gpio.value(value)

def analogWrite(pin, value):
    if sys.platform == 'MaixPy':
        if pin not in pwm_object:
            pinMode(pin, GPIO_DIR.OUT, enable_pwm=True)
        # pinMode may fail so we must check again
        if pin in pwm_object:
            pwm = pwm_object[pin]
            pwm.duty(value)

def digitalRead(pin):
    if sys.platform == 'MaixPy':
        if pin not in gpio_object:
            pinMode(pin, GPIO_DIR.IN)
        # pinMode may fail so we must check again
        if pin in gpio_object:
            gpio = gpio_object[pin]
            return gpio.value()
    return GPIO_STATE.LOW