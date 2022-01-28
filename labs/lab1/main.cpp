#include <iostream>
#include "bitmap_image.hpp"

struct Point {
    int x;
    int y;
    int z;
    float r; //Red
    float g; //Blue
    float b; //Green
};

std::string * tokenize(std::string s) {
    std::string tokens [6];
    std::string return_message;
    std::string delimiter;

    // comma
    delimiter = ",";
    int start = 0;
    int pos = 0;
    int index = 0;
    std::string token;

    while ((pos = s.find(delimiter)) != std::string::npos) {
//        tokens[index++] = s.substr(0, pos);
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
    }

    std::cout << s << std::endl;
    // colon

    return tokens;
}

//Point create_point(std::string) {
//    return Point {
//
//    };
//}

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

    Point points [3];

    std::cout << "Enter 3 points (enter a point as x,y:r,g,b): \n";
    // Part 1
    for (int i = 0; i < 1; i++) {
        std::string data;
        std::cin >> data;
        tokenize(data);
//        points[i] = create_point(tokenize(data, ","));
    }

    // create an image 640 pixels wide by 480 pixels tall
    bitmap_image image(640, 480);

    /*
      Part 1:
          Calculate the bounding box of the 3 provided points and loop
          over each pixel in that box and set it to white using:

          rgb_t color = make_color(255, 255, 255);
          image.set_pixel(x,y,color);

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

    image.save_image("triangle.bmp");
    std::cout << "Success" << std::endl;
}
