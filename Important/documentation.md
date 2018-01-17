fedora nutzt Wailand - muss es auf x11 umstellen
click on the arrow in the top right corner - click on your username -> logout
at the login screen, there is a settings symbol -> change to xorg and login; x11 will work then

What I did for bluetooth:

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




Information about "interruts"
Multi-threading approach

Some time ago I had the same task, and the best way I found to solve it is to use pthreads. Basically, I did next:

    producer thread (main thread): wait for new data in serial port; once new data is available -- write it into circular buffer (produce data) and wake up the consumer thread via pthread_cond_signal()
    consumer thread: wait for producer thread to wake me (using pthread_cond_wait() function); once woke up -- read new data from circular buffer (consume data) and process it properly
    in my case, serial port was open in non-blocking mode, because I wanted to wait for new data with timeout, which provided in poll() function. If you don't need this -- you can open serial port in blocking mode and just use blocking read() call (as proposed by @sawdust in comment)

This way you don't waste CPU time waiting for new data to arrive, and in the same time you don't need to mess with signals (using signals has a lot of complications, so I decided to avoid it).
