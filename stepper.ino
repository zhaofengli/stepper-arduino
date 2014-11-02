/*
	Simple step motor demo
	
	by Zhaofeng Li
*/

#define delayTime 10
unsigned char motorPins[4] =
	{ 13  , 12  , 11  , 10   };

// Stepper switching sequence :)
#ifdef useHalfStep
// half-step
#define totalSteps 8
unsigned char seq[totalSteps][4] = {
	{ HIGH, LOW , LOW , LOW  }, // 1
	{ HIGH, HIGH, LOW , LOW  }, // 2
	{ LOW , HIGH, LOW , LOW  }, // 3
	{ LOW , HIGH, HIGH, LOW  }, // 4
	{ LOW , LOW , HIGH, LOW  }, // 5
	{ LOW , LOW , HIGH, HIGH }, // 6
	{ LOW , LOW , LOW , HIGH }, // 7
	{ HIGH, LOW , LOW , HIGH }, // 8
};
#else
// full-step
#define totalSteps 4
unsigned char seq[totalSteps][4] = {
	{ HIGH, LOW , LOW , LOW  }, // 1
	{ LOW , HIGH, LOW , LOW  }, // 2
	{ LOW , LOW , HIGH, LOW  }, // 3
	{ LOW , LOW , LOW , HIGH }, // 4
};
#endif

// Send a single step to the motor
void sendStep( unsigned char step[4] ) {
	unsigned char i = 0;
	for ( i = 0; i <= 3; i++ ) {
		digitalWrite( motorPins[i], step[i] );
	}
}

// Turn the motor (i.e. send a complete sequence to the motor)
void turn() {
	unsigned char i = 0;
	for ( i = 0; i <= totalSteps - 1; i++ ) {
		sendStep( seq[i] );
		delay( delayTime );
	}
}

void setup() {
	unsigned char i = 0;
	for ( i = 0; i <= 3; i++ ) {
		pinMode( motorPins[i], OUTPUT );
	}
}

void loop() {
	turn();
}
