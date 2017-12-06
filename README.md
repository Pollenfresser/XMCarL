# XMCarL
<p>Project of the Embeded Systems Class at FHTW. Developed by Lucas, Dominik and Chrisy.</p>

# Idea
A remote controlled car is controlled by a xmc which is connected to an acceleration sensor. The car is fitted with a GoPro5 - which sends a live stream to the gui application on the laptop. The car and the GoPro are not talking to each other.

In order to the task-description the xmc communicates with the gui-application (Lucas part)
(Maybe just a "connected" message)

<b>acceleration sensor</b>  -wire-  <b>xmc</b> -wire-  <b>transmitter</b>  -wireless-  <b>car</b>  -mechanical-  <b>gopro</b>  -wireless-  <b>gui</b> 

### Remote controll
<p>Microcontroller XMC and Acceleration sensor is used as a remote control</p>

### Car


### GUI - Application
GoPro & GUI
<p>Using Gstreamer and WebKitGtk</p>
XMC & GUI
<p>Using cairo / gnuplot to visualise data from the sensor</p>


### Steps we did / Working

GoPro

https://github.com/KonradIT/GoProStream

-> python3

dnf install ffmpeg

### Next Steps

gopro video with gstreamer
