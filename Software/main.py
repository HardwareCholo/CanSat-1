import machine, utime
from PicoDHT22 import PicoDHT22
from bmp085 import BMP180
from imu import MPU6050
from mq2 import MQ2

#Led para checar el funcionamiento
led = machine.Pin(25, machine.Pin.OUT)

#Inicialización de perfiéricos
i2c = machine.I2C(0, sda=machine.Pin(16), scl=machine.Pin(17))

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

while True:
    led.value(True)
    #Lectura MPU
    ax=round(imu.accel.x,2)
    ay=round(imu.accel.y,2)
    az=round(imu.accel.z,2)
    gx=round(imu.gyro.x)
    gy=round(imu.gyro.y)
    gz=round(imu.gyro.z)
    aceleracion = "[" + str(round(ax,2)) + "x," + str(round(ay,2)) + "y," + str(round(az,2)) + "z]m\s^2\t"
    giroscopio = "[" + str(gx) + "x," + str(gy) + "y," + str(gz) + "z]\t"
    
    #Lectura BMP180
    p = bmp180.pressure
    altitude = bmp180.altitude
    
    #Lectura DHT11
    T,H = dht11.read()
    
    #Lectura MQ7
    gases = "[" + str(mq7.readSmoke()) + ", " + str(mq7.readLPG()) + ", " + str(mq7.readMethane()) + ", " + str(mq7.readHydrogen()) + "]ppm\t"
    
    #Impresion de variables
    lectura = str(T) + "°C\t" + str(H) + "%\t" + str(p) + "hPa\t" + str(altitude) + "m\t" + aceleracion + giroscopio + gases + "\r\n"
    print(lectura)
    led.value(False)
    utime.sleep(0.5)