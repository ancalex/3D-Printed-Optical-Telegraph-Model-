#include <Servo.h> //import the servo library
#include <SoftwareSerial.h>// import the serial library
Servo cross_bar_servo; //servo objects
Servo arm1_servo;
Servo arm2_servo;
int min_cb = 520; int max_cb = 2630;      //values determined for each servo
int min_arm1 = 490; int max_arm1 = 2510;
int min_arm2 = 440; int max_arm2 = 2470;
SoftwareSerial BlSerial(10, 11); // RX, TX
int index = 0;            // the position of a character in the message string
int start_angle;		// the angle from which the servo movement starts
int stop_angle;			// the angle at which the servo must reach
bool end_message = 0;    // end of message? 0-NO, 1-YES
String message = "";

void show_message() {
	index = 0;
	int pos;
	int mess_len = message.length() ;
	while (index < mess_len) {
		BlSerial.print(message[index]); BlSerial.println(" is transmitting...");
		//Serial.println(message[index]);
		//crossbar position
		if (message[index] == 'C' || message[index] == 'G' || message[index] == 'L' || message[index] == 'P' || message[index] == 'T' || message[index] == 'X' || message[index] == '1' || message[index] == '5' || message[index] == '9') {
			stop_angle = 0;
		}
		else if (message[index] == 'B' || message[index] == 'F' || message[index] == 'K' || message[index] == 'O' || message[index] == 'S' || message[index] == 'W' || message[index] == '&' || message[index] == ' ' || message[index] == '4' || message[index] == '8') {
			stop_angle = 45;
		}
		else if (message[index] == 'A' || message[index] == 'E' || message[index] == 'I' || message[index] == 'N' || message[index] == 'R' || message[index] == 'V' || message[index] == 'Z' || message[index] == '3' || message[index] == '7') {
			stop_angle = 90;
		}
		else {
			stop_angle = 135;
		}
		//Serial.print(index); Serial.print("-----"); Serial.println(stop_angle);
		cross_bar_servo.attach(3, min_cb, max_cb); // re-attach the crossbar servo object
		start_angle = cross_bar_servo.read(); //read the actual position and move to desired position
		if (start_angle > stop_angle) {
			for (pos = start_angle; pos >= stop_angle; pos -= 1) {
				cross_bar_servo.write(pos);
				delay(15);
			}
		}
		else {
			for (pos = start_angle; pos <= stop_angle; pos += 1) {
				cross_bar_servo.write(pos);
				delay(15);
			}
		}
		cross_bar_servo.detach(); // deactivate the servo object
		// upper (or left) arm position
		if (message[index] == 'G' || message[index] == 'F' || message[index] == 'E' || message[index] == 'D' || message[index] == 'L' || message[index] == 'K' || message[index] == 'I' || message[index] == 'J' ||message[index] == 'M' || message[index] == '5' || message[index] == '4' || message[index] == '3' || message[index] == '2') {
			stop_angle = 0;
		}
		else if (message[index] == 'X' || message[index] == 'W' || message[index] == 'V' || message[index] == 'U' || message[index] == '1' || message[index] == '&' || message[index] == ' ' || message[index] == 'Z' || message[index] == '6' || message[index] == '9' || message[index] == '8' || message[index] == '7' || message[index] == '0') {
			stop_angle = 90;
		}
		else {
			stop_angle = 180;
		}
		//Serial.print(index); Serial.print("......."); Serial.println(stop_angle);
		arm1_servo.attach(5, min_arm1, max_arm1); //re-attach the arm servo object
		start_angle = arm1_servo.read(); //read the actual position and move to desired position
		if (start_angle > stop_angle) {
			for (pos = start_angle; pos >= stop_angle; pos -= 1) {
				arm1_servo.write(pos);
				delay(15);
			}
		}
		else {
			for (pos = start_angle; pos <= stop_angle; pos += 1) {
				arm1_servo.write(pos);
				delay(15);
			}
		}
		arm1_servo.detach(); // deactivate the arm servo object
		// lower (or right) arm position
		if (message[index] == 'C' || message[index] == 'B' || message[index] == 'A' || message[index] == 'H' || message[index] == 'L' || message[index] == 'K' || message[index] == 'I' || message[index] == 'J' ||message[index] == 'M' || message[index] == '1' || message[index] == '&' || message[index] == ' ' || message[index] == 'Z' || message[index] == '6') {
			stop_angle = 0;
		}
		else if (message[index] == 'T' || message[index] == 'S' || message[index] == 'R' || message[index] == 'Y' || message[index] == '5' || message[index] == '4' || message[index] == '3' || message[index] == '2' || message[index] == '9' || message[index] == '8' || message[index] == '7' || message[index] == '0') {
			stop_angle = 90;
		}
		else {
			stop_angle = 180;
		}
		//Serial.print(index); Serial.print("********"); Serial.println(stop_angle);
		arm2_servo.attach(6, min_arm2, max_arm2); //re-attach the arm servo object
		start_angle = arm2_servo.read(); //read the actual position and move to desired position
		if (start_angle > stop_angle) {
			for (pos = start_angle; pos >= stop_angle; pos -= 1) {
				arm2_servo.write(pos);
				delay(15);
			}
		}
		else {
			for (pos = start_angle; pos <= stop_angle; pos += 1) {
				arm2_servo.write(pos);
				delay(15);
			}
		}
		arm2_servo.detach(); // deactivate the arm servo object
		BlSerial.print(message[index]); BlSerial.println(" was transmitted...");
		index++;
		delay(3000);
	}
}

void setup()
{
	cross_bar_servo.attach(3, min_cb, max_cb); // attach the servo objects
	arm1_servo.attach(5, min_arm1, max_arm1);  // the crossbar will move to 90 degree
	arm2_servo.attach(6, min_arm2, max_arm2);  // the arms will move to 90 degree also
	delay(1000);
	cross_bar_servo.detach();  // deactivate all servo objects
	arm1_servo.detach();
	arm2_servo.detach();
	//Serial.begin(9600); //for debugging
	BlSerial.begin(9600);
	delay(1000);
}

void loop()
{
	if (BlSerial.available() > 0){
		message = BlSerial.readString();  // read the characters from Bluetooth serial buffer
		message.toUpperCase();			  // change case
		message.trim();			// remove leading and trailing white characters (space, tab, vertical tab, form feed, carriage return, newline)
	end_message = 1;
	show_message(); // 'display' characters
	}
	if (end_message != 0) {
		message = "7";
		show_message();
		BlSerial.println("end of message");
		end_message = 0;
		delay(3000);
	}
}
