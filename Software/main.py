import machine, utime, time
from PicoDHT22 import PicoDHT22
from bmp085 import BMP180
from imu import MPU6050
from mq2 import MQ2
from micropyGPS import MicropyGPS

#Led para checar el funcionamiento
led = machine.Pin(25, machine.Pin.OUT)

#Inicialización de perfiéricos
i2c = machine.I2C(0, sda=machine.Pin(16), scl=machine.Pin(17))
uart = machine.UART(1, 9600, tx=machine.Pin(20), rx=machine.Pin(21))


#Se crean los objetos para los sensores
#DHT11
dht11 = PicoDHT22(machine.Pin(7,machine.Pin.IN,machine.Pin.PULL_UP),dht11=True)

#BMP180
bmp180 = BMP180(i2c)
bmp180.oversample = 2
bmp180.sealevel = 2240

#MPU6050
imu = MPU6050(i2c)

#MQ7
mq7 = MQ2(pinData = 26, baseVoltage = 3.3)
mq7.calibrate()

#GPS
gpsModule = machine.UART(0, baudrate=9600, tx=machine.Pin(12), rx=machine.Pin(13))

#Algunas variables necesarias
buff = bytearray(255)

TIMEOUT = False
FIX_STATUS = False

latitude = "" 
longitude = ""
satellites = ""
GPStime = ""

#Funciones del GPS
def getGPS(gpsModule):
    global FIX_STATUS, TIMEOUT, latitude, longitude, satellites, GPStime
    
    timeout = time.time() + 8 
    while True:
        gpsModule.readline()
        buff = str(gpsModule.readline())
        parts = buff.split(',')
    
        if (parts[0] == "b'$GPGGA" and len(parts) == 15):
            if(parts[1] and parts[2] and parts[3] and parts[4] and parts[5] and parts[6] and parts[7]):
                #print(buff)
                
                latitude = convertToDegree(parts[2])
                if (parts[3] == 'S'):
                    latitude = "-"+latitude
                longitude = convertToDegree(parts[4])
                if (parts[5] == 'W'):
                    longitude = "-"+longitude
                satellites = parts[7]
                GPStime = parts[1][0:2] + ":" + parts[1][2:4] + ":" + parts[1][4:6]
                FIX_STATUS = True
                break
                
        if (time.time() > timeout):
            TIMEOUT = True
            break
        utime.sleep_ms(500)
        
def convertToDegree(RawDegrees):

    RawAsFloat = float(RawDegrees)
    firstdigits = int(RawAsFloat/100) 
    nexttwodigits = RawAsFloat - float(firstdigits*100) 
    
    Converted = float(firstdigits + nexttwodigits/60.0)
    Converted = '{0:.6f}'.format(Converted) 
    return str(Converted)

while True:
    led.value(True)
    
    #Lectura del GPS    
    getGPS(gpsModule)

    if(FIX_STATUS == True):
        #print("Printing GPS data...")
        #print(" ")
        #print("Latitude: "+latitude+"\tLongitud: "+longitude+"\tSatellites: "+satellites+"\tTime: "+GPStime)
        lectura_gps = latitude+longitude+"$"
        
        FIX_STATUS = False
        
    if(TIMEOUT == True):
        #print("No GPS data is found.")
        lectura_gps = "No GPS"
        TIMEOUT = False
    
    
    #Lectura MPU
    ax=round(imu.accel.x,2)
    ay=round(imu.accel.y,2)
    az=round(imu.accel.z,2)
    gx=round(imu.gyro.x)
    gy=round(imu.gyro.y)
    gz=round(imu.gyro.z)
    aceleracion = str(round(ax,2)) + "," + str(round(ay,2)) + ","  + str(round(az,2)) + "A"
    giroscopio = str(gx) + ","  + str(gy) + ","  + str(gz) + "G"
    
    #Lectura BMP180
    p = bmp180.pressure
    altitude = bmp180.altitude
    
    #Lectura DHT11
    T,H = dht11.read()
    
    #Lectura MQ7
    gases = str(mq7.readSmoke()) + "," + str(mq7.readLPG()) + ","  + str(mq7.readMethane()) + ","  + str(mq7.readHydrogen()) + "Q"
    
    #Impresion de variables
    lectura = str(T) + "T" + str(H) + "H" + str(p) + "P" + str(altitude) + "A" + aceleracion + giroscopio + gases + lectura_gps + "\0\n"  
    uart.write(lectura)
    #print(lectura)
    led.value(False)
    utime.sleep(5)



