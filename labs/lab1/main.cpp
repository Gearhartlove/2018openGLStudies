#include <iostream>
#include "bitmap_image.hpp"


// global variables > bad practice but temporary
float gAlpha;
float gBeta;
float gGamma;

struct Point {
    int x;
    int y;
    int r; //Red
    int g; //Blue
    int b; //Green

    Point(int X, int Y, int R, int G, int B) : x(X), y(Y), r(R), g(G), b(B)
    {
    }
};

std::vector<std::string> tokenize(std::string s, std::string delimiter) {
    // token collection
    std::vector<std::string> tokens;
    // parsing data
    int start = 0;
    int pos = 0;
    int index = 0;
    std::string token;

    // replace the ":" with "," to parse
    std::replace(s.begin(), s.end(), ':', ',');

    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
}

/// Instantiate a point and return it; input are tokens created after parsing
Point create_point(std::vector<std::string> tokens) {
    return {std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]),
                 std::stoi(tokens[3]), std::stoi(tokens[4])};
}

/// Check if x and y are in the triangle using barycentric coordinates
bool in_triangle(int x,int y, std::vector<Point> points) {
    Point& A = points[0];
    Point& B = points[1];
    Point& C = points[2];

    float alpha;
    float beta;
    float gamma;

    // calculate beta , gamma
    int matA[1][2] = {{x-A.x,y-A.y}};
    int matB[2][2] = {{B.x-A.x, C.x-A.x},{B.y-A.y, C.y-A.y}};
    float matBInverse[2][2];

    float matResult[1][2];

    // references to help with calculation
    float a = matB[0][0];
    float b = matB[0][1];
    float c = matB[1][0];
    float d = matB[1][1];
    float inverse_scalar = 1/(a*d-b*c);

    // get inverse of matB
    matBInverse[0][0] = d * inverse_scalar;
    matBInverse[0][1] = -b * inverse_scalar;
    matBInverse[1][0] = -c * inverse_scalar;
    matBInverse[1][1] = a * inverse_scalar;

    // calculate result > perform dot prodcut of matBInverse*matB
    matResult[0][0] = matBInverse[0][0] * matA[0][0] + matBInverse[0][1] * matA[0][1];
    matResult[0][1] = matBInverse[1][0] * matA[0][0] + matBInverse[1][1] * matA[0][1];

    beta = matResult[0][0];
    gamma = matResult[0][1];
    alpha = 1 - beta - gamma;

    if (alpha > 0 && alpha < 1 && beta > 0 && beta < 1 && gamma > 0 && gamma < 1) {
        gAlpha = alpha;
        gBeta = beta;
        gGamma = gamma;
        return true;
    }

    return false;
}

int main(int argc, char** argv) {
    /*
      Prompt user for 3 points separated by whitespace.

      Part 1:
          You'll need to get the x and y coordinate as floating point values
          from the user for 3 points that make up a triangle.


      Part 3:
          You'll need to also request 3 colors from the user each having
          3 floating point values (red, green and blue) that range from 0 to 1.
    */

    std::vector<Point> points;

    // Problem Setup
    std::cout << "Enter 3 points (enter a point as x,y:r,g,b): \n";
    std::string p1 = "50,50:1,0,0";
    std::string p2 = "600,20:0,1,0";
    std::string p3 = "300,400:0,0,1";
    points.push_back(create_point(tokenize(p1, ",")));
    points.push_back(create_point(tokenize(p2, ",")));
    points.push_back(create_point(tokenize(p3, ",")));


    // create an image 640 pixels wide by 480 pixels tall
    bitmap_image image(640, 480);


//      Part 1:
//          Calculate the bounding box of the 3 provided points and loop
//          over each pixel in that box and set it to white using:
//
    //bounding box -> have three points, "calculate" the forth point by . . .
    // then loop over those pixels in that x,y and set there color

    int x_lower_bound = 40;
    int x_upper_bound = 610;

    int y_lower_bound = 15;
    int y_upper_bound = 410;

//    Part 2:
//    Modify your loop from part 1. Using barycentric coordinates,
//    determine if the pixel lies within the triangle defined by
//    the 3 provided points. If it is color it white, otherwise
//    move on to the next pixel.
    for (int y = y_lower_bound; y < y_upper_bound; y++) {
        for (int x = x_lower_bound; x < x_upper_bound; x++) {
//            if (in_triangle(x,y, points)) {
//                rgb_t color = make_colour(gAlpha*255, gBeta*255, gGamma*255);
                rgb_t color = make_colour(255,255,255);
                image.set_pixel(x,y,color);
//            }
        }
    }



    /*
      Part 3:
          For each pixel in the triangle, calculate the color based on
          the calculated barycentric coordinates and the 3 provided
          colors. Your colors should have been entered as floating point
          numbers from 0 to 1. The red, green and blue components range
          from 0 to 255. Be sure to make the conversion.
    */

    image.save_image("triangle_square.bmp");
    std::cout << "Success" << std::endl;
}
