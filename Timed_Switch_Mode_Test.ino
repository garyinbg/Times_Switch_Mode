/* Hello everyone, I hope that downloading this will be useful and enjoyable. I have
 * tried to comment each line in a way that will give enough information to those of you that
 * are starting out, and not so much to slow down those who are further down the road on
 * this journey.
 * 
 * 
 * I have left this sketch in a form where you can do any of the following; 
 * Make as many states as you want
 * Change the press times and see whats best for you
 * Extend the options by using more outputs
 * Add another button and extend things that way
 * Many things that I have not even considered I am sure BUT I would like to know so please leave a comment
 * 
 * We can do this again in Atmel Studio using 'C' language if there is interest.. again, just leave a comment :)
 * 
 * This file has the following memory requirements;
 * Program size: 3,710 bytes (used 12% of a 32,256 byte maximum)
 * Minimum Memory Usage: 414 bytes (20% of a 2048 byte maximum)
 * 
 * My question to you, should you want to know OR to try is....???? Imagine we want to use a smaller uC ( micro Controller )
 * What can be done to make the memory requirement smaller ?
 * How small can YOU.. yes You  :))) make this program ?
 * 
 * Made by Gary from    www.10dof.technology   
 * We will be putting many more clips up here as they may be relevant
 * 
 * We actually design the hardware and software for flight and autonomous vehicle control and navigation. Everything we will put here
 * will have a use in 'The Real World' as they say.... Enjoy the learning and especially the mistakes you learn most from :)
 */


int SW_PIN = 7;               // INPUT Pulled HIGH with Switch attached ( If you want another pin just change this )
int State_Ch_Pin;             // Used for storing the digital read of SW_PIN
int State_Counter;            // Variable to count which state we are in ( try changing this from an 'int' to an 'uint' for example
long Press_Time;              // The millis at which button was pressed ( variable type is 'long' as all timer values are passed as 'long's )
long Release_Time;            // The millis at which button was released
long Down_Press_Time = 50;    // The number of millis to have passed to change state downwards BUT LESS THAN 'Up_Press_Time' ( Play with the values )
long Up_Press_Time = 1000;    // The number of millis to have passed to change state upwards ANYTHING MORE THAN 1000         ( Play with the values )
long Pushed;                  // The amount of millis() between the button being pushed down and being released
int Pressed_Flag = 0;         // A flag / Marker to include in logic decisions

//====================== FUNCTIONS============================
void Count_Millis(long Press_Time, long Release_Time);                     // Pre-Declare Millis Counter Function ( Not required by the Arduino IDE..... BUT GREAT PRACTICE FOR MOVING ON TO 'C' )


//========================SETUP==========================
void setup() {                                 // Where se set out things we want to be done one time only
  Serial.begin(9600);                          // Start Serial Comms ( mainly for fault finding by understanding whether a piece of code has 'run' or not

  pinMode(LED_BUILTIN, OUTPUT);                // initialize digital pin LED_BUILTIN as an OUTPUT.
    pinMode(SW_PIN, INPUT_PULLUP);               // initialize digital pin SW_PIN as an INPUT WITH PULLUP ACTIVATED OR YOU CAN USE .
//  pinMode(SW_PIN, INPUT);                    // Sets SW_PIN as INPUT  BUT THEN WE HAVE TO DO 
//  digitalWrite(SW_PIN, HIGH);                // This digitalWrite................JUST MORE WORK BUT THE SAME OUTCOME :)
}


void loop() {                                  // the loop ROUND AND ROUND over and over again forever.. :D ...................
                                               // The only thing happening in this loop is the checking of the SW_PIN. That happens SOOOO fast it will catch even the shortest press
State_Ch_Pin = digitalRead(SW_PIN);            // Read the pin we chose for the button and store its value in the variable *State_Ch_Pin*

if (! State_Ch_Pin && Pressed_Flag == 0)       // IF there is no value at *State_Ch_Pin*, ( SO IF ITS LOW ) ANDDDDDD Pressed_Flag is Equal to 0 THEN RUN THE FOLLOWING CODE
  {                                            // Using the '!' means that something 'IS NOT'
     Press_Time = millis();                    // Read and store the moment we pressed the button in the variable *Press_Time*
     Serial.println("Pressed Time");           // Print it because its nice to use
     Serial.println(millis());                 // And we understand if that part of th code has 'run'
     Pressed_Flag = 1;                         // Set the *Pressed_Flag* to a 1 to show this operation has been completed
  }// END if

//===== NOW.....ANYTIME AFTER THAT 'if' ENDS ========

     if ( State_Ch_Pin && Pressed_Flag == 1)       // If the *State_Ch_Pin* has a value ( so its HIGH, a '1' ) ANDDDDDDDD *Pressed_Flag* is Equal to 1 ( so the press operation is complete
    {                                              // RUN THE FOLLOWING CODE
    Release_Time = millis();                       // Record the millis() and store it in the variable ( a long ) *Released_Time*
    Serial.println("Release Time");                // Print so we can use it and see how things are going
    Serial.println(millis());                      // And we understand if that part of th code has 'run'
    Count_Millis(Press_Time, Release_Time);        // Call the function to calculate the times FROM INSIDE THE IF....OTHERWISE IT WILL BE CALLED AGAIN AND AGAIN AND WELL you see ( Try it :)  )
    }// END if
}// END loop

//=======================FUNCTION =======================================
// This function comes in two parts.. an 'if' and an 'if else'
// I did this because I wanted to use the timer to give me the option to make sure
// I was not dealing with 'switch bounce' BUT wanted a short push to go - up a mode -

// AT the same time I wanted a push of about a second to come back - down a mode -
// NOW you can play with those numbers and get something you like and that works for you, 
// especially in a none time critical application.

// I want to fit this to a radio control transmitter I have adapter for people with special needs 
// and those who just want as much centralized on one of the transmitter sticks
       
void Count_Millis(long Press_Time, long Release_Time)
{
  if (Release_Time - Press_Time > 50 && Release_Time - Press_Time < 1000)
  {
     State_Counter += 1;                                                   // Increment the mode state
     digitalWrite(LED_BUILTIN, HIGH);                                      // use the LED to show this happened
     Pressed_Flag = 0;                                                     // Reset the flag ready for the next time
     Serial.print("Mode has gone 'UP' by 1 state to  ");                   // Print the operation result
     Serial.println(State_Counter);                                        // And show the state
  }// END IF... START ELSE IF

  
 else if (Release_Time - Press_Time > 50 && Release_Time - Press_Time > 1000) 
{
     State_Counter -= 1;                                                   // Decrement the mode state
     digitalWrite(LED_BUILTIN, LOW);                                       // use the LED to show this happened
     Pressed_Flag = 0 ;                                                    // Reset the flag ready for the next time
     Serial.print("Mode has gone 'DOWN' by 1 state to  ");                 // Print the operation result 
     Serial.println(State_Counter);                                        // And show the state 
     }// END else if
}// END Function

// You might even want to add this as another option===== SEE BELOW =========

// I will leave you to consider where this should go and what the effects will be....
// Think of this like... Homework :D

/*  else if (Release_Time - Press_Time > 1400 && Release_Time - Press_Time > 2500)
  {
 	 State_Counter -= 3;                                                   // Decrement the mode state to the first level mode state immediately without going through the other states, one by one
 	 digitalWrite(LED_BUILTIN, LOW);                                       // use the LED to show this happened
 	 Pressed_Flag = 0 ;                                                    // Reset the flag ready for the next time
 	 Serial.print("Mode has gone 'DOWN' by 3 states to  ");                 // Print the operation result
 	 Serial.println(State_Counter);                                        // And show the state
  }  // END else if
  }  */