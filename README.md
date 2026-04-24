# Arduino_Contest_MazeSolving
[Được giải khuyến khích]
# 🤖 Maze Solving Robot using Ultrasonic Sensors

Dự án này xây dựng một robot tự hành có khả năng **giải mê cung (maze solving)** sử dụng cảm biến siêu âm và điều khiển động cơ cơ bản. Robot có thể tự phát hiện vật cản và đưa ra quyết định di chuyển phù hợp theo thời gian thực.

---

## 📸 Demo

[![Maze Robot Demo](https://github.com/user-attachments/assets/c4de03b3-d6ac-4a46-8dbb-a374f271d1b8)](https://drive.google.com/file/d/15IDcdu7uDnC81xKNGSTDM813HmJNBLfA/view?usp=drive_link)

<p align="center">▶ Click to watch full demo video</p>

<img width="1536" height="2048" alt="image" src="https://github.com/user-attachments/assets/c4de03b3-d6ac-4a46-8dbb-a374f271d1b8" />

---

## 🎯 Features

* 🚧 Tránh vật cản bằng cảm biến siêu âm (Front, Left, Right)
* 🔄 Tự động điều hướng (rẽ trái / phải / quay đầu)
* ⚡ Điều chỉnh tốc độ theo khoảng cách (Dynamic Speed)
* 🧠 Phát hiện kẹt và tự lùi lại (Stuck Detection)
* ⏱ Timeout khi đi thẳng quá lâu

---

## 🛠 Hardware Components

* Arduino (Uno / Nano / tương đương)
* 3x Cảm biến siêu âm (HC-SR04)
* Driver động cơ (L298N hoặc tương đương)
* 2x Động cơ DC
* Khung xe robot

---

## ⚙️ Pin Configuration

### 📡 Ultrasonic Sensors

| Sensor | Trig | Echo |
| ------ | ---- | ---- |
| Front  | 7    | 8    |
| Right  | 9    | 10   |
| Left   | 12   | 13   |

---

### ⚙️ Motor Driver

| Motor   | IN Pin            |
| ------- | ----------------- |
| Motor 1 | IN1 (5), IN2 (6)  |
| Motor 2 | IN3 (3), IN4 (11) |

---

## 🧠 Control Logic

Robot hoạt động dựa trên **Finite State Machine (FSM)**:

```cpp id="fsm1"
enum RobotState {
  IDLE,
  FORWARD,
  TURN_LEFT,
  TURN_RIGHT,
  REVERSE,
  UTURN
};
```

---

## 🔄 Operational Flow

1. Đọc khoảng cách từ 3 cảm biến:

   * Trước (Front)
   * Trái (Left)
   * Phải (Right)

2. Phân tích môi trường:

   * Nếu phía trước trống → đi thẳng
   * Nếu có vật cản → chọn hướng rẽ
   * Nếu bị kẹt → lùi hoặc quay đầu

3. Điều khiển động cơ tương ứng

---

## ⚡ Key Functions

### 📏 Distance Measurement

```cpp id="dist1"
long getDistance(int trigPin, int echoPin);
```

* Đo khoảng cách bằng HC-SR04
* Timeout để tránh treo hệ thống

---

### 🚗 Movement Control

* `moveForward(speed)`
* `turnLeft()`
* `turnRight()`
* `reverseShort()`
* `uTurn()`
* `stopMotors()`

---

### 🎯 Dynamic Speed

```cpp id="speed1"
int dynamicSpeed(long d);
```

* Điều chỉnh tốc độ theo khoảng cách:

  * Xa → nhanh
  * Gần → chậm

---

### 🛑 Stuck Detection

```cpp id="stuck1"
void handleStuck();
```

* Nếu robot không thay đổi vị trí trong thời gian dài:

  * Tự động lùi lại
  * Reset trạng thái

---

## ⚙️ Configuration

```cpp id="config1"
#define MAX_SPEED 70
#define DIS 7
#define CHANGE_THRESHOLD 20
#define FORWARD_TIMEOUT 5000
```

---

## 📊 Serial Monitor Output

Robot sẽ in thông tin để debug:

```
📍 F: <distance_front>
➡️ R: <distance_right> | ⬅️ L: <distance_left>
```

---

## 🚀 How to Run

1. Upload file `.ino` vào Arduino
2. Kết nối đúng dây theo cấu hình
3. Mở Serial Monitor (9600 baud)
4. Đặt robot vào mê cung và chạy

---

## 📸 Results

<!-- 👉 Thêm ảnh kết quả tại đây -->

<!-- Ví dụ:
![Result](./assets/result.jpg)
-->

---

## ⚠️ Limitations

* Chưa sử dụng thuật toán tối ưu đường đi (DFS/BFS)
* Phụ thuộc nhiều vào độ chính xác cảm biến
* Delay blocking có thể làm giảm phản ứng realtime

---

## 🚀 Future Improvements

* Áp dụng thuật toán:

  * Wall-following
  * Flood fill
* Thay delay bằng non-blocking (millis)
* Thêm encoder để đo quãng đường
* Tích hợp SLAM hoặc camera

---

