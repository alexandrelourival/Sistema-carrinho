import keyboard  # using module keyboard
import serial

conexao = serial.Serial("COM6", 115200)
estado = '0'

while True:  # making a loop
    try:  # used try so that if user pressed other than the given key error will not be shown
        if keyboard.is_pressed('1'):  # if key 'q' is pressed 
            print('voce apertou 1')
            #keyboard.on_press_key('1')
            estado = '1'
        elif keyboard.is_pressed('2'):
            print('voce apertou 2')
            #keyboard.on_press_key('2')
            estado = '2'
        else:
            pass
        if estado == '1':
            conexao.write(b'1')
            #print("frente")
        elif estado == '2':
            conexao.write(b'2')
            #print("tras")
        else:
            pass
    except:
        break  # if user pressed a key other than the given key the loop will break