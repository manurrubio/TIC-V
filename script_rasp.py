#!/usr/bin/env python 
# -*- coding: utf-8 -*-
# lsusb to check device name
#dmesg | grep "tty" to find port name

import serial,time
from vosk import Model, KaldiRecognizer
import pyaudio

 

if __name__ == '__main__':

      print('Running. Press CTRL-C to exit.')
      model = Model("/home/um/Downloads/vosk-model-small-es-0.42")
      rec = KaldiRecognizer(model, 16000) # 16kHz es lo que soporta el moedelo
      mic = pyaudio.PyAudio()
      stream = mic.open(format = pyaudio.paInt16, channels = 1, rate = 16000, input = True, frames_per_buffer = 8192) #paint16 son 16 bits de muestra
      stream.start_stream()
      
      with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:

            time.sleep(0.1) #wait for serial to open
            
            if arduino.isOpen():
                  print("{} connected!".format(arduino.port))
                  
                  try:
                        while True:
                              data = stream.read(4096)

                              if rec.AcceptWaveform(data):
                                    result = rec.Result()[14:-3]
                                    
                                    if result == "adelante" or result == "atrás" or result == "izquierda" or result == "derecha" or result == "alto":
                                          print('Palabra reconocida')
                                          print(result)
                                          arduino.write(result.encode())
                                          
                                          while arduino.inWaiting()==0: pass

                                          if  arduino.inWaiting()>0:
                                                answer=arduino.readline()
                                                print('Respuesta del arduino')
                                                print(answer.decode())
                                                arduino.flushInput() #remove data after reading

                  except KeyboardInterrupt:
                        print("KeyboardInterrupt has been caught.")#!/usr/bin/env python 
