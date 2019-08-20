#pragma config(Sensor, S1,     Touch,          sensorEV3_Touch)
#pragma config(Sensor, S2,     Sonar,          sensorEV3_Ultrasonic)
#pragma config(Sensor, S3,     Gyro,           sensorEV3_Gyro)
#pragma config(Sensor, S4,     Colour,         sensorEV3_Color, modeEV3Color_Color)

	int foundPerson = 0;
	int turn = 78;
	int turnx2 = 178;


void checkSoundFile(const char *pFileName)
{
	bool bExists;

	bExists = bEv3FileExists(pFileName);
	while (!bSoundQueueAvailable)
	{}
	playSoundFile(pFileName);
	return;
}

	void playAnalyzeSound(){
		bPlaySounds = true;
		while(bSoundActive) {
			setSoundVolume(100);
			checkSoundFile("Analyze.wav");
			clearSounds();
	}
}


	/*
void hardCode90LeftTurn() {
	clearTimer(T1);
	while(time1[T1] < 750) {
		motor[motorB] = -20;
		motor[motorC] = 20;
	}
}

void hardCode90RightTurn() {
	clearTimer(T1);
	while(time1[T1] < 750) {
		motor[motorB] = -20;
		motor[motorC] = 20;
	}
}
*/
void forwardToDistanceOrRed(int d) {
	while((SensorValue(Colour) != 5) && (SensorValue(Sonar) > d)){
		motor[motorB] = 20;
		motor[motorC] = 20;
	}
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(200);
}

void leftTurn(int d)
{
	int start = SensorValue(Gyro);
	while(SensorValue(Gyro) > start - d) {
		motor[motorB] = 0;
		motor[motorC] = 10;
	}
}

void rightTurn(int d)
{
	int start = SensorValue(Gyro);
	while(SensorValue(Gyro) < start + d){
		motor[motorB] = 10;
		motor[motorC] = 0;
	}
}

void forwardToDistance(int d){
	while(SensorValue(Sonar) > d) {
		motor[motorC] = 20;
		motor[motorB] = 20;
	}
}

void rightTurnOnSpot(int d) {
	int start = SensorValue(Gyro);
	while(SensorValue(Gyro) < start + d){
		motor[motorB] = 10;
		motor[motorC] = -10;
	}
}

void leftTurnOnSpot(int d) {
	int start = SensorValue(Gyro);
	while(SensorValue(Gyro) > start - d) {
		motor[motorB] = -10;
		motor[motorC] = 10;
	}
}

void moveUntilRed(int s){
	while(SensorValue(Colour) != 5){
		motor[motorB] = s;
		motor[motorC] = s;
	}
	motor[motorB] = 0;
	motor[motorC] = 0;
	wait1Msec(200);
}

void reverseForTime(int t){
	clearTimer(T1);
	while(time1[T1] < t) {
		motor[motorB] = -20;
		motor[motorC] = -20;
	}
		motor[motorB] = 0;
		motor[motorC] = 0;
}

void forwardForTime(int t){
	clearTimer(T1);
	while(time1[T1] < t) {
		motor[motorB] = 20;
		motor[motorC] = 20;
	}
		motor[motorB] = 0;
		motor[motorC] = 0;
}

void lowerArm() {
	clearTimer(T1);
	while(time1[T1] < 1000) {
		motor[motorA] = -25;
	}
}

void raiseArm() {
	clearTimer(T1);
	while(time1[T1] < 1000) {
		motor[motorA] = 25;
	}
}

task main()
{
	playAnalyzeSound();
	int a;
	int b;
	int c;
	int count = 0;
	while(count < 4){
		forwardToDistanceOrRed(9);

		//Fire room found
		if(SensorValue(Colour) == 5){
					reverseForTime(500);
					rightTurnOnSpot(turnx2);
					moveUntilRed(-20);
					leftTurnOnSpot(turn);
					reverseForTime(2000);
					rightTurnOnSpot(turnx2);
					count++;
		}
		//Not fire
		else{
			 a = SensorValue(Sonar);
				leftTurnOnSpot(20);
				motor[motorB] = 0;
				motor[motorC] = 0;
				wait1Msec(400);
				 b = SensorValue(Sonar);
				rightTurnOnSpot(40);
				motor[motorB] = 0;
				motor[motorC] = 0;
				wait1Msec(400);
			c = SensorValue(Sonar);
			leftTurnOnSpot(20);
				motor[motorB] = 0;
				motor[motorC] = 0;
				wait1Msec(400);



				//rescue found
				if ((b >= 15) || (c >= 15)) {
					if (foundPerson == 0) {
							foundPerson++;
							reverseForTime(250);
							lowerArm();
							wait1Msec(400);
							forwardForTime(400);
							raiseArm();
							wait1Msec(200);
							forwardToDistance(12);
							leftTurnOnSpot(turn);
							forwardToDistanceOrRed(9);
							playAnalyzeSound();
							count++;

					}
			}


	//empty or box room
	else {
		leftTurnOnSpot(turn);
		forwardToDistance(9);
		reverseForTime(200);
		leftTurnOnSpot(turn);

		motor[motorB] = 0;
		motor[motorC] = 0;
		wait1Msec(300);

		if (SensorValue(Sonar) > 15) {
			motor[motorB] = 20;
			motor[motorC] = 20;
			wait1Msec(500);

			motor[motorB] = 0;
			motor[motorC] = 0;
			wait1Msec(300);

			motor[motorB] = -20;
			motor[motorC] = -20;
			wait1Msec(500);
		}

		//If sensor < 12 (box room)
			if (SensorValue(Sonar) <= 15) {

				motor[motorB] = 0;
				motor[motorC] = 0;
				wait1Msec(300);
				leftTurnOnSpot(turnx2);
				forwardToDistance(9);
				leftTurnOnSpot(turn);
				} else {
					rightTurn(turn);
					forwardToDistanceOrRed(9);
				}
				playAnalyzeSound();
				count++;
			}
		}
}
}
