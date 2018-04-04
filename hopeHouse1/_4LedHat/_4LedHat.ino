
typedef void applyFunc (int);

int pins[] = {LED_BUILTIN, 6, 7, A2, A3};
int numPins = sizeof(pins)/sizeof(pins[0]);

void setup() {
  forEachLedCallFunction(setMode);
}

void loop() {
    forEachLedCallFunction(flashLed);       
}

void setMode(int i) {
    pinMode(pins[i], OUTPUT);  
}

void flashLed(int i) {
    digitalWrite(pins[i], HIGH);
    delay(1000);                    
    digitalWrite(pins[i], LOW); 
    delay(100);  
}

void forEachLedCallFunction(applyFunc f) {
  for(int i=0; i < numPins; ++i) {
    f(i);
  }  
}


double sampleNormal() {
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) return sampleNormal();
    double c = sqrt(-2 * log(r) / r);
    return u * c;
}

double randomNormal(double u, double d) {
 
        static double t = 0.0;
        double x, w1, w2, r;
 
        if( t == 0 ) {
               do{
                      w1 = 2.0 * randomFloat() - 1.0;
                      w2 = 2.0 * randomFloat() - 1.0;
                      r = w1 * w1 + w2 * w2;
                  }
                while( r >= 1.0 );
                r = sqrt( -2.0*log(r) / r );
                t = w2 * r;  // was v2 * r...
                return( u + w1 * r * d );
       }
 
        else {
                x = t;
                t = 0.0;
                return( u + x * d);
        } 
}

float randomFloat() {
  return random(0, 1000000)/1000000.0;
}



