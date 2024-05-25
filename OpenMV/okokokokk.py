
import sensor, image, time
from machine import LED
from pyb import UART
from pyb import Pin


P_IN = Pin('P6', Pin.IN, Pin.PULL_UP)

ROI=[10,20,280,150]

uart = UART(3, 115200)

coin_threshold = (0, 52, -29, 127, -49, 127)
led = LED("LED_BLUE")

led.off()

sensor.reset()
sensor.set_pixformat(sensor.RGB565) # 灰度更快
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

sensor.set_hmirror(True)
sensor.set_vflip(True)

clock = time.clock()




while(True):
    clock.tick()


    img = sensor.snapshot().lens_corr(1.8)

    img.binary([coin_threshold],invert = 0)

    blobi = img.find_blobs([(0,0,0)],roi=ROI,area_threshold=200)

    img.draw_rectangle(10,20,280,150,(0,0,0))


    if blobi:
        for blob in blobi:
            if blob.area()>500 and blob.area()<2000:
                xt = (blob.cy()-32)
                yt = (blob.cx()-160)

                msg1 = ("x%dy%dX\n" %(xt,yt))
                print(msg1)

                uart.write(msg1)

