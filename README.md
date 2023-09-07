# 3DViewer on C Laguage

## Implementation of 3DViewer

In this project a program to view 3D wireframe models (3D Viewer) in the C programming language implamented. The models themselves must be loaded from .obj files and be viewable on the screen with the ability to rotate, scale and translate. The program is built with Makefile which contains standard set of targets for GNU-programs: all, install, uninstall, clean, dvi, dist, tests, gcov. The full coverage of modules related to model loading and affine transformations with unit-tests prepared.
The program provides the ability to:
    - Load a wireframe model from an obj file (vertices and surfaces list support only).
    - Translate the model by a given distance in relation to the X, Y, Z axes.
    - Rotate the model by a given angle relative to its X, Y, Z axes.
    - Scale the model by a given value.
    - The program allowes customizing the type of projection (parallel and central)
    - The program allowes setting up the type (solid, dashed), color and thickness of the edges, display method (none, circle, square), color and size of the vertices
    - The program allowes choosing the background color
    - Settings are saved between program restarts
    - The program allowes saving the captured (rendered) images as bmp and jpeg files.
    - The program allowes recording small screencasts by a special button - the current custom affine transformation of the loaded object into gif-animation (640x480, 10fps, 5s)

The graphical user interface containes:
    - A button to select the model file and a field to output its name.
    - A visualisation area for the wireframe model.
    - Button/buttons and input fields for translating the model.
    - Button/buttons and input fields for rotating the model.
    - Button/buttons and input fields for scaling the model.
    - Information about the uploaded model - file name, number of vertices and edges.
