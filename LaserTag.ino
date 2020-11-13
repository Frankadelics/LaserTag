const int lightLVL = 0;
const int redLEDPin = 3;
const int piezoPin = 12;
const int G = 392;
const int A = 440;
const int buttonPin = 11;
const int laserPin = 13;
//comment fdf
class Player {
private:
  int health = 10;
  int ammo = 5;
  int lives = 2;
  bool alive = true;
public:
  void increaseAmmo(int amount) 
  {
    if (ammo > 5)
      ammo = 10;
    else
      ammo += amount;
  }
  void increaseHealth(int amount) 
  {
    if (health > 10)
      health = 10;
    else
      health += amount;
  }
   
  void decreaseHealth(int amount) 
  {
    if (health <= 0)
      alive = false;
    else
      health -= amount;
  }
  void decreaseAmmo(int amount) 
  {
    if (ammo <= 0)
      ammo = 0;
    else 
      ammo -= amount;
  }

  int getHealth() {return health;}
  int getAmmo() {return ammo;}
  int getLives() {return lives;}
  bool getAlive {return alive;}
}

void checkHit()
{
  lightLVL = analogRead(A0);
  Serial.println(lightLVL);
  if (lightLVL > 200)
  {
    digitalWrite(redLEDPin, HIGH);
    tone(piezoPin, G*5);
    delay(100);
    tone(piezoPin, A*3);
    delay(100);
    noTone(piezoPin);
  }
  else
    digitalWrite(redLEDPin, LOW);
}

void shootLaser()
{
  if (digitalRead(buttonPin) == LOW)
  {
    digitalWrite(laserPin, HIGH);
    tone(piezoPin, A*2);
    delay(100);
    checkHit();
    noTone(piezoPin);
    digitalWrite(laserPin, LOW);
    delay(200);
  }
  else
    digitalWrite(laserPin, LOW);
}

void setup()
{
  Serial.begin(9600);
  pinMode(redLEDPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(laserPin, OUTPUT);

  digitalWrite(redLEDPin, LOW);
  digitalWrite(buttonPin, HIGH);
  digitalWrite(laserPin, LOW);
}

void loop()
{
  checkHit();
  shootLaser();
}
