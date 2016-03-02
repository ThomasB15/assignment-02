/* ----------------------------------------------------------------------------
 * Copyright &copy; 2016 Thomas Brenner, Adam Djabra, Andrew Nomura <tommyb@csu.fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * Tying everything together.
 *
 * Notes:
 * - We also include our test functions here, since there aren't that many.
 */
#include "buffer.h"
#include "constants.h"
#include "neighborhood.h"
#include "shape.h"

// ----------------------------------------------------------------------------
// test functions

/**
 * Test the `Buffer` object by creating one, drawing a few things on it, and
 * then rendering it to the screen.
 */
void test_buffer() {
    Buffer b(TERM_SIZE_X, TERM_SIZE_Y);

    // draw ellipse
    for (int y=0; y < b.size_y; y++)
        for (int x=0; x < b.size_x; x++)
            if ( (x-40)*(x-40) + (y-10)*(y-10) == 50)
                b.set(x, y, '*');

    // draw boarder
    for (int y=0; y < b.size_y; y++) {
        b.set(0, y, '|');
        b.set(b.size_x-1, y, '|');
    }
    for (int x=0; x < b.size_x; x++) {
        b.set(x, 0, '-');
        b.set(x, b.size_y-1, '-');
    }

    // render to screen
    b.draw();
}

/**
 * Test the `Shape` object by creating one of each type (besides "empty"), and
 * tiling them on a buffer.
 */
void test_shape() {
    Buffer b(TERM_SIZE_X, TERM_SIZE_Y);

    Shape triangle("triangle");
    Shape square("square");

    // draw shapes
    for (int y = 0; y <= b.size_y - Shape::size_y; y += Shape::size_y) {
        for (int x = 0; x <= b.size_x - Shape::size_x*2; x += Shape::size_x*2) {
            triangle.drawToBuffer(b, x + Shape::size_x*((y+0)%2), y);
            square.drawToBuffer(b, x + Shape::size_x*((y+1)%2), y);
        }
    }

    // render to screen
    b.draw();
}

// ----------------------------------------------------------------------------

/**
 * Notes:
 * - Comment out the parts you aren't currently using.
 */
int main() {
     //test_buffer();

    // ------------------------------------------------------------------------

     //test_shape();

    // ------------------------------------------------------------------------

    //animate  neighborhood
    unsigned int size_x = TERM_SIZE_X/Shape::size_x;
    unsigned int size_y = TERM_SIZE_Y/Shape::size_y;
    Neighborhood(size_x, size_y).animate(1000);

    // ------------------------------------------------------------------------

    return 0;  // success
}



//--------------------------------------------------------------------------------------------------------------------------------------------
//buffer.cpp

/* ----------------------------------------------------------------------------
* Copyright &copy; 2016 Thomas Brenner, Adam Djabra, Andrew Nomura <tommyb@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

/**
* Implements `buffer.h`.
*/

// TODO: `#include`s for system headers, if necessary
#include <iostream>
#include <cstdlib>
#include <string>
#include "buffer.h"
using std::cout;
using std::endl;
// TODO: `#include`s for other local headers, if necessary

// ----------------------------------------------------------------------------

// TODO: implementations for all functions in `class Buffer`
Buffer::Buffer(unsigned int size_x, unsigned int size_y)
	:size_x(size_x), size_y(size_y)
{
	data_ = new char[size_x * size_y];
	//for (unsigned int i = 0; i < size_x * size_y; i++)
		//data_[i] = ' ';
	clear();
}
/**
* The constructor.
*
* Must initialize `size_x` and `size_y`, and allocate memory for (and
* initialize) `data_`.
*
* Notes:
* - Since `size_x` and `size_y` are constant, they must be initialized
*   in the initialization list, rather than set in the constructor
*   body.
* - You may assume that the dynamic memory allocation succeeds.
*/

Buffer::~Buffer()
{
	delete[] data_;
}
/**
* The destructor.
*
* Must free the memory that the constructor allocated to `data_`.
*/


char Buffer::get(unsigned int x, unsigned int y) const {



	if (x >= size_x || y >= size_y)
	{
		cout << "ERROR: Buffer::get : index out of bounds\n";

		exit(1);
	}


	return data_[y * size_x + x];
}
/**
* Return the character at `data_[ y * size_x + x ]`.
*
* If `x` or `y` is out of bounds, should write
* ```
* "ERROR: `Buffer::get`: index out of bounds\n"
* ```
* to `cerr` and `exit(1)`.
*/

void Buffer::set(unsigned int x, unsigned int y, char c) {

	data_[y * size_x + x] = c;

	if (x >= size_x || y >= size_y)
	{
		cout << "ERROR: Buffer::get : index out of bounds\n";

		exit(1);
	}


}
/**
* Set the character at `data_[ y * size_x + x ]` to `c`.
*
* If `x` or `y` is out of bounds, should write
* ```
* "ERROR: `Buffer::set`: index out of bounds\n"
* ```
* to `cerr` and `exit(1)`.
*/

void Buffer::set(unsigned int pos_x, unsigned int pos_y, std::string s) {
	for (int i = 0, x = pos_x, y = pos_y; i < s.length(); i++) {
		if (s[i] == '\n') {
			y++;
			x = pos_x;
		}
		else {
			set(x++, y, s[i]);
		}
		
	}
	
}
/**
* Overlay `s` onto `data_`.
*
* For example, if this buffer is representing an array that looks like
* ```
* *******
* *******
* *******
* *******
* *******
* ```
* and we call `set(1, 2, "hello\nworld")`, the buffer's contents
* should now be
* ```
* *******
* *******
* *hello*
* *world*
* *******
* ```
*
* Notes:
* - This function may call the other `set` (which takes a `char` as
*   its last argument), if you like.  In that case, you may leave the
*   index error checking to the other `set`.  Otherwise, you should
*   have checks in this function to make sure you're not putting
*   characters where they don't belong.
* - This function will be useful when implementing the `Shape` class.
* - If you can't think of a way to do this, see
*   `hint--implementation-of-Buffer-set.md`.
*/


void Buffer::draw() const {

	for (unsigned int y = 0; y < size_y; y++) {
		for (unsigned int x = 0; x < size_x; x++) {
			cout << get(x,y);
		}
		cout << endl;
	}
 
}
/**
* Output the contents of the buffer to `cout`.
*/


void Buffer::clear() {
	for (unsigned int i = 0; i < size_x * size_y; i++)
		data_[i] = ' ';
	/*for (int y = 0; y < size_y; y++)
		for (int x = 0; x < size_x; x++)
			set(x, y, ' ');*/

}
/**
* Set each element `data_` to ' '.
*/


//-------------------------------------------------------------------------------------------------------------------------------
//shape.cpp

/* ----------------------------------------------------------------------------
* Copyright &copy; 2016 Thomas Brenner, Adam Djabra, Andrew Nomura <tommyb@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

/**
* Implements `shape.h`.
*/

// TODO: `#i#include <iostream>
#include <iostream>
#include <string>
#include "buffer.h"
#include "shape.h"
#include "constants.h"



using std::cin;
using std::cout;
using std::endl;
using std::string;


// TODO: `#include`s for other local headers, if necessary

// ----------------------------------------------------------------------------

// TODO: implementations for all functions in `class Buffer`



Shape::Shape(const string & type) :type_(type) {
	setType(type);


}
/**
* The constructor.
*
* Must initialize `type_`, and `type_art_`.
*
* Notes:
* - I suggest calling `setType` in the body of the constructor, to
*   avoid duplicating code.
*/

Shape::~Shape() = default;
/**
* The destructor.
*
* Since there's no dynamically allocated memory to `delete`, this may
* be left out, or it may be implemented with
* ```
* Shape::~Shape() = default;
* ```
* (valid since C++ 11).
*/


string Shape::getType() {
	return type_;
}
/**
* Return `type_`.
*/

void Shape::setType(const string & type) {
	if (type_ == "empty")
		type_art_ = "     \n"
		            "     \n"
					"     \n";
	else if (type_ == "triangle")
		type_art_ = "  ,  \n"
					" / \\\n"
					"/___\\\n";
	else if (type_ == "square")
		type_art_ = ".---.\n"
					"|   |\n"
					"'---'\n";
	else {
		cout << "ERROR: 'Shape::setType': invalid type\n";
	}

}
/**
* Set `type_` to `type`, and set `type_art_` to the appropriate value.
*
* If the passed `type` is not valid, write
* ```
* "ERROR: `Shape::setType`: invalid type\n"
* ```
* to `cerr` and `exit(1)`.
*/


void Shape::drawToBuffer(Buffer & b, unsigned int x, unsigned int y) const {

	b.set(x, y, type_art_);
}
/**
* Draw `type_art_` onto the `Buffer` at position `x, y`.
*
* Notes:
* - This (primarily) is what
*   ```
*   void Buffer::set(unsigned int, unsigned int, std::string);
*   ```
*   is for.
*/


bool Shape::isHappy(const Neighborhood & n,
	unsigned int pos_x,
	unsigned int pos_y) const {

	if (n.get(pos_x, pos_y).getType() == "empty")
		return true;

	unsigned int x_min = (pos_x == 0) ? pos_x : pos_x - 1;
	unsigned int y_min = (pos_y == 0) ? pos_y : pos_y - 1;

	unsigned int x_max = (pos_x == n.size_x - 1) ? pos_x : pos_x + 1;
	unsigned int y_max = (pos_y == n.size_y - 1) ? pos_y : pos_y + 1;

	double alike = 0;
	double different = 0;

	for (unsigned int x = x_min; x <= x_max; x++) {
		for (unsigned int y = y_min; y <= y_max; y++) {
			if (x == pos_x && y == pos_y)
				continue;
			else if (n.get(x, y).getType() == "empty")
				continue;
			else if (n.get(x, y).getType() == n.get(pos_x, pos_y).getType())
				alike++;
			else
				different++;
		}
	}

	return    (different || alike)
		&& (different == 0 || alike / different >= RATIO_ALIKE_HAPPY)
		&& (alike == 0 || different / alike >= RATIO_DIFFERENT_HAPPY);
}/**
 * Return `true` if the shape is happy (i.e. not willing to move), and
 * `false` otherwise.
 *
 * - More specifically, return `true` if and only if the shape
 *     - has more than 0 "triangle" or "square" neighbors
 *     - and the ratio of like neighbors to unlike (different)
 *       neighbors is greater than or equal to `RATIO_ALIKE_HAPPY`
 *       (from `constants.h`)
 *     - and the ratio of unlike (different) neighbors to like
 *       neighbors is greater than or equal to `RATIO_DIFFERENT_HAPPY`
 *       (from `constants.h`)
 *
 * Notes:
 * - Use `n.get(...).getType() == "..."` to determine the type of the
 *   `Shape` at a given position.
 * - Be careful not to look for neighbors outside the bounds of the
 *   `Neighborhood`.
 * - Be careful not to have a shape count itself, when trying to count
 *   its neighbors.
 * - Be careful not to count "empty" shapes as unlike (different)
 *   shapes ("empty" shapes should not count as either like or
 *   unlike).
 * - Be careful of possible division by 0 when testing the ratios of
 *   like and unlike shapes.
 */

//-------------------------------------------------------------------------------------------------------------------------------------------------------
//neighborhood.cpp

/* ----------------------------------------------------------------------------
* Copyright &copy; 2016 Thomas Brenner, Adam Djabra, Andrew Nomura <tommyb@csu.fullerton.edu>
* Released under the [MIT License] (http://opensource.org/licenses/MIT)
* ------------------------------------------------------------------------- */

/**
* Implements of `neighborhood.h`.
*/
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
// TODO: `#include`s for other system headers, if necessary

#include "neighborhood.h"
#include "constants.h"


// TODO: `#include`s for other local headers, if necessary

// ----------------------------------------------------------------------------
// local helper functions
namespace {

	/**
	* Return a uniformly distributed random number in the range [low, high]
	* using the Mersenne Twister engine, seeded with (ideally) the hardware
	* random device.
	*
	* Because `rand()` (and especially `rand() % ...`) maybe shouldn't be
	* used, if we can avoid it:
	* [`rand()` considered harmful]
	* (https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful)
	* (talk by stephan t. lavavej)
	*
	*
	* Notes:
	* - In C++, `static` function variables are created and initialized once,
	*   when the function is first called, and they remain until the program
	*   is terminated:
	*   [Static variables in class methods]
	*   (http://stackoverflow.com/questions/6223355/static-variables-in-class-methods)
	* - `std::mt19937` objects are expensive to create.
	*   `std::uniform_int_distribution` objects are said to be pretty cheap.
	*/
	unsigned int mtrand(unsigned int low, unsigned int high) {
		static std::random_device rd;
		static std::mt19937 mt(rd());  // engine (mersenne twister)

		return std::uniform_int_distribution<unsigned int>(low, high)(mt);
	}

}


//Neighborhood(unsigned int size_x, unsigned int size_y);
Neighborhood::Neighborhood(unsigned int size_x, unsigned int size_y)
	: size_x(size_x), size_y(size_y) {

	// initialize `neighborhood_` and fill with "empty" `Shape`s
	neighborhood_ = new Shape[size_x * size_y]();

	// fill with non-empty shapes so that the ratio of non-empty to empty
	// shapes is `RATIO_FILLED` (from `constants.h`)
	for (int filled = 0; filled < size_x*size_y*RATIO_FILLED; ) {
		unsigned int x = mtrand(0, size_x - 1);
		unsigned int y = mtrand(0, size_y - 1);

		if (this->get(x, y).getType() == "empty") {
			this->set(x, y, mtrand(0, 1) ? Shape("triangle")
				: Shape("square"));
			filled++;
		}
	}
}

/**
* The constructor.
*
* Must initialize `size_x` and `size_y`.
*
* Must also allocate memory for `neighborhood_`, initialize it to
* contain all "empty" `Shape`s, and then fill it with non-empty shapes
* so that the ratio of non-empty to empty shapes is `RATIO_FILLED`
* (from `constants.h`).
*
* Notes:
* - Since `size_x` and `size_y` are constant, they must be initialized
*   in the initialization list, rather than set in the constructor
*   body.
* - You may assume that the dynamic memory allocation succeeds.
*/

Neighborhood::~Neighborhood() {
	delete[] neighborhood_;
}
/**
* The destructor.
*
* Must free the memory that the constructor allocated to
* `neighborhood_`.
*/


Shape Neighborhood::get(unsigned int x, unsigned int y) const {
	if (x >= size_x || y >= size_y)
	{
		std::cout << "ERROR: Buffer::get : index out of bounds\n";

		exit(1);
	}


	return neighborhood_[y * size_x + x];
}
/**
* Return the `Shape` at `neighborhood_[ y * size_x + x ]`.
*
* If `x` or `y` is out of bounds, should write
* ```
* "ERROR: `Neighborhood::get`: index out of bounds\n"
* ```
* to `cerr` and `exit(1)`.
*/

void Neighborhood::set(unsigned int x, unsigned int y, const Shape & s) {
	neighborhood_[y * size_x + x] = s;

	if (x >= size_x || y >= size_y)
	{
		std::cout << "ERROR: Buffer::get : index out of bounds\n";

		exit(1);
	}
}
/**
* Set the `Shape` at `neighborhood_[ y * size_x + x ]` to `s`.
*
* If `x` or `y` is out of bounds, should write
* ```
* "ERROR: `Neighborhood::set`: index out of bounds\n"
* ```
* to `cerr` and `exit(1)`.
*/


//void move(unsigned int old_x, unsigned int old_y);
void Neighborhood::move(unsigned int old_x, unsigned int old_y) {
	for (;;) {
		unsigned int x = mtrand(0, size_x - 1);
		unsigned int y = mtrand(0, size_y - 1);

		if (get(x, y).getType() == "empty") {
			set(x, y, get(old_x, old_y));
			set(old_x, old_y, Shape("empty"));

			break;
		}
	}
}
/**
* Move the shape at index `old_x, old_y` to a random empty location in
* the neighborhood.
*/


void Neighborhood::animate(unsigned int frames) {
	Buffer b(size_x*Shape::size_x, size_y*Shape::size_y);


	for (; frames; frames--) {
		// draw all the shapes in our neighborhood to it 
		for (unsigned int y = 0; y < size_y; y++) {
			for (unsigned int x = 0; x < size_x; x++) {
				get(x, y).drawToBuffer(b, x * Shape::size_x, y * Shape::size_y);
			}
		}
		// render it to the screen
		b.draw();

		// move all the unhappy shapes
		for (unsigned int y = 0; y < size_y; y++) {
			for (unsigned int x = 0; x < size_x; x++) {
				if (!get(x, y).isHappy(*this, x, y)) {
					move(x, y);
				}
			}
		}
		// wait a little while before drawing the next frame
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}
/**
* 1. Create a buffer.
* 2. Draw all the shapes in our neighborhood to it, and render it to
*    the screen.
* 3. Move all the unhappy shapes, and go back to step (2).
*
* Loop from step (3) to step (2) `frames` times; that is, the
* neighborhood should be rendered to the screen (i.e. output to the
* terminal) `frames` times.
*
* To make it so that each frame can be seen, you should have the
* program sleep for a little while (probably at least 100
* milliseconds) at the end of each loop.  To do this, include the
* `<chrono>` and `<thread>` headers, and use the following code:
* ```
* std::this_thread::sleep_for(std::chrono::milliseconds(100));
* ```
*/


/**
* Notes:
* - If you like, you can start reading about what this "unnamed `namespace`"
*   is for [here](http://www.comeaucomputing.com/techtalk/#nostatic).
*/


// ----------------------------------------------------------------------------

// TODO: implementations for all functions in `class Neighborhood`


