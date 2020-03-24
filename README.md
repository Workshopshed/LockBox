# Arduino Project - Defuse the Device Game Plan

## Setting the Device
When inputting code A1111# this should go to a menu that asks you via the display screen ‘SET TIME’ it will allow you to key in via the keypad how many minutes you want the game to last for that should display on the countdown display, (Maximum 99 minutes).
By pressing # this will confirm the number of minutes.

Once the number of minutes has been inputted this should go to a menu that asks you via the display screen ‘START GAME’
By pressing # this will confirm and start the game in 5 seconds that when reaches 0 will beep via the buzzer once in high volume and set the light sensor detector.

## Opening Device
When the box is opened the light sensor will activate the display screen and LED 10 will begin flashing as well as and beep via the buzzer whenever LED 10 is lit up.

The display screen should display ‘DEVICE ARMED’ in flashing text for 3 seconds, It should also say this in speech via the internal speaker once in high volume.

After 3 seconds it should say in speech via the internal speaker once in high volume ‘DEVICE WILL DETONATE IN T MINUS (However many minutes the pre-set time the countdown timer was set for). The countdown timer will then begin starting from the pre-set time.
Once the Countdown timer as started LED’s 7,8 and 9 should turn on, the internal speaker should also activate a sound that signifies something been activated or powered up in high volume.

Code 1

When inputting code 9374# into the keypad, LED 1 will light up and remain turned on.

Once the correct code has been entered into the Keypad the display screen should display ‘CODE ACCEPTED’ in text for 3 seconds. It should also say this in speech via the internal speaker once in high volume.

Code 2

When inputting code 1564# into the keypad, LED 2 will light up and remain turned on.

Once the correct code has been entered into the Keypad the display screen should display ‘CODE ACCEPTED’ in text for 3 seconds. It should also say this in speech via the internal speaker once in high volume.

Code 3

When inputting code 7132# into the keypad, LED 3 will light up and remain turned on.

Once the correct code has been entered into the Keypad the display screen should display ‘CODE ACCEPTED’ in text for 3 seconds. It should also say this in speech via the internal speaker once in high volume.

Code 4

When inputting code 3684# into the keypad, LED 4 will light up and remain turned on.

Once the correct code has been entered into the Keypad the display screen should display ‘CODE ACCEPTED’ in text for 3 seconds. It should also say this in speech via the internal speaker once in high volume.

## Conditions
The Countdown timer will display the countdown in Minutes/Seconds/Milliseconds/Microseconds.

If an invalid code is entered into the Keypad the countdown speeds up 30 seconds and LED 10 flashes quicker. The display screen should display ‘INVALID CODE ENTERD’ in flashing text for 3 seconds. It should also say this in speech via the internal speaker once in high volume.

Every key pressed on the Keypad should be acknowledged with a beep from the buzzer and display as text on the Display Screen.

Every 5 minutes that pass it should say T MINUS (However many minutes are remaining) in speech ‘via the internal speaker once in high volume.

Once the countdown timer gets to 4 minutes it should say T MINUS (However many minutes are remaining) for each minute after until 0 minutes in speech ‘via the internal speaker once in high volume and beep via the buzzer.

Once the countdown timer gets to the last 10 Seconds it should begin to count down from 10 seconds to 0 Seconds in speech ‘via the internal speaker once in high volume and beep in a higher tone each second via the buzzer.

If any other wire color is disconnected other than the ones listed in (Code 6) the countdown timer is to speed up by 30 seconds and LED 10 flashes quicker.

The Display screen should display ‘LOW POWER’ and say this in speech via the internal speaker once in high volume if the remaining power in the battery is below 10%

By pressing B9820# the countdown will pause, when entering the same code again the countdown will continue.

Once LED’s from 1-6 are all activated the Countdown Timer is to stop but still display the current time it is on. The display screen should display ‘DEVICE DEACTIVATED’ in text for 3 seconds. It should also say this in speech via the internal speaker once in high volume. All LED’s and buzzers will turn off.

Once the countdown timer reaches 0 the internal speaker should activate a sound of a bomb detonating or loud explosion once in high volume. The display screen should display ‘BOOM in flashing text.
