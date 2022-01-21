# arduino
 
 **https://www.tinkercad.com/things/46D67SujmRQ**
 ![Picture](https://user-images.githubusercontent.com/94222074/150573977-46b2483f-d107-4554-9c81-623e4029255f.jpg)
 
## 🔴Instruction for arduino Project:<br>
The newly appointed Minister of Agriculture has decided to improve the lives of avocado consumers in the country with the help of a policy of "sending avocados to the writer according to the level of ripeness."
It is known that avocados have 3 ripe grades (1- lowest level, 3- highest level), you must design a packing house that will work according to the new policy.

The packing house works as follows:

🔹The start of the day and the end of the day will be done by the push button (On / Off button on the remote control), all the avocados will rise at one level of maturity when the day ends (the system will start when the factory is closed and empty of crates)

🔹During the work day each time the PLAY button is pressed on the IR remote, new crates arrive at the packing house. The number of boxes ranges from 1-9 and the number of boxes must be selected by pressing the appropriate button on the remote control immediately after pressing PLAY. If the PLAY button is pressed, the program will wait until the number of crates is received.

🔹 Each crate that arrives is at a certain level of ripeness and uniform for all the fruits in it. The level of ripeness of the crate is randomly drawn.

🔹 When inserting (after selecting the number of boxes), the green light will flash as the number of boxes inserted.

🔹 You need to manage the inventory of crates so that you know how many crates there are at each level of maturity and what day it was.

🔹 At the end of each day if a fruit crate has reached the maximum level of ripeness (grade 3) it will be sent to the writer and the red light will flash as the number of crates coming out.

🔹 In order to keep the fruit optimal, it was decided to install a temperature control in the warehouse. When the temperature is higher than 23 degrees all the avocados will rise to the level of ripeness. Level 3 avocados will rot and be thrown in the trash. The control works during the working day only. The increase in the level of ripeness will take place once each time the temperature exceeds the limit of 23 degrees. For example, if the temperature was 22 and rose to 23.5 -> raise the maturity levels, then rise from 23.5 to 25 we will not raise the maturity levels again, but if the temperature drops below 23 again then cross the 23 again Level of ripeness.

🔹 In addition, it was decided to install an anti-burglar alarm in the warehouse which is activated when the working day is over. If the ultrasonic sensor detects a person (thief) approaching at a distance of less than 100 cm, the alarm will start operating for 3 seconds. In each theft, the thief will be able to steal 3 random boxes from the warehouse. Can reach at most one thief per night.You must address deviations, note that you are working with a code adapted to the simulator and not with the code that appeared in the practice (you can use the link https://www.tinkercad.com/things/jqCWhVb9yIa-copy-of-copy- of-ultrasonic-sensor / editel? tenant = circuits).

🔹 When a box is thrown in the trash it means that no more information is kept on it.

When exercising you need to think about extreme cases and address them in code. You must use detailed documentation within the code.

