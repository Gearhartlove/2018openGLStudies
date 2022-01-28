#include <iostream>
#include "bitmap_image.hpp"

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

// from video: https://www.youtube.com/watch?v=HYAgJN3x4GA
// timestamp : 3 minutes 42 seconds
/// Check if x and y are in the triangle using barycentric coordinates
bool in_triangle(int x,int y, std::vector<Point> points) {
    Point& A = points[0];
    Point& B = points[1];
    Point& C = points[2];

    float w1 = 0;
    float w2 = 0;

    w1 = (A.x * (C.y - A.y) + (y - A.y) * (C.x - A.x) - x * (C.y - A.y)) /
            ((B.y - A.y) * (C.x - A.x) -(B.x - A.x) * (C.y - A.y));
    w2 = (y -A.y - w1 * (B.y - A.y)) /
            (C.y - A.y);

    if (w1 >= 0 && w2 >= 0 && w1 + w2 <= 1) {
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

    rgb_t color = make_colour(255, 255, 255);

    for (int y = y_lower_bound; y < y_upper_bound; y++) {
        for (int x = x_lower_bound; x < x_upper_bound; x++) {
            if (in_triangle(x,y, points)) {
                image.set_pixel(x,y,color);
            }
        }
    }

    float w1;
    float w2;
    // x axis
    // P = A + w1(B-A) + w2(C-A)
    // y axis
    // P = A + w1(B-A) + w2(C-A)
    /*
      Part 2:
          Modify your loop from part 1. Using barycentric coordinates,
          determine if the pixel lies within the triangle defined by
          the 3 provided points. If it is color it white, otherwise
          move on to the next pixel.

      Part 3:
          For each pixel in the triangle, calculate the color based on
          the calculated barycentric coordinates and the 3 provided
          colors. Your colors should have been entered as floating point
          numbers from 0 to 1. The red, green and blue components range
          from 0 to 255. Be sure to make the conversion.
    */

    image.save_image("triangle2.bmp");
    std::cout << "Success" << std::endl;
}
