<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>

<h1>Smart Medicine Pill Dispenser</h1>

<p>This project is a Smart Medicine Pill Dispenser that uses an ESP32, DS3231 RTC module, and a stepper motor. It is programmed using Arduino and can be controlled through a mobile app. The dispenser pre-schedules medicine times (morning, day, night) via the app, and stores data in Google Firebase. At the scheduled time, the medicine will be dispensed, and an alarm will sound.</p>

<h2>Features</h2>
<ul>
    <li>Uses ESP32 microcontroller</li>
    <li>Includes DS3231 RTC module for accurate timekeeping</li>
    <li>Stepper motor for precise pill dispensing</li>
    <li>Arduino programming for device control</li>
    <li>Mobile app for scheduling and control</li>
    <li>Data storage in Google Firebase</li>
    <li>Automated pill dispensing at scheduled times</li>
    <li>Alarm system to alert the user</li>
</ul>

<h2>How to Use</h2>
<ol>
    <li>Install the mobile app and connect it to the device.</li>
    <li>Schedule medicine times (morning, day, night) through the app.</li>
    <li>The schedule is saved in Google Firebase.</li>
    <li>At the scheduled time, the device will dispense the medicine and the alarm will sound.</li>
</ol>

<h2>Hardware Components</h2>
<ul>
    <li>ESP32</li>
    <li>DS3231 RTC module</li>
    <li>Stepper motor</li>
</ul>

<h2>Software Requirements</h2>
<ul>
    <li>Arduino IDE</li>
    <li>Firebase setup</li>
    <li>Mobile app</li>
</ul>

</body>
</html>
