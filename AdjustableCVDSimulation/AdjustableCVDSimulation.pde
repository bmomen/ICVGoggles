// This is based on the tutorial at:
// http://www.inf.ufrgs.br/~oliveira/pubs_files/CVD_Simulation/CVD_Simulation.html
// The tutorial is based on the paper: A Physiologically-based Model for Simulation of Color Vision Deficiency
// by Gustavo M. Machado, Manuel M. Oliveira & Leandro A. F. Fernandes
// the matrices of data at the bottom of that website are what is at the bottom of this program

// use the up and down arrow keys to increase or decrease the severity of hte simulation provided
// use the 'p', 'd', and 't' keys to specify 'protan', 'deutan', or 'tritan' simulation respectively

import processing.video.*;
import javax.swing.*;

Capture cam;
int type = 0;                   // default to protan simulation
int severity = 0;               // default to no CVD at all (severity = 0)
String typeOutput = "Protan ";  // should agree with 'type', where 0=protan, 1=deutan, 2=tritan

void setup()
{
  size(500, 500);
  colorMode(RGB, 1.0);
  frame.setResizable(true);

  // If no device is specified, will just use the default.
// cam = new Capture(this, 640, 480);
// cam.start();

  // To use another device (e.g., if the default device causes an error),  
  // list all available capture devices to a dialog box to let the user pick one.
  String[] devices = Capture.list();
  String selectedDevice = (String) JOptionPane.showInputDialog(null, "Choose Camera", "Input", JOptionPane.INFORMATION_MESSAGE, null, devices, devices[0]);

  // Create the viewport for the selected camera
  cam = new Capture(this, selectedDevice);
  cam.start();
}

void draw()
{
  if (cam.available() == true)
  {
    cam.read();
    cam.loadPixels();
    frame.setSize(cam.width, cam.height);  // a little overkill doing this everytime, but seems okay
    for (int i=0; i<(cam.width*cam.height); i=i+1)
    {
      float r = red(cam.pixels[i]);    // should be the red value in range [0-1]
      float g = green(cam.pixels[i]);  // should be the green value in range [0-1]
      float b = blue(cam.pixels[i]);   // should be the blue value in range [0-1]
      float newR = (r * mult[type][severity][0][0]) + (g * mult[type][severity][0][1]) + (b * mult[type][severity][0][2]);
      float newG = (r * mult[type][severity][1][0]) + (g * mult[type][severity][1][1]) + (b * mult[type][severity][1][2]);
      float newB = (r * mult[type][severity][2][0]) + (g * mult[type][severity][2][1]) + (b * mult[type][severity][2][2]);
      cam.pixels[i] = color(newR, newG, newB);
    }
    cam.updatePixels();
    image(cam, 0, 0);

    // insert the text label showing what is currently on-screen
    float brightness = (0.2126*red(cam.pixels[0])) + (0.7152*green(cam.pixels[0])) + (0.0722*blue(cam.pixels[0]));  // approximate brightness of top left corner pixel
    if (brightness > 0.5) { fill(0); }    // black text for light images
    else { fill(1.0); }                   // white text for dark images
    text((typeOutput + (severity/10.0)), 20, 20);
  }
}

// interact -> allow user to select form of simulation
void keyPressed()
{
  if (key == CODED && keyCode == UP) {
    severity = Math.min(10, (severity + 1));
  }
  else if (key == CODED && keyCode == DOWN) {
    severity = Math.max(0, (severity - 1));
  }
  else if (key == 'p' || key == 'P') {
    type = 0;  // protan
    typeOutput = "Protan ";
  }
  else if (key == 'd' || key == 'D') {
    type = 1;  // deutan
    typeOutput = "Deutan ";
  }
  else if (key == 't' || key == 'T') {
    type = 2;  // tritan
    typeOutput = "Tritan ";
  }
}

// the matrix multiplication data provided from the URL listed at the top of this program
// 4D array:
//    D1 is for 'type', where '0' is 'protan', '1' is 'deutan', and '2' is 'tritan';
//    D2 is for 'severity', ranging from 0-10, where '0' represents no CVD, and '10' represents maximum CVD (essentially dichromatism)
//    D3 specifies the row of the multiplication matrix [0-2]
//    D4 specifies the column of the multiplication matrix [0-2]
float mult[][][][] = {
  // protan simulation
{
{ { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } },
{ { 0.856167, 0.182038, -0.038205 }, { 0.029342, 0.955115, 0.015544 }, { -0.00288, -0.001563, 1.004443 } },
{ { 0.734766, 0.334872, -0.069637 }, { 0.05184, 0.919198, 0.028963 }, { -0.004928, -0.004209, 1.009137 } },
{ { 0.630323, 0.465641, -0.095964 }, { 0.069181, 0.890046, 0.040773 }, { -0.006308, -0.007724, 1.014032 } },
{ { 0.539009, 0.579343, -0.118352 }, { 0.082546, 0.866121, 0.051332 }, { -0.007136, -0.011959, 1.019095 } },
{ { 0.458064, 0.679578, -0.137642 }, { 0.092785, 0.846313, 0.060902 }, { -0.007494, -0.016807, 1.024301 } },
{ { 0.38545, 0.769005, -0.154455 }, { 0.100526, 0.829802, 0.069673 }, { -0.007442, -0.02219, 1.029632 } },
{ { 0.319627, 0.849633, -0.169261 }, { 0.106241, 0.815969, 0.07779 }, { -0.007025, -0.028051, 1.035076 } },
{ { 0.259411, 0.923008, -0.18242 }, { 0.110296, 0.80434, 0.085364 }, { -0.006276, -0.034346, 1.040622 } },
{ { 0.203876, 0.990338, -0.194214 }, { 0.112975, 0.794542, 0.092483 }, { -0.005222, -0.041043, 1.046265 } },
{ { 0.152286, 1.052583, -0.204868 }, { 0.114503, 0.786281, 0.099216 }, { -0.003882, -0.048116, 1.051998 } }
},

// deutan simulation
{
{ { 1.0, 0.0, 0.0}, { 0.0, 1.0, 0.0}, { 0.0, 0.0, 1.0} },
{ { 0.866435, 0.177704, -0.044139}, { 0.049567, 0.939063, 0.01137}, { -0.003453, 0.007233, 0.99622} },
{ { 0.760729, 0.319078, -0.079807}, { 0.090568, 0.889315, 0.020117}, { -0.006027, 0.013325, 0.992702} },
{ { 0.675425, 0.43385, -0.109275}, { 0.125303, 0.847755, 0.026942}, { -0.00795, 0.018572, 0.989378} },
{ { 0.605511, 0.52856, -0.134071}, { 0.155318, 0.812366, 0.032316}, { -0.009376, 0.023176, 0.9862} },
{ { 0.547494, 0.607765, -0.155259}, { 0.181692, 0.781742, 0.036566}, { -0.01041, 0.027275, 0.983136} },
{ { 0.498864, 0.674741, -0.173604}, { 0.205199, 0.754872, 0.039929}, { -0.011131, 0.030969, 0.980162} },
{ { 0.457771, 0.731899, -0.18967}, { 0.226409, 0.731012, 0.042579}, { -0.011595, 0.034333, 0.977261} },
{ { 0.422823, 0.781057, -0.203881}, { 0.245752, 0.709602, 0.044646}, { -0.011843, 0.037423, 0.974421} },
{ { 0.392952, 0.82361, -0.216562}, { 0.263559, 0.69021, 0.046232}, { -0.01191, 0.040281, 0.97163} },
{ { 0.367322, 0.860646, -0.227968}, { 0.280085, 0.672501, 0.047413}, { -0.01182, 0.04294, 0.968881} }
},

// tritan simulation
{
{ { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } },
{ { 0.92667, 0.092514, -0.019184 }, { 0.021191, 0.964503, 0.014306 }, { 0.008437, 0.054813, 0.93675 } },
{ { 0.89572, 0.13333, -0.02905 }, { 0.029997, 0.9454, 0.024603 }, { 0.013027, 0.104707, 0.882266 } },
{ { 0.905871, 0.127791, -0.033662 }, { 0.026856, 0.941251, 0.031893 }, { 0.01341, 0.148296, 0.838294 } },
{ { 0.948035, 0.08949, -0.037526 }, { 0.014364, 0.946792, 0.038844 }, { 0.010853, 0.193991, 0.795156 } },
{ { 1.017277, 0.027029, -0.044306 }, { -0.006113, 0.958479, 0.047634 }, { 0.006379, 0.248708, 0.744913 } },
{ { 1.104996, -0.046633, -0.058363 }, { -0.032137, 0.971635, 0.060503 }, { 0.001336, 0.317922, 0.680742 } },
{ { 1.193214, -0.109812, -0.083402 }, { -0.058496, 0.97941, 0.079086 }, { -0.002346, 0.403492, 0.598854 } },
{ { 1.257728, -0.139648, -0.118081 }, { -0.078003, 0.975409, 0.102594 }, { -0.003316, 0.501214, 0.502102 } },
{ { 1.278864, -0.125333, -0.153531 }, { -0.084748, 0.957674, 0.127074 }, { -0.000989, 0.601151, 0.399838 } },
{ { 1.255528, -0.076749, -0.178779 }, { -0.078411, 0.930809, 0.147602 }, { 0.004733, 0.691367, 0.3039 } }
}
};

