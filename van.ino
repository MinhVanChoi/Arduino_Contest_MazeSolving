// Cảm biến siêu âm
const int TrigFront = 7;
const int EchoFront = 8;
const int TrigRight = 9;
const int EchoRight = 10;
const int TrigLeft = 12;
const int EchoLeft = 13;
bool isForward = false;
// Thêm hằng số và biến mới
#define LEFT_MIN 7
unsigned long stuckStartTime = 0;
bool isStuck = false;
int stuckCount = 0; // Đếm số lần khoảng cách không đổi hoặc nhiễu

// Động cơ
#define IN1 5
#define IN2 6
#define IN3 3
#define IN4 11

// Cấu hình
#define MAX_SPEED 70
#define MIN_SPEED 0
#define DIS 7
#define RIGHT_DIS 7
#define MIN_DIS 7
#define CHANGE_THRESHOLD 20
#define FORWARD_TIMEOUT 5000 // 10 giây cho động cơ chạy liên tục
unsigned long  forwardStartTime = 0; // Thời gian chạy tiến thẳng

enum RobotState {IDLE, FORWARD, TURN_LEFT, TURN_RIGHT, REVERSE, UTURN};
RobotState currentState = IDLE;

long lastFront = -1;

void setup() {
    Serial.begin(9600);
    pinMode(TrigFront, OUTPUT); pinMode(EchoFront, INPUT);
    pinMode(TrigRight, OUTPUT); pinMode(EchoRight, INPUT);
    pinMode(TrigLeft, OUTPUT);  pinMode(EchoLeft, INPUT);
    pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
}

// --- ĐO KHOẢNG CÁCH ---
long getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW); delayMicroseconds(2);
    digitalWrite(trigPin, HIGH); delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH, 30000);
    if (duration == 0) return -1;
    return duration / 2 / 29.412;
}

// --- ĐỘNG CƠ ---
void stopMotors() {
    digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
    isForward = false;
}

void motor1Forward(int speed) {
    digitalWrite(IN1, LOW); analogWrite(IN2, speed);
}

void motor2Forward(int speed) {
    digitalWrite(IN3, LOW); analogWrite(IN4, speed);
}

void motor1Backward(int speed) {
    digitalWrite(IN1, HIGH); analogWrite(IN2, 255 - speed);
}

void motor2Backward(int speed) {
    digitalWrite(IN3, HIGH); analogWrite(IN4, 255 - speed);
}
void moveForward(int speed) {
    motor1Forward(speed);
    motor2Forward(speed);
    currentState = FORWARD;
    if (!isForward) {
        isForward = true;
        forwardStartTime = millis(); // Bắt đầu đếm thời gian tiến thẳng
    }
}
void turnLeft() {
    motor1Backward(MAX_SPEED);
    motor2Forward(MAX_SPEED);
    delay(250);
    stopMotors();
    delay(2000);
    currentState = TURN_LEFT;
    isForward = false;
}

void turnRight() {
    motor1Forward(MAX_SPEED);
    motor2Backward(MAX_SPEED);
    delay(220);
    stopMotors();
    delay(2000);
    currentState = TURN_RIGHT;
    isForward = false;
}

void reverseShort() {
    motor1Backward(MAX_SPEED);
    motor2Backward(MAX_SPEED);
    delay(400);
    stopMotors();
    currentState = REVERSE;
    isForward = false;
}

void uTurn() {
    motor1Forward(MAX_SPEED);
    motor2Backward(MAX_SPEED);
    delay(600);
    stopMotors();
    delay(1000);
    currentState = UTURN;
    isForward = false;
}

int dynamicSpeed(long d) {
    if (d > 50) return MAX_SPEED;
    if (d > 30) return 60;
    if (d > 15) return 45;
    return 35;
}

bool isSuddenChange(long current, long previous) {
    return (previous != -1 && abs(current - previous) > CHANGE_THRESHOLD);
}

// Hàm lùi xe khi bị kẹt
void handleStuck() {
    Serial.println("🛑 Xe bị kẹt quá 10s → lùi lại...");
    reverseShort();
    stuckStartTime = millis();
}
// --- LOOP ---
void loop() {
    long front = getDistance(TrigFront, EchoFront);
    Serial.print("📍 F: "); Serial.println(front);


    long left = getDistance(TrigLeft, EchoLeft);
    long right = getDistance(TrigRight, EchoRight);

    Serial.print("➡️ R: "); Serial.print(right);
    Serial.print(" | ⬅️ L: "); Serial.println(left);

      

    delay(100);
}