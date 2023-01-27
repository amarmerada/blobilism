#include <iostream>
#include <vector>
#include "tinygl-cpp.h"
#include "math.h"
using namespace tinygl;
//r , g , b, diameter, x, y, transparency
struct Pen{
    float r;
    float g;
    float b;
    float diameter;
    int xCoord;
    int yCoord;
    float transparency;
};

class MyWindow : public Window {
 public:
  MyWindow(int w, int h) : Window(w, h) {}

  

  




  void setup() override {
    std::cout << "Window size: " << width() << ", " << height() << std::endl;
  }

  virtual void mouseMotion(int x, int y, int dx, int dy) {
    if (mouseIsDown(GLFW_MOUSE_BUTTON_LEFT)) {
      // todo: store a circle with the current color, size, x, y
        pen.xCoord = x;
        pen.yCoord = y;
        myCircles.push_back(pen);
    }
  }
  
  virtual void mouseDown(int button, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        myPallette.push_back(black);
        myPallette.push_back(white);
        myPallette.push_back(red);
        myPallette.push_back(orange);
        myPallette.push_back(yellow);
        myPallette.push_back(green);
        myPallette.push_back(cyan);
        myPallette.push_back(magenta);
        myPallette.push_back(blue);
        myPallette.push_back(purple);
      // todo: check if user clicked a color 
      float mx = mouseX();  // current mouse pos x
      float my = mouseY();  // current mouse pos y
      printf("mousex: %f mousey: %f\n", mx, my);
      float localx = 0;
      float localy = 0;
      float localDist = 100;
      for (int i = 0; i < myPallette.size(); i++) {
          localx = myPallette[i].xCoord;
          localy = myPallette[i].yCoord;
          //printf("xCoord: %f  yCoord: %f\n", localx, localy);
          double xdist = (double)mx - (double)localx;
          double ydist = (double)my - (double)localy;
          double squareX = pow(xdist, 2);
          double squareY = pow(ydist, 2);
          double sum = squareX + squareY;
          double sqrRt = sqrt(sum);
          localDist = (float)sqrRt;
          printf("DISTANCE: %f\n", localDist);
          if (localDist < 10) {
              printf("ATTEMPTING CHANGE\n");
              pen.r = myPallette[i].r;
              pen.g = myPallette[i].g;
              pen.b = myPallette[i].b;
              break;
          }
      }
    }
  }


  void keyDown(int key, int mods) {
    if (key == GLFW_KEY_UP) {
      // increase size of circle
        if (pen.diameter < 250) {
            pen.diameter += 1;
        }
    } 
      // decrease size of circle 
    else if (key == GLFW_KEY_DOWN) {
        if (pen.diameter > 0) {
            pen.diameter -= 1;
        }
    }
    else if (key == GLFW_KEY_LEFT) {
      // decrease alpha
        printf("BEFORE: pen R: %f  pen G: %f pen B: %f\n", pen.r, pen.g, pen.b);
        if (pen.transparency >= 0.1) {
            pen.transparency -= 0.1;
        }
        float currentSatR = pen.r * pen.transparency;
        float currentSatG = pen.g * pen.transparency;
        float currentSatB = pen.b * pen.transparency;
        float currentBGR = 0.95f * (1 - pen.transparency);
        float currentBGG = 0.95f * (1 - pen.transparency);
        float currentBGB = 0.95f * (1 - pen.transparency);
        pen.r = currentSatR + currentBGR;
        pen.g = currentSatG + currentBGG;
        pen.b = currentSatB + currentBGB;
    }
    else if (key == GLFW_KEY_RIGHT) {
      // increase alpha
        printf("BEFORE: pen R: %f  pen G: %f pen B: %f\n", pen.r, pen.g, pen.b);
        if (pen.transparency < 0.9) {
            pen.transparency += 0.1;
        }
        //alpha * c_foreground + (1-alpha c_background)
        float currentSatR = pen.r * pen.transparency;
        float currentSatG = pen.g * pen.transparency;
        float currentSatB = pen.b * pen.transparency;
        float currentBGR = 0.95f * (1 - pen.transparency);
        float currentBGG = 0.95f * (1 - pen.transparency);
        float currentBGB = 0.95f * (1 - pen.transparency);
        pen.r = currentSatR + currentBGR;
        pen.g = currentSatG + currentBGG;
        pen.b = currentSatB + currentBGB;
    }
    else if (key == GLFW_KEY_C) {
      // clear vector of circles
        myCircles.clear();
    }
  }

  void draw() override {
    background(0.95f, 0.95f, 0.95f); // parameters: r, g, b

    //color(1.0f, 0.5f, 0.5f);
    //circle(width() * 0.5f, height() * 0.5, 300);

    // todo : draw pallet
    color(0.1f, 0.1f, 0.1f);
    square(width()/2.0f, 35, width(), 70);
    for (int i = 0; i < myCircles.size();  i++) {
        color(myCircles[i].r, myCircles[i].g, myCircles[i].b);
        circle(myCircles[i].xCoord, myCircles[i].yCoord, myCircles[i].diameter);
    }
    color(pen.r, pen.g, pen.b);
    circle(pen.xCoord, pen.yCoord, pen.diameter);   

    color(black.r, black.g, black.b); //black
    circle(black.xCoord, black.yCoord, black.diameter);
    color(white.r, white.g, white.b); //white
    circle(white.xCoord, white.yCoord, white.diameter);
    color(red.r, red.g, red.b); //red
    circle(red.xCoord, red.yCoord, red.diameter);
    color(orange.r, orange.g, orange.b);//orange
    circle(orange.xCoord, orange.yCoord, orange.diameter);
    color(yellow.r, yellow.g, yellow.b); //yellow
    circle(yellow.xCoord, yellow.yCoord, yellow.diameter);
    color(green.r, green.g, green.b); //green
    circle(green.xCoord, green.yCoord, green.diameter);
    color(cyan.r, cyan.g, cyan.b);  //cyan
    circle(cyan.xCoord, cyan.yCoord, cyan.diameter);
    color(blue.r, blue.g, blue.b); //blue
    circle(blue.xCoord, blue.yCoord, blue.diameter);
    color(purple.r, purple.g, purple.b); // purple???
    circle(purple.xCoord, purple.yCoord, purple.diameter);
    color(magenta.r, magenta.g, magenta.b); //magenta
    circle(magenta.xCoord, magenta.yCoord, magenta.diameter);
  }
 private:

  // todo: create member variables for 
  // current circle size
  float penSize = 5.0f;
  // current transparency
  float alpha = 1.0;
  // current color
  float R;
  float G;
  float B;
  // list of circles to draw each frame
  struct Pen pen = Pen{ R, G, B, penSize, 300, 300, alpha };
  std::vector<Pen> myCircles;

  //color pallet
  std::vector<Pen> myPallette;
  struct Pen black = Pen{ 0.0, 0.0, 0.0, 20, 490, 10, 1.0f};
  struct Pen white = Pen{1, 1, 1, 20, 470, 10, 1.0f};
  struct Pen red = Pen{1, 0 , 0, 20, 450, 10, 1.0f};
  struct Pen orange = Pen{1, 0.6, 0, 20, 430, 10, 1.0f};
  struct Pen yellow = Pen{1, 1, 0, 20, 410, 10, 1.0f};
  struct Pen green = Pen{0, 1, 0, 20, 390, 10, 1.0f};
  struct Pen cyan = Pen{0, 1, 1, 20, 370, 10, 1.0f};
  struct Pen blue = Pen{0, 0, 1, 20, 350, 10, 1.0f};
  struct Pen purple = Pen{0.65f, 0.2f, 1.0f, 20, 330, 10, 1.0f};
  struct Pen magenta = Pen{1.0f, 0.0f, 1.0f, 20, 310, 10, 1.0f};
  
  // color pallet
};

int main() {
  MyWindow window(500, 500);
  window.run();
}
