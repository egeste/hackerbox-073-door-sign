# A Sign For Your Door

An automated door sign for your office based on the Hackerbox 073 "LanLord"

<img src="https://user-images.githubusercontent.com/536059/188494944-9dcdb193-1027-4c12-b033-09cf0f1d389a.jpg" width="300" />
<img src="https://user-images.githubusercontent.com/536059/188494922-943b8e1d-342f-4087-ad87-12ea6af01f91.jpg" width="300" />
<img src="https://user-images.githubusercontent.com/536059/188494955-5161771d-e9f7-4360-a3e7-87e1284ddeb6.jpg" width="300" />

## Hardware

### Hackerbox 073 "LanLord"

 * [Hackerbox 073 "LanLord"](https://hackerboxes.com/products/hackerbox-0073-lan-lord)
 * [Setup & Assembly](https://www.instructables.com/HackerBox-0073-LAN-Lord/#step5)

### Other stuff

 * 1x [USB-A to USB Micro B](https://www.amazon.com/s?k=usb+micro+b+cable&i=electronics&s=relevancerank)
 * 1x [5v 1a USB AC->DC adapter](https://www.amazon.com/s?k=5v+1a+usb+adapter&s=review-rank)

## Software

### Dependencies

 * [Arduino IDE](https://www.arduino.cc/en/software)
 * [Adafruit_ILI9341](https://github.com/adafruit/Adafruit_ILI9341)
 * [WiFiWebServer_RTL8720](https://github.com/khoih-prog/WiFiWebServer_RTL8720)

### Configuration

 1. Duplicate/copy `network.example.h` to a new file named `network.h`
 1. Modify `network.h`, adding your `WIFI_NET_SSID` and `WIFI_NET_PASS`

### Use

At boot time, the board will connect to your WiFi network and display its IP address.

#### Message Priority

The message status is represented as a `byte` where each bit represents a message's boolean state.
If more than one message bit is set to `true`, the most significant bit will take priority.

The bit mapping for messages can be found in the source code and looks as follows:

#### URLs

##### "Meeting in progress"

 * http://<device_ip>/meeting?on
 * http://<device_ip>/meeting?off

##### "Do Not Disturb"

 * http://<device_ip>/donotdisturb?on
 * http://<device_ip>/donotdisturb?off

##### "Please Enter"

 * http://<device_ip>/enter?on
 * http://<device_ip>/enter?off

```c
// Bit mapping
#define ENTER_BIT_IDX        0
#define DONOTDISTURB_BIT_IDX 1
#define MEETING_BIT_IDX      2
```

### Wall Mount

Included in this repository is a [3d printable STL file for mounting your board.](https://github.com/egeste/hackerbox-073-door-sign/blob/main/door-sign.stl)

<img src="https://user-images.githubusercontent.com/536059/188531301-c6b68b45-b99f-4551-b359-b94f7337cf4a.png" width="300" />
<img src="https://user-images.githubusercontent.com/536059/188531321-1c48f9c5-079a-40a0-b079-7c182514fd90.jpg" width="300" />

### Integrations

#### Hubitat

Hubitat provides a handly [HTTP GET switch](https://github.com/hubitat/HubitatPublic/blob/master/examples/drivers/httpGetSwitch.groovy) virtual device.

 1. Follow the directions on the [Hubitat documentation](https://docs.hubitat.com/index.php?title=How_to_Install_Custom_Drivers) to install this driver.
 1. Connect to your Hubitat dashboard
 1. Click the "Devices" button ![Screenshot from 2022-09-05 10-01-38](https://user-images.githubusercontent.com/536059/188493963-6eb11a4b-a26d-47e1-93c1-8e1ae278aeb6.png)
 1. Click the "Add Device" button ![Screenshot from 2022-09-05 10-01-54](https://user-images.githubusercontent.com/536059/188494135-ec6125fd-073b-4984-916f-18e9c9de9b4e.png)
 1. Click the "Virtual" button ![Screenshot from 2022-09-05 09-58-35](https://user-images.githubusercontent.com/536059/188493999-44a8acac-0008-4146-8457-572b69cfb63a.png)
 1. Enter a name for this switch in the `Name` field ![Screenshot from 2022-09-05 09-59-19](https://user-images.githubusercontent.com/536059/188494014-4b30142e-45f2-4392-b9ed-9f83df5e8afb.png)
 1. Select `Http GET Switch` from the `Type` field ![Screenshot from 2022-09-05 09-59-26](https://user-images.githubusercontent.com/536059/188494023-03bb50a4-795c-4c55-ab26-2e4245280b13.png)
 1. Click `Save Device`
 1. Use the URLs above to control the message using this switch ![Screenshot from 2022-09-05 10-00-24](https://user-images.githubusercontent.com/536059/188494055-c3aee09a-8517-485a-aba5-0a8e481966e3.png)
