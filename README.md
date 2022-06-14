# StoveTop-simulation-Qt
What happens if you use a not really stable method to solve differential equation. Electric stove top simulation.

The project can be built in Qt creator (at least in version 7.0.1.).

The idea is to simulate an electric stove top. It consists of a heater element and a working plate, the material of which can be chosen
among several materials. When the simulation is ran, the heater heats up and heats also the working plate, which is directly on top of
the heater. Due to the instability of the explicit method used to calculate the evolution of the system, the solution often sometimes
does not work as expected :)

When ran, the programm displays a window, where, to the left, you can set the power supply to the stove, the number of threads for
parallel computing, the material of the stove top and change the pen size for drawing. In order to start simulations one has to draw
the heater element on the plane to the right. When everytihing is set, click start and switch on the heater.
