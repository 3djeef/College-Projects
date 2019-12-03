import RPi.GPIO as GPIO
import telepot
from telepot.loop import MessageLoop
import time, datetime
import random

white = 26
yellow = 19
red = 13
green = 6

now = datetime.datetime.now()
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

#LED White
GPIO.setup(white, GPIO.OUT)
GPIO.output(white, 0) #off initialy

#LED yellow
GPIO.setup(yellow, GPIO.OUT)
GPIO.output(white, 0) #off initialy

#LED red
GPIO.setup(red, GPIO.OUT)
GPIO.output(red, 0) #off initialy

#LED green
GPIO.setup(green, GPIO.OUT)
GPIO.output(green, 0) #off initialy

colors = [26, 19, 13, 6]

def handle(msg):
    chat_id = msg['chat']['id'] # Receiving the message from telegram
    command = msg['text']   # Getting text from the message

    print ('Received:')
    print(command)

    if "on" in command:
        message = "Turned on "
        if "white" in command:
            GPIO.output(white, 1)
            message = message + "white "

        if "yellow" in command:
            message = message + "yellow "
            GPIO.output(yellow, 1)

        if "red" in command:
            message = message + "red "
            GPIO.output(red, 1)

        if "green" in command:
            message = message + "green "
            GPIO.output(green, 1)

        if "all" in command:
            message = message + "all"
            GPIO.output(white, 1)
            GPIO.output(yellow, 1)
            GPIO.output(red, 1)
            GPIO.output(green, 1)

        message = message + "light(s)"
        bot.sendMessage(chat_id, message)

    if "off" in command:
        message = "Turned off "
        if 'white' in command:
            message = message + "white "
            GPIO.output(white, 0)

        if "yellow" in command:
            message = message + "yellow "
            GPIO.output(yellow, 0)

        if "red" in command:
            message = message + "red "
            GPIO.output(red, 0)

        if "green" in command:
            message = message + "green "
            GPIO.output(green, 0)

        if "all" in command:
            message = message + "all"
            GPIO.output(white, 0)
            GPIO.output(yellow, 0)
            GPIO.output(red, 0)
            GPIO.output(green, 0)

        message = message + "light(s)"
        bot.sendMessage(chat_id, message)

    if "dance" in command:
        message = "started "
        message = message + "dancing"
        message = "All lights " + message
        bot.sendMessage(chat_id, message)

        for _ in range(0, random.randint(10, 30)):
            light = colors[random.randint(0, 3)]
            GPIO.output(light, 1)
            time.sleep(0.5)
            GPIO.output(light, 0)

        message = "All lights stopped dancing"
        bot.sendMessage(chat_id, message)


if __name__ == '__main__':
    bot = telepot.Bot([OMITTED API KEY])
    print(bot.getMe())
    MessageLoop(bot, handle).run_as_thread()

    print("Telegram Bot up and running")

    while True:
        time.sleep(10)

