# RepRapTester - An Arduino Open Source 3D printable tensile tester
An Open Source 3D printed tensile strength tester using Arduino for about £30

Things needed:
Arduino Nano/Uno
HX711 load cell amplifier
300mm section of 51mm square aluminium tubin
Stepstick/DRV8825 stepper driver
10kg bar load cell
some 3D printed parts
Nema 17 stepper motor
Flexible coupling (5mm at one end and 8mm at the other)
A section of M8 studding
A micro-switch
A push-to-make button switch


 This Arduino electronics and code performs the following stages:
  
  1. Drives the stepper motor back to the limit switch
  2. Drives the stepper motor to allow placement of the specimen
  3. Zeros the load cell
  4. Waits for pressing of Start button before starting the test
  5. Drives the stepper motor at a set rate (specified in the sketch) whilst printing stress and strain data to the serial terminal
  6. Stops after travelling 30mm (Assumes the specimen has already broken after this movement)
