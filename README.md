<h1>Bluetooth Controlled LEDS Project</h1>
	


Author
------------------------------------------
	
	

<!-- fill out the following table with your information -->
	

<!-- Note: wrapping table in div.noheader will hide the table's header -->
	

<!-- Note: wrapping table in div.firstcol will style the first column different from other columns -->
	

Authored by: Josh Meleski
Contributors: buzzandy 



Specifications
-----------------------------------------

<ul>
<li>The code uses a bluetooth connection to send data over Serial. I used an app from the Google app store to send it over. </li>
<li>The data received then goes into a case statement; and then, based on the data received, will call a function.</li>

<li>The functions are:
<ul>
<li>Twinkle: Lights up random LED's within the strip and changes for a twinkle effect</li>
<li>RunningLights: Runs a sine wave down the strip where brightness is the height of the function.</li>
<li>Sound: Changes one strip to white and the other to react to sound by lighting up each octave. (NOTE: I did not write this code. I got it from Arduino project user buzzandy and modified it to work better for Neopixel RGBW lights.
<li>Rainbow: Creates a rainbow over the lenght of the strip and moves it over time
</ul>
<li>Data should be able to given at anytime and change functions. Each color that is called can also call the Runninglights or twinkle functions and have those do those functions in chosen color.
</ul>
	
	
Future Improvemets
----------------------------------------------
Getting more light features as well as more color calibration in for non primary colors in sound reactive mode.
