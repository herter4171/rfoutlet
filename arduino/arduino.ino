/*
 * This is a simple sketch for polling analog sensors used to track
 * levels of water and light being supplied to the plant.
 *
 * Pin layout
 * ----------------------
 * A0: Photoresistor
 * A1: Hygrometer
 * A2: Water level sensor
 * ----------------------
 */

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  for (int i = A0; i < A3; i++)
  {
    // Read and map to 8 bits
    int val = analogRead(i);
    val = map(val, 0, 1023, 0, 255);

    // Print val
    Serial.print(val);

    // Print comma to coninue line or newline
    char tailChar = ',';    
    if (i == A2)
    {
      tailChar = '\n';
    }
    Serial.print(tailChar);
  }

  delay(50); // Milliseconds of pause between reads
}
