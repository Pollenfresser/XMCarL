# GOPRO stream

The URI interface

In all examples so far, we have only supported local files through the “filesrc” element. GStreamer, obviously, supports many more location sources. However, we don't want applications to need to know any particular element implementation details, such as element names for particular network source types and so on. Therefore, there is a URI interface, which can be used to get the source element that supports a particular URI type. There is no strict rule for URI naming, but in general we follow naming conventions that others use, too. For example, assuming you have the correct plugins installed, GStreamer supports “file:///<path>/<file>”, “http://<host>/<path>/<file>”, “mms://<host>/<path>/<file>”, and so on.

In order to get the source or sink element supporting a particular URI, use gst_element_make_from_uri (), with the URI type being either GST_URI_SRC for a source element, or GST_URI_SINK for a sink element.

# how to connect gopro to laptop
* first, we have to install the gopro app on mobile phone to activate wlan
* mobile phone needs turned on bluetooth
* connect to laptop with wlan (you cannot be in the internet and connected to gopro)
* compile with python3 -> https://github.com/KonradIT/GoProStream here is a python file

# gstreamer - lernen
* i like this tutorial: http://z25.org/static/_rd_/videostreaming_intro_plab/
* gst-launch-1.0 videotestsrc ! autovideosink // this command shows an example picture :)
* autovideosink -> to display
* gst-launch-1.0 udpsrc port=5000 ! \ application/x-rtp,\ encoding-name=H264,payload=96 ! \ rtph264depay ! h264parse ! avdec_h264 ! \ autovideosink


# gstreamer x11
fedora nutzt Wailand - muss es auf x11 umstellen
click on the arrow in the top right corner - click on your username -> logout
at the login screen, there is a settings symbol -> change to xorg and login; x11 will work then

# What I did for bluetooth:

Tutorial: https://people.csail.mit.edu/albert/bluez-intro/c33.html
I used bluez with c

* Step 1: install packages
dnf search bluez // for finding out how the package is called
sudo dnf install bluez-libs-devel.x86_64
bluez-libs-devel.x86_64 : Development libraries for Bluetooth applications
it was this version: bluez-libs-devel-5.46-6.fc26.x86_64


https://www.pcsuggest.com/bluetooth-linux-part-2/
here you find commands to find / connect / bind (with rfcomm) your bluetooth device

# Bluetooth commands (terminal)

* hcitool scan
* sdptool browse
channel is important
* hciconfig
UP RUNNING PSCAN PSCAN
* sudo rfcomm release 0 
for removing rfcomm0; listed here: ls /dev/
* sudo rfcomm connect 1 00:1B:35:88:0C:81 1
Connected /dev/rfcomm1 to 00:1B:35:88:0C:81 on channel 1
wuhu, it's working!!!

# MEMS Sensor Pin belegung
wir sind auf der x2 seite - achtung, außenbeschr = außenports, innenbeschr = innenports
* GND -> GND
* Vin -> VDD3.3
* SCL -> P0_11
* SDA -> P0_5
* INT -> P0_3
USB
* grünes kabel: tx also geht an rx - p1_4
* schwarzes kabel: gnd
* weißes kabel: rx also geht an tx - p1_5

data from mems is from -17.000 to 17000

Information about "interrupts"
Multi-threading approach

Some time ago I had the same task, and the best way I found to solve it is to use pthreads. Basically, I did next:

    producer thread (main thread): wait for new data in serial port; once new data is available -- write it into circular buffer (produce data) and wake up the consumer thread via pthread_cond_signal()
    consumer thread: wait for producer thread to wake me (using pthread_cond_wait() function); once woke up -- read new data from circular buffer (consume data) and process it properly
    in my case, serial port was open in non-blocking mode, because I wanted to wait for new data with timeout, which provided in poll() function. If you don't need this -- you can open serial port in blocking mode and just use blocking read() call (as proposed by @sawdust in comment)

This way you don't waste CPU time waiting for new data to arrive, and in the same time you don't need to mess with signals (using signals has a lot of complications, so I decided to avoid it).
