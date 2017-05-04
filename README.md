# techTrek2017

A list of projects for the screen array built for Tech Trek 2017 at The Forge in Ann Arbor.  
This event will happen June 16th, 2017.  See http://annarborusa.org/techtrek/.

We will cover one of the walls at The Forge with a light-up array about eight feet tall and 25 feet wide.
Each light is an 11" round balloon backed by a 32-bit RGBW LED.  The array will be 24 pixels wide by 8 pixels high.

Please fork this repository and send me pull requests for displays that you want to contribute to this event.

## Project List:

### Fun Stuff

**randomMatrix**: This program simulates Hollywood computers from the 1960's.
  https://www.youtube.com/watch?v=mIcSkuEbRSg

**Conway's Game of Life**: classic computer science problem
https://www.youtube.com/watch?v=ASGULYbXmfs

TODO: **Message Marquee**

### Boring Stuff

**singleDotCycleEntireMatrix**:  Verify that the individual LED strands are wired correctly in the proper order.

**pixelIntegrityTest**: Verify all LEDS in each pixel are functional for an entire matrix.  Used to check for problems 
after the matrix is assembled.

**strandIntegrityTest**: Verify all LEDS in each pixel are functional for a single strand.  Used to check for problems 
after soldering a bunch of LEDS.

**stressTest**: Verify that the power is adequate for lighting all pixels full blast at the same time

