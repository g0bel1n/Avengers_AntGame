# Avenger AntGame

## Briefly

This project is an implementation of what can be called an "Ant Search". Generic ants are independently generated. They
follow some basic rules, are attracted to food and leave pheromones or markers behind them depending on in which state
they are. It enables them to guide other in order to develop a common intelligence based on each individual experience.

It can be implemented to solve TSP Problems

## An example

<div align ="center"> 

![git_Antgame_vid_1](https://github.com/g0bel1n/Avengers_AntGame/blob/master/ressources/ant_gif.gif)

</div>

Below, in a very simple configuration, we can see that the ants are following markers to find their direction.

## On Boarding

The simulation offers many functionalities.

Before launching the game, many parameters are accessible in the ```parameters.h``` file.

When the simulation is launched the user arrives on frozen state. All the functionalities shown here are also available when the simulation is running.
The upper right info area represents data of the colony that is modifiable by the user. To switch to another colony, the user can press *Enter*, and therefore modify the specs of another colony. 
The user can modify the number of ants in this colony and their speed using the arrows keys. It is also possible to move the colony : the user have to put his mouse where he intends to move the colony and when it's done, he only has to press *D*.

There are also features that affects the world such as pressing *M*, *F*, *C* to respectively clear every Marker, every Food and every Obstacle.

Moreover, quitting the simulation with *Q* shows a graphics that represents the update delay and the number of markers according to the time. It is useful to assess the optimality of the code.


