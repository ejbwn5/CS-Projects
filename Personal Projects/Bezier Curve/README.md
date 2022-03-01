# Bezier Curves

This is a program I wrote in Python using the matplotlib library to plot [Bezier Curves](https://en.wikipedia.org/wiki/B%C3%A9zier_curve). Right clicking creates a new control point, and left click + dragging moves existing points. The backspace key clears the plot, the delete key deletes the most recently selected node, and the spacebar toggles point/control handle visibility. The C key toggles whether or not the curve should have connected endpoints.

The original Bezier.py file plots nth order bezier curves, while the BezierAlternate.py file plots composite cubic bezier curves, which is more commonly used in computer graphics engines like Blender or Autodesk 3ds Max.

## Nth Order Bezier
This is an example of a quartic bezier curve, drawn using 5 control points.
![Example](Example.png?raw=true "Example")

## Composite Cubic Bezier Example

This is an example showing how composite cubic bezier curves are often used. This is an approximation of the curve representing the famous Circuit de Spa-Francorchamps racetrack.

With control points:
![Example](Composite1.PNG?raw=true "Example")

Without control points:
![Example](Composite2.PNG?raw=true "Example")