/* ZJW simple C++ code to write out a PPM file representing an ellipse(s) */

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include "ppmR.h"
#include "shape.h"
#include "color.h"
#include "rect.h"
#include "ellipse.h"
#include "polygon.h"
#include "util.h"

using namespace std;


/*write out PPM data, using the defined implicit equation 
  interior points write a differnt color then exterior points */
void writeOut(ostream& out, ppmR& theWriter, 
				vector<shared_ptr<shape>> theShapes) {

	float res;
	color inC;
	color drawC;
	color background(12, 34, 56);
	bool inTrue = false;
	double curDepth = -1.0;

	//for every point in the 2D space
	for (int y=0; y < theWriter.height; y++) {
		for (int x =0; x < theWriter.width; x++) {

			inTrue = false;
			curDepth = -1;
			//iterate through all possible equations
			for (auto s : theShapes) {
				if (s->eval(x, y) && s->getDepth() > curDepth){
					inC = s->getInC();
					inTrue = true;
					curDepth = s->getDepth();
				}
			}

			if (inTrue) {			
				theWriter.writePixel(out, x, y, inC);
			}
			else
				theWriter.writePixel(out, x, y, background);
		}
		theWriter.writeNewLine(out);
	}
}

/* make slightly random triangle takes offfSet to help spread */
void createTriangle(vector<shared_ptr<shape>>& thePolygons, vec2 offSet) {

	//create a vector of vertices for the triangle 
	//vertices specified counter clockwise!
	vector<vec2> triVerts;
	triVerts.push_back(vec2(offSet.x() + nicerRand(-10, 10), offSet.y()+50+nicerRand(-10, 20)));
	triVerts.push_back(vec2(offSet.x() + 50+nicerRand(-10, 10), offSet.y()+10+nicerRand(-20, 10)));
	triVerts.push_back(vec2(offSet.x() + 100+nicerRand(-10, 10), offSet.y()+50+nicerRand(-10, 20)));

	thePolygons.push_back(make_shared<Polygon>(triVerts, nicerRand(4,10), color(nicerRand(0, 25), nicerRand(0, 55), nicerRand(0, 255) ) ) );

}

/*read command line arguments and write out new ascii file of given size */
int main(int argc, char *argv[]) {

	ofstream outFile;
	int sizeX, sizeY;

	string outFilename;
	if (argc < 4) {
		cerr << "Error format: a.out sizeX sizeY outfileName" << endl;
		exit(0);
	} 

	sizeX = stoi(argv[1]);
	sizeY = stoi(argv[2]);
	ppmR theWriter(sizeX, sizeY);

	// layer values larger is closer - ie on top
	vector<shared_ptr<shape>> theShapes;
	color ellipseColor = color(61, 101, 110);
	theShapes.push_back(make_shared<ellipse>(50, 100, 11*6, 11*5, 11, ellipseColor));

	theShapes.push_back(make_shared<ellipse>(150, 200, 11*6, 11*5, 11, ellipseColor));	

	theShapes.push_back(make_shared<Rect>(vec2(200, 200), 60, 60, color(120), 14));

	//make a nice matrix of triangles (rows of blue mountains)
	for (int x=0; x < 4; x++) {
		for (int y=0; y < 4; y++) {
			vector<vec2> triVerts;
			triVerts.push_back(vec2(x*(sizeX/4.0)+ nicerRand(-10, 10), y*(sizeY/4.0)+50+nicerRand(-10, 20)));
			triVerts.push_back(vec2(x*(sizeX/4.0)+ 50+nicerRand(-10, 10), y*(sizeY/4.0)+10+nicerRand(-20, 10)));
			triVerts.push_back(vec2(x*(sizeX/4.0) + 100+nicerRand(-10, 10), y*(sizeY/4.0)+50+nicerRand(-10, 20)));

			theShapes.push_back(make_shared<Polygon>(triVerts, nicerRand(4,10), color(nicerRand(0, 25), nicerRand(0, 55), nicerRand(0, 255) ) ) );

		}
	}
	theShapes.push_back(make_shared<ellipse>(50, 100, 11*6, 11*5, 11, ellipseColor));

	color orange = color(161, 101, 90);
	color magenta = color(255, 0, 255);
	color blue = color(0, 0, 255);
	vector<vec2> theVelocities;
	//set all their colors and create velocities
	for (auto s: theShapes) {
		//TODO set this up per specs:
		s->setColor(orange);
		theVelocities.push_back(vec2(nicerRand(-4, 4), nicerRand(-4, 4)));
	}
	//loop through all the animations - TODO change to 60
	for (int i=0; i < 4; i++) {
		//code to write the files
		outFilename.append(argv[3]);
		if (i < 10)
		  	outFilename.append(to_string(0));
		outFilename.append(to_string(i));
		outFilename.append(".ppm");
		outFile.open(outFilename);

		if (outFile) {
		  	//update the shapes - kind of wacky
		  	int i=0;
			for (auto s: theShapes) {
				//TODO uncomment when ready
				//s->translate(theVelocities.at(i));
				i++;
			}
			cout << "writing an image of size: " << sizeX << " " << sizeY << " to: " << outFilename << endl;
			theWriter.writeHeader(outFile);
			writeOut(outFile, theWriter, theShapes);
			//clean up to open next file
			outFile.close();
			outFilename.erase();
		} else {
			cout << "Error cannot open outfile: " << outFilename << endl;
			exit(0);
		}
	}//end animation loop

}
