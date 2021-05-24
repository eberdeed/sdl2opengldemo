/**********************************************************
 *   UniformPrinter:  A class to encapsulate printing out
 *   the unforms from a shader program.  Gives the location
 *   of the uniform and it's status.
 *   Created by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   12/2019 San Diego, California USA
 * ********************************************************/

#ifndef UNIFORMPRINTER_H
#define UNIFORMPRINTER_H
#include "commonheader.h"

/** A class to encapsulate printing out the unforms from a 
 * shader program.  Gives the location of the uniform and 
 * it's status.  Turn on debug1 in SceneMkr to see it used.
 */
class UniformPrinter
{
public:
    // Constructor:  requires the shader program object.
    UniformPrinter(int progObj);
    ~UniformPrinter();
protected:
    // Print the active uniforms in the shader program.
    void printUniforms();
    // Class global variables for limits, etc.
    int maxUniformLen, numUniforms, index, progObj;
    char *uniformName;
    
};



#endif // UNIFORMPRINTER_H
