# vs-hook
---
Visual Studio C++ functions hook framework. 

##About
-----
By using the /Gh compiler switch vs will call __penter in every function epilog, implementing this function
as a naked function we can use it to trace calls, install hook do whatever we want in every function entry


## Development
---
- This project is in it's early stage, what is implement is a proof of concept, a demo to calculate calls count to the hooked
functions.
- Want to contribute? Great! please fork and submit pull requests.

## Todo's
---
- Callbacks on hooked function AKA stubs
- Static methods hooking and global functions
- Refine the current code and rewrite it in more readable way
- X86_64 support



#License
------
MIT

