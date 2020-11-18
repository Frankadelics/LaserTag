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
    int ammo = 10;
    bool alive = true;
public:
    void setAmmo(int amount) { ammo > 10 ? ammo = 10 : ammo += amount; }
    void setHealth(int amount) { health > 10 ? health = 10 : health += amount; }
    void setAlive(bool living) { alive = living; }
    
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
void reset(Player& p1)
{
    p1.setHealth(10);
    p1.setAmmo(5);
    p1.setAlive(true);
    Serial.println("You have been reset.");
    Serial.println("Health: 10 | Ammo: 5 | Alive = True");
}
void reload(Player& p1)
{
    while (p1.getAmmo() < 10)
    {
        if (digitalRead(buttonPin) == LOW)
            break;
        p1.setAmmo(1);
        Serial.print("Ammo: ");
        Serial.println(p1.getAmmo());
        beep(B, C);
        delay(1000);
    }
}
void shoot(Player& p1)
{
    p1.setAmmo(-1);
    Serial.print("Ammo: ");
    Serial.println(p1.getAmmo());
    digitalWrite(laserPin, HIGH);
    beep(A, F);
    digitalWrite(laserPin, LOW);
    delay(200);
}
void checkHit(Player& p1)
{
    lightLVL = analogRead(A0);
    if (lightLVL > 200)
    {
        beep(G, A);
        digitalWrite(redLEDPin, HIGH); 
        p1.setHealth(-1);
        if (p1.getHealth() == 0)
            p1.setAlive(false);
        delay(1000);
        Serial.print("HP: ");
        Serial.println(p1.getHealth());
    }
    else
        digitalWrite(redLEDPin, LOW);
}
void checkAmmo(Player& p1)
{
    if (digitalRead(buttonPin) == LOW && p1.getAmmo() > 0)
        shoot(p1);
    else if (digitalRead(buttonPin) == LOW && p1.getAmmo() <= 0)
        beep(F, F);
    else 
        reload(p1);
}
void loop()
{
    checkHit(player1);
    checkAmmo(player1);

    if (!player1.getAlive())
        reset(player1);
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