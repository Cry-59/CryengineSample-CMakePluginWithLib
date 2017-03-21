Simple cryengine plugin example demonstrating a simple external library integration.
Both CMakeLists and Project Code example.

NOTES:
1. An example third-party library is contained inside "ThirdPartyLibs/ThirdPartyLib" (Binary/lib and include files)
2. CMakeLists has some customization to;
- A) Copy the third-party binary to the used engine folder and 
- B) Correctly add required third-party directories.

Assumes x64 binaries (some hardcoded paths - eg, engine path).

USAGE:

(from Cryproject file)
1. Generate solution.
2. Launch Game.
3. Check game.log for the following message:
- "Loaded ThirdPartyLib. Name: ThirdPartyLibExample, Version: 1.0.0"