#define KEY_PIN 2
#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define A 11
#define B 10
#define C 9
#define D 8
#define E 7
#define F 6
#define G 5
#define DP 4
#define Control_left 3
#define Control_right A1

bool light_state;
void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);
    pinMode(A0, INPUT);
    pinMode(KEY_PIN, INPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(Control_left, OUTPUT);
    pinMode(Control_right, OUTPUT);
    // 設定腳位 11 到 3 為 OUTPUT
    for (int pin = 3; pin <= 11; pin++)
    {
        pinMode(pin, OUTPUT);
    }
    light_state = false;
    digitalWrite(Control_left, HIGH);
    digitalWrite(Control_right, HIGH);
}

void loop()
{
    if (digitalRead(KEY_PIN) == HIGH)
    {
        light_state = !light_state;
    }
    delay(200);

    if (light_state)
    {
        float distance = getDistance(TRIGGER_PIN, ECHO_PIN);
        Serial.print("Distance: ");
        Serial.print(distance);
        Serial.println(" cm");
        showDistance(distance);
    }
    else
    {
        float tmp = getTemperature();
        getTemperature();
        Serial.print("tmp: ");
        Serial.print(tmp);
        Serial.println(" C ");
        showTemp(tmp);
    }
}

void showDistance(float distance)
{
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        showsevenseg(int(distance / 100));
        delay(10);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        showsevenseg(int(distance / 100));
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        showsevenseg(int(distance) % 100 / 10);
        delay(5);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        showsevenseg(int(distance) % 100 / 10);
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        showsevenseg(int(distance) % 10);
        delay(5);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        showsevenseg(int(distance) % 10);
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        displayC();
        delay(5);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        displayC();
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        displaym();
        delay(5);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        displaym();
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        displayspace();
        delay(5);
    }
}

void showTemp(float tmp)
{
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        showsevenseg(int(tmp / 10) % 10);
        delay(10);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        showsevenseg(int(tmp / 10) % 10);
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        showsevenseg(int(tmp) % 10);
        delay(5);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        showsevenseg(int(tmp) % 10);
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        displaypoint();
        delay(5);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        displaypoint();
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        showsevenseg(int(tmp * 10) % 10);
        delay(5);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        showsevenseg(int(tmp * 10) % 10);
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        displaydegree();
        delay(5);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        displaydegree();
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        displayC();
        delay(5);
    }
    for (int i = 0; i < 50; i++)
    {
        digitalWrite(Control_left, LOW);
        digitalWrite(Control_right, HIGH);
        displayC();
        delay(5);
        digitalWrite(Control_left, HIGH);
        digitalWrite(Control_right, LOW);
        displayspace();
        delay(5);
    }
}

float getDistance(int trigPin, int echoPin)
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigPin, LOW);

    long duration = pulseIn(echoPin, HIGH, 30000); // 20ms timeout
    return duration * 0.034 / 2;                   // Convert duration to distance in centimeters
}

float getTemperature()
{
    float tmp;
    tmp = analogRead(A0) * (500.0) / 1024;
    return tmp;
}

void displayC()
{
    for (int i = 4; i < 12; i++)
    {
        digitalWrite(i, HIGH); // 先關閉所有段
    }

    digitalWrite(A, LOW);
    digitalWrite(F, LOW);
    digitalWrite(E, LOW);
    digitalWrite(D, LOW);
}

void displaym()
{
    for (int i = 4; i < 12; i++)
    {
        digitalWrite(i, HIGH); // 先關閉所有段
    }
    digitalWrite(C, LOW);
    digitalWrite(G, LOW);
    digitalWrite(E, LOW);
}

void displaypoint()
{
    for (int i = 4; i < 12; i++)
    {
        digitalWrite(i, HIGH); // 先關閉所有段
    }
    digitalWrite(DP, LOW);
}

void displayspace()
{
    for (int i = 4; i < 12; i++)
    {
        digitalWrite(i, HIGH); // 先關閉所有段
    }
}

void displaydegree()
{
    for (int i = 4; i < 12; i++)
    {
        digitalWrite(i, HIGH); // 先關閉所有段
    }
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(G, LOW);
    digitalWrite(F, LOW);
}

void showsevenseg(int num)
{
    // 清除所有段（共陽極：輸出 HIGH 表示關閉）
    for (int i = 4; i < 12; i++)
    {
        digitalWrite(i, HIGH); // 先關閉所有段
    }

    switch (num)
    {
    case 0:
        digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        break;
    case 1:
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        break;
    case 2:
        digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(G, LOW);
        break;
    case 3:
        digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(G, LOW);
        break;
    case 4:
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
        break;
    case 5:
        digitalWrite(A, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
        break;
    case 6:
        digitalWrite(A, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
        break;
    case 7:
        digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        break;
    case 8:
        digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(E, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
        break;
    case 9:
        digitalWrite(A, LOW);
        digitalWrite(B, LOW);
        digitalWrite(C, LOW);
        digitalWrite(D, LOW);
        digitalWrite(F, LOW);
        digitalWrite(G, LOW);
        break;
    }
}
