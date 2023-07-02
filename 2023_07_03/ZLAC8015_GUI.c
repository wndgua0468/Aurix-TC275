import processing.serial.*;
Serial port;
import controlP5.*;
import javax.swing.JOptionPane;

Button closeButton;
Button openSerialButton;
Button stopButton;
Button resetButton;
Button velocityButton;
Button positionButton;

String comportValue = "COM5"; // 초기 comport 값
int baudrateValue = 115200; // 초기 baudrate 값

InputBox comportInput;
InputBox baudrateInput;
InputBox positionInput;

float velocityValue = 0; // 초기 속도 값
float positionValue = 0; // 초기 위치 값

boolean isStopped = false; // 정지 상태 여부

char[] Data_pkg={184,174,'I',0,0,0,0,0};
int Mod=0;
int Velocity=0;
//int Velocity_mouseX=52;
//int Velocity_front_reverse=1;
int Position =0;
int keyPressed_error=0;
String Position_str="";

void setup() {
  size(900, 600);
  String portName ;
  println(Serial.list());
  port = new Serial(this,"COM5",115200);
  port.bufferUntil('\n');
  smooth();

  closeButton = new Button("Close", color(150), width - 180, 110, 110, 70);
  openSerialButton = new Button("Open Serial Port", color(150), 400, 110, 160, 70);
  stopButton = new Button("Emergency \nStop", color(150), width - 180, 320, 110, 70);
  resetButton = new Button("Reset", color(150), width - 180, 440, 110, 70);
  velocityButton = new Button("Change Velocity", color(150), 400, 220, 160, 70);
  positionButton = new Button("Change Position", color(150), 400, 290, 160, 70);

  comportInput = new InputBox("Comport:", 160, 110, 90, 35, comportValue);
  baudrateInput = new InputBox("Baudrate:", 160, 145, 90, 35, str(baudrateValue));
  positionInput = new InputBox("Position:", 160, 275, 90, 35, str(positionValue));
}

void motor_stop(){
  if(resetButton.isMouseOver()){
  Data_pkg[3]=5;
  Data_pkg[4]=0;
  Data_pkg[5]=0;
  Data_pkg[6]=0;
  Data_pkg[7]=0;

    for(int i=0;i<8;i++){
      port.write(Data_pkg[i]);
    }
    delay(10);
  }
}
void send_Velocity(){
  if(Velocity> 0){
    Data_pkg[3]=1;
  }
  else if(Velocity < 0){
    Data_pkg[3]=2;
  }
  Data_pkg[4]=(char)(Velocity>>8);
  Data_pkg[5]=(char)(Velocity%256);
  Data_pkg[6]=0;
  Data_pkg[7]=0;
  for(int i=0;i<8;i++){
    port.write(Data_pkg[i]);
  }
  delay(10);
}
void send_Position(){
  if(Position>=0){
    Data_pkg[3]=3;
    Data_pkg[4]=(char)(Position>>8);
    Data_pkg[5]=(char)(Position%256);
  }
  else{
    Data_pkg[3]=4;
    Data_pkg[4]=(char)((Position*-1)>>8);
    Data_pkg[5]=(char)((Position*-1)%256);
  }
  Data_pkg[6]=0;
  Data_pkg[7]=0;
  for(int i=0;i<8;i++){
    port.write(Data_pkg[i]);
  }
  delay(10);
}


void draw() {
  background(100);
  Velocity = round(velocityValue);
  Position = round(positionValue);
  closeButton.Draw();
  openSerialButton.Draw();
  stopButton.Draw();
  resetButton.Draw();
  velocityButton.Draw();
  positionButton.Draw();

  comportInput.Draw();
  baudrateInput.Draw();
  //positionInput.Draw();
   motor_stop();
   send_Velocity();
   send_Position();

  if (!isStopped) {
    updateValues(); // 값 업데이트
  }

  displayValues();
}

void mousePressed() {
  if (closeButton.isMouseOver()) {
    exit(); // Close the application if the close button is clicked
  } else if (openSerialButton.isMouseOver()) {
    // Open serial port: Add the necessary code to open the serial port here
    comportValue = comportInput.getInputValue(); // Update the comport value
    baudrateValue = int(baudrateInput.getInputValue()); // Update the baudrate value
    println("Opening serial port...");
    println("Comport:", comportValue);
    println("Baudrate:", baudrateValue);
  } else if (stopButton.isMouseOver()) {
    isStopped = true; // Stop the program if the stop button is clicked
  } else if (resetButton.isMouseOver()) {
    isStopped = false; // Restart the program if the reset button is clicked
    velocityValue = 0; // Reset the velocity value to 0
    positionValue = 0; // Reset the position value to 0
  } else if (velocityButton.isMouseOver()) {
    // Show an input box to enter the new velocity value
    String newVelocityString = JOptionPane.showInputDialog("Enter the new velocity value:");

    // Convert the input to a float
    float newVelocity = 0;
    try {
      newVelocity = Float.parseFloat(newVelocityString);
    } catch (NumberFormatException e) {
      println("Invalid input. Please enter a valid number.");
      return;
    }

    // Update the velocityValue with the new value
    velocityValue = newVelocity;
  } else if (positionButton.isMouseOver()) {
    // Show an input box to enter the new position value
    String newPositionString = JOptionPane.showInputDialog("Enter the new position value:");

    // Convert the input to a float
    float newPosition = 0;
    try {
      newPosition = Float.parseFloat(newPositionString);
    } catch (NumberFormatException e) {
      println("Invalid input. Please enter a valid number.");
      return;
    }

    // Update the positionValue with the new value
    positionValue = newPosition;
  }
}


// Button 클래스
class Button {
  String label;
  color xcolor;
  float x, y, w, h;

  Button(String labelB, color x_color, float xpos, float ypos, float widthB, float heightB) {
    label = labelB;
    xcolor = x_color;
    x = xpos;
    y = ypos;
    w = widthB;
    h = heightB;
  }

  void Draw() {
    fill(xcolor);
    stroke(141);
    rect(x, y, w, h, 10);

    textAlign(CENTER, CENTER);
    fill(256, 256, 256);
    textSize(20);
    text(label, x + (w / 2), y + (h / 2));
  }

  boolean isMouseOver() {
    return mouseX > x && mouseX < x + w && mouseY > y && mouseY < y + h;
  }
}

// InputBox 클래스
class InputBox {
  String label;
  float x, y, w, h;
  String inputValue;

  InputBox(String labelB, float xpos, float ypos, float widthB, float heightB, String initialValue) {
    label = labelB;
    x = xpos;
    y = ypos;
    w = widthB;
    h = heightB;
    inputValue = initialValue;
  }

  void Draw() {
    textAlign(LEFT, CENTER);
    textSize(14);

    // 입력창 표시 영역
    fill(200);
    rect(x, y, w, h);

    // 레이블 표시
    fill(0);
    text(label, x, y + h / 2);

    // 입력값 표시
    fill(0);
    text(inputValue, x + w + 10, y + h / 2);
  }

  String getInputValue() {
    return inputValue;
  }
}

void displayValues() {
  // ...

  // 속도 표시 영역
  fill(200);
  rect(160, 220, 200, 60);
  if (!isStopped) {
    fill(0);
    text("Velocity: " + nf(velocityValue, 0, 1) + "rpm", 170, 240);
  }

  // 위치 표시 영역
  fill(200);
  rect(160, 300, 200, 60);
  if (!isStopped) {
    fill(0);
    text("Position: " + nf(positionValue, 0, 1), 170, 320);
  }
}

void updateValues() {
  // velocityValue와 positionValue를 업데이트하고 사용하는 코드를 여기에 작성합니다.
}
