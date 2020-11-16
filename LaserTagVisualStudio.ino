int lightLVL = 0;
const int redLEDPin = 3;
const int piezoPin = 12;
const int buttonPin = 11;
const int laserPin = 13;

enum Note {
    A = 440, B = 494, C = 262, D = 294, E = 330, F = 349, G = 392
};

class Player {
private:
    int health = 10;
    int ammo = 5;
    bool alive = true;
public:
    void increaseAmmo(int amount) { ammo > 10 ? 10 : ammo += amount; }
    void increaseHealth(int amount) { health > 10 ? 10 : health += amount; }

    void decreaseHealth(int amount) { health <= 0 ? alive = false : health -= amount; }
    void decreaseAmmo(int amount) { ammo <= 0 ? ammo = 0 : ammo -= amount; }

    int setAlive(bool living) { alive = living; }
    int getHealth() { return health; }
    int getAmmo() { return ammo; }
    bool getAlive() { return alive; }
} player1;

void beep(Note freq1, Note freq2)
{
    tone(piezoPin, freq1);
    delay(100);
    tone(piezoPin, freq2);
    delay(100);
    noTone(piezoPin);
}
void reset(Player p1)
{
    p1.increaseHealth(10);
    p1.increaseAmmo(5);
    p1.setAlive(true);
    Serial.println("You have been reset. /n Health: 10 /n Ammo: 5 /n Alive = True");
}

void shootLaser()
{
    if (digitalRead(buttonPin) == LOW)
    {
        digitalWrite(laserPin, HIGH);
        beep(A, F);
        digitalWrite(laserPin, LOW);
        delay(200);
    }
    else
        digitalWrite(laserPin, LOW);
}

void checkHit(Player& p1)
{
    lightLVL = analogRead(A0);
    if (lightLVL > 200)
    {
        beep(G, A);
        digitalWrite(redLEDPin, HIGH); 
        p1.decreaseHealth(1);
        Serial.print("Current Health: ");
        Serial.println(p1.getHealth());
    }
    else
        digitalWrite(redLEDPin, LOW);
}

void loop()
{
    while (player1.getAlive())
    {
        checkHit(player1);
        shootLaser();
    }

    if (player1.getAlive() == false)
    {
        Serial.print("Game Over! Health reached zero.");
        reset(player1);
    }
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