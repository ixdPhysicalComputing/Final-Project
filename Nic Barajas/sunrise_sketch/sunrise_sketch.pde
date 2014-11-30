int m;
int r = 0;
int g = 0;
int b = 0;
int t1 = 3000;
int t2 = 8000;
int t3 = 15000;
int s = 100;
int x = 255;
color c;

void setup() {
  size(x,x);
  background(x);
}

void draw() {
  m = millis();
  println("Timer:  " + m);
  if (m > t1) {
    r = (m - t1) / s;
    println("Red:    " + r);
    if (r > x) { r = x; }
  }
  if (m > t3) {
    b = (m - t3) / s;
    println("Blue:  " + b);
    if (b > x) { b = x; }
  }
  if (m > t2) {
    g = (m - t2) / s;
    println("Green: " + g);
    if (g > x) { g = x; }
  }
  c = color(r, g, b);
  background(c);
}
