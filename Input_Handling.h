#include <string>

class Invalid_Input
{
 public :
    Invalid_Input(std::string in_ptr) : msg_ptr (in_ptr) { }
    const std::string msg_ptr;
 private :
    Invalid_Input ();
    // no default construction
};
