//You are allowed to define your own function to fulfill the requirement of tasks
//Dont change the name of following functions
*Author:Sanchay Harjai, Sudeep Gopavaram, Kartik Dua, Rishabh Pathak
*Filename :CB_Task_1_Project.sln
*Functions:nodedetector(unsigned char centreline, unsigned char leftline,unsigned char rightline),
*nodedetector1(unsigned char centreline, unsigned char leftline, unsigned char rightline),
*nodedetectorwhite(unsigned char centreline, unsigned char leftline, unsigned char rightline),
*forward_wls(unsigned char node),
*forward_wlssharp(unsigned char node),
*forward_wls_tillwhite(unsigned char node),
*forward_wlszigzag(unsigned char node),
*left_turn_wls(void),
*right_turn_wls(void),
*e_shape(void),
*Task_1_1(void),
*Task_1_2(void)
*Global Variables: None
*/

#include "CB_Task_1_Sandbox.h"
/*
*
* Function Name: nodedetector
* Input: centreline,leftline,rightline
* Output: flagy
* Logic: Uses white line sensors and returns 1 if node is detected based on sensor values
* Example Call: nodedetector(0,255,0); //Returns 0 since this input does not fulfill conditions of node
*
*/

unsigned char nodedetector(unsigned char centreline, unsigned char leftline,unsigned char rightline) {

	// centreline,leftline and rightline stand for sensor values which are passed to it by forawrd_wls function

	unsigned char flag = 0;
	// a variable to find if any of the conditions becomes true and is initialised
	//by 0 which stand for false or no node detected
	//if any of the following conditions is satisfied ,a node has been detected,in which case
	//flag is set to 1 and is returned
	if (centreline == 255 && rightline == 255 && leftline == 255)
	{
		flag = 1;
		
	}

	else if (centreline == 0 && rightline == 255 && leftline == 255)
	{
		flag = 1;
		
	}
	else if (centreline == 255 && rightline == 0 && leftline == 255)
	{
		flag = 1;
		
	}
	else if (centreline == 255 && rightline == 255 && leftline == 0)
	{
		flag = 1;
		
	}
	return flag;
	//returns the result
}

unsigned char nodedetectorwhite(unsigned char centreline, unsigned char leftline, unsigned char rightline) {
	// centreline,leftline and rightline stand for sensor values which are passed to it by forawrd_wls function

	unsigned char flag = 0;
	// a variable to find if any of the conditions becomes true and is initialised
	//by 0 which stand for false or no node detected
	//if any of the following conditions is satisfied ,a node has been detected,in which case
	//flag is set to 1 and is returned
	if (centreline == 0 && leftline == 0 && rightline == 0) {
		flag = 1;
	}
	
	if (centreline == 255 && leftline == 0 && rightline == 0) {
		flag = 1;
	}
	return flag;//return result
}
/*
*
* Function Name: nodedetector1
* Input: centreline,leftline,rightline
* Output: unsigned char
* Logic: Uses white line sensors and returns 1 if node is detected based on sensor values,this nodetector has been
*made specifically for a path which has too much curve in which case a node may be detected even on the path
*this function returns 1 only when all three sensors detect black line
* Example Call: nodedetector1(0,255,0); Returns 0 since this input does not fulfill conditions of node
*
*/
unsigned char nodedetector1(unsigned char centreline, unsigned char leftline, unsigned char rightline) {
	// centreline,leftline and rightline stand for sensor values which are passed to it by forawrd_wls function

	unsigned char flag = 0;
	// a variable to find if any of the conditions becomes true and is initialised
	//by 0 which stand for false or no node detected
	//if following is satisfied ,a node has been detected,in which case
	//flag is set to 1 and is returned
	if (centreline == 255 && rightline == 255 && leftline == 255)
	{
		flag = 1;
		
	}

	return flag;
	//return result
}

/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/

void forward_wls(unsigned char node)
{

	unsigned char centreline, leftline, rightline;
	//three variables for sensor values of centre,left and right  sensors respectively
	unsigned char leftprox, frontprox, rightprox;

	unsigned char i = 1;
	//iteration variable to repeat the function for specified no. of nodes

	while (i <= node)
		//loop to repeat this till iteration variable reaches no. of nodes specified
	{
	
		leftline = ADC_Conversion(1);

		centreline = ADC_Conversion(2);

		rightline = ADC_Conversion(3);
			//store values returned by left,centre and right sensors respectively
		//these are stored just so that lastleft,lastcentre,lastright can be defined in first iteration

		do {//a loop to go forward until a node is detected and follow black line

			velocity(255, 255);//set velocity of motors to 200 and 200

			unsigned char lastleft = leftline;
		
			unsigned char lastcentre = centreline;
	
			unsigned char lastright = rightline;
			//store value of sensors in last iteration of sensor values to help in
			//logic explained ahead

			leftline = ADC_Conversion(1);
			centreline = ADC_Conversion(2);
			rightline = ADC_Conversion(3);
			//store values returned by sensors
			leftprox = ADC_Conversion(5);
			frontprox = ADC_Conversion(4);
			rightprox = ADC_Conversion(6);

			if (leftline != 0) {//if value returned by left sensor is not 0(white),bot is drifting from path
				
				velocity(125, 200);
				//velocities of motors are set such that bot turns left;
			}

			if (rightline != 0) {//if value returned by right sensor is not 0(white),bot is drifting from path
				
				velocity(200, 125);//velocities of motors are set such that bot turns right;
			}

			if (centreline == 0 && leftline == 0 && rightline == 0) {
				//it implies all sensor sense white and the bot went off path

				if (lastleft == 255) {
					//if value of left sensor in last iteration was 255(black),bot drifted right 
					//and went off path
					while (centreline != 255) {
						velocity(75, 150);
						_delay_ms(35);
						centreline = ADC_Conversion(2);
					}
					
				}
				else if (lastright == 255) {//if value of right sensor in last iteration was 255(black),bot drifted
					//left and went off path
					while (centreline != 255) {
						velocity(150, 75);
						_delay_ms(35);
						centreline = ADC_Conversion(2);
					}


				}




			}
			printf("\n %d %d %d", leftline, centreline, rightline);
			//printf("\n %d %d %d", leftprox, frontprox, rightprox);
			_delay_ms(25);
		
			forward();//moves forward
			
		} while (nodedetector(centreline, leftline, rightline) == 0);//until a node is detected
		printf("\n node detected----------");
		i = i + 1;//increase value of node iteration
		forward();//moves forward

		_delay_ms(250);
		//when bot detecs node, it moves forward for 260 ms so that it can cross the current node
	//so that its is not detected multiple times


	}
}
void forwardfollow() {
	unsigned char centreline, leftline, rightline;
	//three variables for sensor values of centre,left and right  sensors respectively
	unsigned char leftprox, frontprox, rightprox;

	unsigned char i = 1;
	//iteration variable to repeat the function for specified no. of nodes



		leftline = ADC_Conversion(1);

		centreline = ADC_Conversion(2);

		rightline = ADC_Conversion(3);
		//store values returned by left,centre and right sensors respectively
	//these are stored just so that lastleft,lastcentre,lastright can be defined in first iteration

		do {//a loop to go forward until a node is detected and follow black line

			velocity(255, 255);//set velocity of motors to 200 and 200

			unsigned char lastleft = leftline;

			unsigned char lastcentre = centreline;

			unsigned char lastright = rightline;
			//store value of sensors in last iteration of sensor values to help in
			//logic explained ahead

			leftline = ADC_Conversion(1);
			centreline = ADC_Conversion(2);
			rightline = ADC_Conversion(3);
			//store values returned by sensors
			leftprox = ADC_Conversion(5);
			frontprox = ADC_Conversion(4);
			rightprox = ADC_Conversion(6);

			if (leftline != 0) {//if value returned by left sensor is not 0(white),bot is drifting from path

				velocity(125, 200);
				//velocities of motors are set such that bot turns left;
			}

			if (rightline != 0) {//if value returned by right sensor is not 0(white),bot is drifting from path

				velocity(200, 125);//velocities of motors are set such that bot turns right;
			}

			if (centreline == 0 && leftline == 0 && rightline == 0) {
				//it implies all sensor sense white and the bot went off path

				if (lastleft == 255) {
					//if value of left sensor in last iteration was 255(black),bot drifted right 
					//and went off path
					while (centreline != 255) {
						velocity(75, 150);
						_delay_ms(35);
						centreline = ADC_Conversion(2);
					}

				}
				else if (lastright == 255) {//if value of right sensor in last iteration was 255(black),bot drifted
					//left and went off path
					while (centreline != 255) {
						velocity(150, 75);
						_delay_ms(35);
						centreline = ADC_Conversion(2);
					}


				}




			}
			printf("\n %d %d %d", leftline, centreline, rightline);
			//printf("\n %d %d %d", leftprox, frontprox, rightprox);
			_delay_ms(25);

			forward();//moves forward
			i = i + 1;
		} while (i<=8);//until a node is detected
	
		


	
}
void forward_wlswallfollow(unsigned char node)
{

	unsigned char centreline, leftline, rightline;
	//three variables for sensor values of centre,left and right  sensors respectively
	unsigned char leftprox, frontprox, rightprox;

	unsigned char i = 1;
	//iteration variable to repeat the function for specified no. of nodes

	while (i <= node)
		//loop to repeat this till iteration variable reaches no. of nodes specified
	{

		leftline = ADC_Conversion(1);

		centreline = ADC_Conversion(2);

		rightline = ADC_Conversion(3);
		//store values returned by left,centre and right sensors respectively
	//these are stored just so that lastleft,lastcentre,lastright can be defined in first iteration

		do {//a loop to go forward until a node is detected and follow black line

			velocity(255, 255);//set velocity of motors to 200 and 200

			unsigned char lastleft = leftline;

			unsigned char lastcentre = centreline;

			unsigned char lastright = rightline;
			//store value of sensors in last iteration of sensor values to help in
			//logic explained ahead

			leftline = ADC_Conversion(1);
			centreline = ADC_Conversion(2);
			rightline = ADC_Conversion(3);
			//store values returned by sensors
			leftprox = ADC_Conversion(5);
			frontprox = ADC_Conversion(4);
			rightprox = ADC_Conversion(6);

			if (leftline != 0) {//if value returned by left sensor is not 0(white),bot is drifting from path

				velocity(100, 200);
				//velocities of motors are set such that bot turns left;
			}

			if (rightline != 0) {//if value returned by right sensor is not 0(white),bot is drifting from path

				velocity(200, 100);//velocities of motors are set such that bot turns right;
			}

			if (centreline == 0 && leftline == 0 && rightline == 0) {
				//it implies all sensor sense white and the bot went off path

				if (frontprox == 32 && leftprox != 32 && rightprox != 32) {
					unsigned char av;
					av = (leftprox + rightprox) / 2;

					if (leftprox < av) {
						velocity(255, 235);
					}
					else if (rightprox < av) {
						velocity(235, 255);
					}
					printf("\n %d", av);
				}


			}
			_delay_ms(20);
			//printf("\n %d %d %d", leftline, centreline, rightline);
			printf("\n %d %d %d", leftprox, frontprox, rightprox);
			
			forward();//moves forward

		} while (nodedetector1(centreline, leftline, rightline) == 0);//until a node is detected

		i = i + 1;//increase value of node iteration
		forward();//moves forward

		_delay_ms(260);
		//when bot detecs node, it moves forward for 260 ms so that it can cross the current node
	//so that its is not detected multiple times


	}
}
/*
*
* Function Name: forward_wlssharp
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified,this function has been specifically
*made for path with sharp turns since on such paths bot has to go slow and also on such paths node detections
* had to be cahnged  due to too much curve of paths otherwise false node may be detected
* Example Call: forward_wlssharp(2); //Goes forward by two nodes
*
*/
void forward_wlssharp(unsigned char node)
{
	unsigned char centreline, leftline, rightline;
	//three variables for sensor values of centre,left and right  sensors respectively

	unsigned char i = 1;
	//iteration variable to repeat the function for specified no. of nodes

	while (i <= node)
	{//loop to repeat this till iteration variable reaches no. of nodes specified
		leftline = ADC_Conversion(1);
		centreline = ADC_Conversion(2);
		rightline = ADC_Conversion(3);
		//store values returned by left,centre and right sensors respectively
			//these are stored just so that lastleft,lastcentre,lastright can be defined in first iteration

		do {//a loop to go forward until a node is detected and follow black line
			velocity(150, 150);

			//lowers velocity of both motors as this function is specific for sharp turns
			unsigned char lastleft = leftline;
		
			unsigned char lastcentre = centreline;
		
			unsigned char lastright = rightline;
			//store value of sensors in last iteration of sensor values to help in
			//logic explained ahead
			
			leftline = ADC_Conversion(1);
			centreline = ADC_Conversion(2);
			rightline = ADC_Conversion(3);
			//store values returned by sensors
			
			
			 if (leftline!=0) {//if left sensor senses value is not 0(white) bot is moving away from path 

				soft_left();//adjusts itself by moving left

			}
			 else if (rightline != 0) {//if right sensor senses value is not 0(white) bot is moving away from path 

				soft_right();//adjusts itself by moving right

			 }

			 if (centreline == 0 && leftline == 0 && rightline == 0) {
				 //in case all snsor give values 0,
				 //it implies all sensor sense white and the bot went off path

				 if (lastleft == 255) {//in case value of left sensor in last iteration was 255(black),bot was
					 //drifting right and went off path

					 while (centreline != 255)//until centre sensor detects 255(black) bot turns left
					 {
						 soft_left();
						 centreline = ADC_Conversion(2);
					 }
				 }
				 else if (lastright == 255) {//in case value of left sensor in last iteration was 255(black),bot was
					 //drifting right and went off path

					 while (centreline != 255)//until centre sensor detects 255(black) bot turns right
					 {
						 soft_right();
						 centreline = ADC_Conversion(2);
					 }

				 }
			 }

		
			printf("\n %d %d %d", leftline, centreline, rightline);

			forward();

		} while (nodedetector1(centreline, leftline, rightline) == 0);

		i = i + 1;//increase value of node iteration variable

		forward();//bot moves forward

		_delay_ms(250);//when bot detecs node, it moves forward for 250 ms so that it can cross the current node
		//so that its is not detected multiple times 
		

	}

}
/*
*
* Function Name: forward_wlstillwhite
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified,this function has been specifically
*made to follow white line
* Example Call: forward_wlstillwhite(2); //Goes forward by two nodes
*
*/
void forward_wls_tillwhite(unsigned char node) {

	unsigned char centreline, leftline, rightline;
	//three variables for sensor values of centre,left and right  sensors respectively

	unsigned char i = 1;
	//iteration variable to repeat the function for specified no. of nodes

	while (i <= node)//loop to repeat this till iteration variable reaches no. of nodes specified
	{
		leftline = ADC_Conversion(1);
		centreline = ADC_Conversion(2);
		rightline = ADC_Conversion(3);
		//store values rerturned by sensors
		//these are stored just so that lastleft,lastcentre,lastright can be defined in first iteration

		do {
			velocity(180, 180);
			unsigned char lastleft = leftline;
			unsigned char lastcentre = centreline;
			unsigned char lastright = rightline;
			//store values returned by sensors in last iteration of sensor values

			leftline = ADC_Conversion(1);
			centreline = ADC_Conversion(2);
			rightline = ADC_Conversion(3);
			//store values rerturned by sensors

			if (leftline != 255) {//if left sensor does not return 255(black),bot is drifting from path
				
				velocity(40, 150);//set velocity such that bot moves right
			}
			if (rightline != 255) {//if right sensor does not return 255(black),bot is drifting from path
				
				velocity(150, 40);//set velocity such that bot moves left
			}
			if (centreline == 255 && rightline == 255 && leftline == 255) {
				if (lastleft == 0) {
					while (centreline != 0) {
						velocity(75, 150);
						_delay_ms(20);
						centreline = ADC_Conversion(2);
					}
				}
				else if (lastright == 0) {
					while (centreline != 0) {
						velocity(150, 75);
						_delay_ms(20);
						centreline = ADC_Conversion(2);
					}
				}
			}
			
			printf("\n %d %d %d", leftline, centreline, rightline);
			_delay_ms(20);
			forward();

		} while (nodedetectorwhite(centreline, leftline, rightline) == 0);//until nodetectorwhite returns 0 
		printf("\n node detected----------");
		i = i + 1;//increase value of iteration variable
		forward();
		_delay_ms(250);
		//when bot detecs node, it moves forward for 260 ms so that it can cross the current node
		//so that its is not detected multiple times 

	}
}
/*
*
* Function Name: forward_wlszigzag
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified,this function has been specifically
*made for disconnected paths where bot goes in zigzag motion
* Example Call: forward_wlszigzag(2); //Goes forward by two nodes
*
*/
void forward_wlszigzag(unsigned char node)
{	
	unsigned char centreline, leftline, rightline;
	//three variables for sensor values of centre,left and right  sensors respectively

	unsigned char i = 1;
	//iteration variable to repeat the function for specified no. of nodes



	while (i <= node)

	{
		unsigned char count = 1;
		leftline = ADC_Conversion(1);
		centreline = ADC_Conversion(2);
		rightline = ADC_Conversion(3);
		//store values rerturned by sensors
			//these are stored just so that lastleft,lastcentre,lastright can be defined in first iteration

		do {
			
			velocity(150, 150);
			unsigned char lastleft = leftline;
			unsigned char lastcentre = centreline;
			unsigned char lastright = rightline;
			//store values of sensors in last iteration 

			leftline = ADC_Conversion(1);
			centreline = ADC_Conversion(2);
			rightline = ADC_Conversion(3);
		//store values returned by sensors
		
			 if (leftline != 0) {//if left sensor does not return 0(white),bot is drifting right
				
				velocity(30, 190);//set velocity such that bot corrects its path
				_delay_ms(4);
				
			}
			else if (rightline != 0) {//if right sensor does not return 0(white),bot is drifting left
			
				velocity(190, 30);
				_delay_ms(4);
			}
			 else if (centreline == 0 && leftline == 0 && rightline == 0) {
				 //if all sensor return 0
				 //it implies all sensor sense white and the bot went off path

				 if (lastleft == 255) {//if value of left sensor in last iteration was 255,it drifted left and went off path

					 unsigned char e = 0;//a variable to repeat loop for some time only

					 while (centreline == 0 && leftline==0&&rightline==0 &&e< 100) {
						 _delay_ms(1);
							 velocity(20, 190);
						 //move left

						 e++;

						 leftline = ADC_Conversion(1);
						 centreline = ADC_Conversion(2);
						 rightline = ADC_Conversion(3);
						 //store value of sensors

					 } 
					 //the above loop works for 100ms +execution time so that bot does not keep moving left
						
				 }
				 else if (lastright == 255) {//if value of left sensor in last iteration was 255,it drifted left and went off path
					 
					 unsigned char e = 0;
					 while (centreline==0&&leftline==0&&rightline==0&&e<200) {
						 _delay_ms(1);
						 velocity(190, 20);
				//move right
						
						 e++;

						 leftline = ADC_Conversion(1);
						 centreline = ADC_Conversion(2);
						 rightline = ADC_Conversion(3);
						 //store value of sensors

					 }
					 //the above loop works for 100ms +execution time so that bot does not keep moving right
				 }
				 else {//otherwise the bot went off path due to disconnection of path

					 unsigned char flag2 = 0;
					 unsigned char flag1 = 0;
					 // variables to check executiion of loops

					 velocity(180, 180);
						 _delay_ms(80);
						 //moves forward for 80 ms

						 unsigned char q = 0;
						 //variable to keep time check on execution of loop

						 while (centreline == 0 && leftline == 0 && rightline == 0 && q < 200) {//loop to search for path on left side for 200 ms + execution time

							 flag1 = 0;
							 flag2 = 0;

							 left();
							 _delay_ms(1);
							 //move left

							 q++;

							 flag1 = 1;
							 leftline = ADC_Conversion(1);
							 centreline = ADC_Conversion(2);
							 rightline = ADC_Conversion(3);

						 } //until centre line finds path

						 if (flag1 == 1) {//if last loop was executed but no path was found

							 unsigned char w = 0;
							 //variable to keep time check on loop

							 while (centreline == 0 && leftline == 0 && rightline == 0 && w < 400) {
								
								 right();
								 _delay_ms(1);
								 
								 w++;

								 flag2 = 1;
								 leftline = ADC_Conversion(1);
								 centreline = ADC_Conversion(2);
								 rightline = ADC_Conversion(3);

							 } //bot moves right until path is found for 400 ms
						 }
						 //in case no path is found bot turns left again so that this whole loop is repeated again
						 if (flag2 == 1) {
							 unsigned char e=0;
							 //loop to keep time check on loop

							 while (centreline == 0  && leftline == 0 && rightline == 0 && e < 200) {
								
								 left();
								 _delay_ms(1);

								 e++;

								
								 leftline = ADC_Conversion(1);
								 centreline = ADC_Conversion(2);
								 rightline = ADC_Conversion(3);

							 } 
						 }

					
				 }

			 }
		
			printf("\n %d %d %d", leftline, centreline, rightline);
			_delay_ms(20);
			forward();
			
		} while (nodedetector1(centreline, leftline, rightline) == 0);//until a node is detected

		i = i + 1;//increase value of node iteration variable

		forward();
		_delay_ms(250);
		//when bot detects node, it moves forward for 260 ms so that it can cross the current node
		//so that its is not detected multiple times 

	}
}



/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/

void left_turn_wls(void)
{
	left();
	_delay_ms(230);
	///movees left for 230 ms so as to cross current line

	unsigned char centreline;
	//variable to store value returned by centre sensor

	do {
		centreline = ADC_Conversion(2);
		left();

	} while (centreline != 255);//move left until centre sensor returns 255(black)
}

/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)
{
	right();
	_delay_ms(230);
	///movees right for 230 ms so as to cross current line

	unsigned char centreline;
	//variable to store value returned by centre sensor

	do {
		centreline = ADC_Conversion(2);
	     right();
	} while (centreline != 255);//move right until centre sensor returns 255(black)
}
void left_turn_wlstillwhite(void)
{
	left();
	_delay_ms(230);
	///movees left for 230 ms so as to cross current line

	unsigned char centreline;
	//variable to store value returned by centre sensor

	do {
		centreline = ADC_Conversion(2);
		left();

	} while (centreline != 0);//move left until centre sensor returns 255(black)
}

/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wlstillwhite(void)
{
	right();
	_delay_ms(230);
	///movees right for 230 ms so as to cross current line

	unsigned char centreline;
	//variable to store value returned by centre sensor

	do {
		centreline = ADC_Conversion(2);
		right();
	} while (centreline != 0);//move right until centre sensor returns 255(black)
}
void checkproximity(void) {


	unsigned char centreline, leftline, rightline;
	//three variables for sensor values of centre,left and right  sensors respectively
	unsigned char leftprox, frontprox, rightprox;

	unsigned char i = 1;
	//iteration variable to repeat the function for specified no. of nodes

	while (i <= 2)
	{


		//loop to repeat this till iteration variable reaches no. of nodes specified


		leftline = ADC_Conversion(1);

		centreline = ADC_Conversion(2);

		rightline = ADC_Conversion(3);
		//store values returned by left,centre and right sensors respectively
	//these are stored just so that lastleft,lastcentre,lastright can be defined in first iteration

		do {//a loop to go forward until a node is detected and follow black line

			velocity(255, 255);//set velocity of motors to 200 and 200

			unsigned char lastleft = leftline;

			unsigned char lastcentre = centreline;

			unsigned char lastright = rightline;
			//store value of sensors in last iteration of sensor values to help in
			//logic explained ahead

			leftline = ADC_Conversion(1);
			centreline = ADC_Conversion(2);
			rightline = ADC_Conversion(3);
			//store values returned by sensors
			leftprox = ADC_Conversion(5);
			frontprox = ADC_Conversion(4);
			rightprox = ADC_Conversion(6);

			if (leftline != 0) {//if value returned by left sensor is not 0(white),bot is drifting from path

				velocity(125, 200);
				//velocities of motors are set such that bot turns left;
			}

			if (rightline != 0) {//if value returned by right sensor is not 0(white),bot is drifting from path

				velocity(200, 125);//velocities of motors are set such that bot turns right;
			}

			if (centreline == 0 && leftline == 0 && rightline == 0) {
				//it implies all sensor sense white and the bot went off path

				if (lastleft == 255) {
					//if value of left sensor in last iteration was 255(black),bot drifted right 
					//and went off path
					while (centreline != 255) {
						velocity(75, 150);
						_delay_ms(35);
						centreline = ADC_Conversion(2);
					}

				}
				else if (lastright == 255) {//if value of right sensor in last iteration was 255(black),bot drifted
					//left and went off path
					while (centreline != 255) {
						velocity(150, 75);
						_delay_ms(35);
						centreline = ADC_Conversion(2);
					}


				}




			}
			printf("\n %d %d %d", leftline, centreline, rightline);
			//printf("\n %d %d %d", leftprox, frontprox, rightprox);
			_delay_ms(25);

			forward();//moves forward

		} while (leftprox == 32 && frontprox == 32 && rightprox == 32);//until a node is detected
		printf("\n node detected----------");
		i++;
	}
	
		//when bot detecs node, it moves forward for 260 ms so that it can cross the current node
	//so that its is not detected multiple times


	
}
void forwardfollowwhite(void) {
	unsigned char centreline, leftline, rightline;
	//three variables for sensor values of centre,left and right  sensors respectively

	unsigned char i = 1;
	//iteration variable to repeat the function for specified no. of nodes

	while (i <= 8)//loop to repeat this till iteration variable reaches no. of nodes specified
	{
		leftline = ADC_Conversion(1);
		centreline = ADC_Conversion(2);
		rightline = ADC_Conversion(3);
		//store values rerturned by sensors
		//these are stored just so that lastleft,lastcentre,lastright can be defined in first iteration

		do {
			velocity(180, 180);
			unsigned char lastleft = leftline;
			unsigned char lastcentre = centreline;
			unsigned char lastright = rightline;
			//store values returned by sensors in last iteration of sensor values

			leftline = ADC_Conversion(1);
			centreline = ADC_Conversion(2);
			rightline = ADC_Conversion(3);
			//store values rerturned by sensors

			if (leftline != 255) {//if left sensor does not return 255(black),bot is drifting from path

				velocity(40, 150);//set velocity such that bot moves right
			}
			if (rightline != 255) {//if right sensor does not return 255(black),bot is drifting from path

				velocity(150, 40);//set velocity such that bot moves left
			}
			if (centreline == 255 && rightline == 255 && leftline == 255) {
				if (lastleft == 0) {
					while (centreline != 0) {
						velocity(75, 150);
						_delay_ms(20);
						centreline = ADC_Conversion(2);
					}
				}
				else if (lastright == 0) {
					while (centreline != 0) {
						velocity(150, 75);
						_delay_ms(20);
						centreline = ADC_Conversion(2);
					}
				}
			}

			printf("\n %d %d %d", leftline, centreline, rightline);
			_delay_ms(20);
			forward();
			i = i + 1;
		} while (i<=25);
		printf("\n node detected----------");
		
		
		//when bot detecs node, it moves forward for 260 ms so that it can cross the current node
		//so that its is not detected multiple times 

	}
}
void leftturndelay(void) {
	left();
	_delay_ms(380);
}
/*
*
* Function Name: e_shape
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a e shape path on the arena
* Example Call: e_shape();
*/
void e_shape(void)
{
	forward_wls(1);
	right_turn_wls();
	forward_wls(2);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
}


/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.1 logic
* Example Call: Task_1_1();
*/
void Task_1_1(void)
{
	// Write your task 1.1 Logic here
	forward_wls(1);
	left_turn_wls();
	forward_wls(4);
right_turn_wls();
	forward_wlssharp(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wlszigzag(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	forward_wls_tillwhite(1);
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
}

/*
*
* Function Name: Task_1_2
* Input: void
* Output: void
* Logic: Use this function to encapsulate your Task 1.2 logic
* Example Call: Task_1_2();
*/
void Task_1_2(void)
{
	//write your task 1.2 logic here
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	checkproximity();
	pick();//red
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wlswallfollow(2);
	stop();
	place();//H1red
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	checkproximity();
	pick();//brown
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wlswallfollow(1);
	left_turn_wls();
	forward_wls(2);
	right_turn_wls();
	forward_wls(1);
	place();//H5browncompleted
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	checkproximity();
	pick();//black
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wlszigzag(1);
	forward_wls(1);
	stop();
	place();//H3black
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	checkproximity();
	pick();//blue
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(3);
	left_turn_wls();
	forward_wlswallfollow(2);
	stop();
	place();//H2blue
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	checkproximity();
	pick();//2red
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wlswallfollow(1);
	right_turn_wls();
	forward_wls(2);
	left_turn_wls();
	forward_wls(1);
	stop();
	place();
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	checkproximity();
	pick();//green
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wlswallfollow(2);
	stop();
	place();//H2greencompleted
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	checkproximity();
	pick();//black2
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(3);
	left_turn_wls();
	forward_wls(1);
	forward_wls_tillwhite(1);
	left_turn_wlstillwhite();
	forwardfollowwhite();
	stop();
	place();//H5blac
	leftturndelay();
	left_turn_wlstillwhite();
	forward_wls_tillwhite(1);
	right_turn_wlstillwhite();
	forward_wls_tillwhite(1);
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	checkproximity();
	pick();//pink2
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(3);
	right_turn_wls();
	forward_wlswallfollow(1);
	forward_wls(1);
	stop();
	place();//pink2
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(1);
	left_turn_wls();
	forward_wls(1);
	checkproximity();
	pick();//brown2
	right_turn_wls();
	forwardfollow();
	forward_wls(1);
	right_turn_wls();
	forward_wls(5);
	right_turn_wls();
	forward_wls(1);
	forward_wls_tillwhite(1);
	right_turn_wlstillwhite();
	forwardfollowwhite();
	place();//H5brown
	

}
