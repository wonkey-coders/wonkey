# WonkeyTutorials
Some example code for the Wonkey programming language

## Spacecraft Tutorial
### Part 1:

1) Create a SpaceCraft class that extends Window
2) Prepare some methods to draw and update the screen
3) Make a GameObject Class which will be the base class for all our game objects
4) Implement a simple Component class for giving game objects functionality
5) Create a Player class with a control Component and get it drawing to the screen

### Part 2:

1) Enable the GameObject to have a Body and Space and set up an InitPhysics method
2) Add a chipmunk Space in the SpaceCraft class.
3) Write some maintainence functions to handle adding and removing from the Space
4) Use a Chipmunk bounding box query to draw all objects on screen (in this case just the player).

### Part 3:

1) Build on the Controls component to define the player controls and get it moving about
2) Use a chipmunk query to update objects that are on screen

### Part 4 - Implement json to load in a set of map tiles

### Part 5 - Create a terrain class that will manage adding and removing tiles from the game world
1) Create a Tilemap class and set some initial fields that we'll need
2) Create some methods for converting screen coordinates into node coordinates and vice versa
3) Set the origin vec in the Spacraft Class to the centre of the screen
4) Test the coordinates for the tilemap are working ok.

### Part 6 - Create a tile layer class and draw tiles to the screen according to adjacent tiles.
1) Create a TileLayer class and create some fields and methods that we'll need
2) Add extra methods and fields to the TileMap class that we need
3) Draw nodes to the screen with just a single block tile for each node to start with and test.
4) Add a way to erase tiles

### Part 7 - Make the tiles take into account adjacent nodes to draw the appropriate tiles in the world
1) Alter the AssignTiles method to create four tiles for each node
2) Create AssignTile to assign the correct tile image according to surrounding nodes
3) Update the erase method to erase all tiles as necessary.

### Part 8 - Use TimelineFX to shoot a laser beam
1) Import TimelineFX and load in the effects library
2) Add a class to create the different weapons and utilities the ship can fire/use
3) Extend that class and make a laser beam class
4) Add controls to the player to fire the laser on left mouse (update the map drawing controls to something else as well)

### Part 9 - Use TimelineFX to shoot a laser beam
1) Import TimelineFX and load in the effects library
2) Add a class to create the different weapons and utilities the ship can fire/use
3) Extend that class and make a laser beam class
4) Add controls to the player to fire the laser on left mouse (update the map drawing controls to something else as well)

### Part 10 - Use Raycasting in Chipmunk to have the laser hit the maptiles
1) Start with some bug fixing with the virtual screen resolution
2) Create a segment query in chipmunk to handle the raycasting
3) Add a sparks particle effect at the point of impact
4) Add a particle effect for the player and a thruster effect too
5) Set the texture filter to linear for more crisper graphics

### Part 11 - Destroy the map tiles with the laser, and use a matrix to position points on the player
1) Use a matrix to calulate points on the player as it rotates to offset the laser and thrusters
2) Make the maptiles destructable by giving them properties and the ability to take damage
3) Add a glow effect for map tiles that are being mined
4) Add an explosion effect for when a tile is destroyed

### Part 12 - Add rocket objects that appear after mining a map tile
1) Create a new RockObject class that extends Gameobject
2) Use Chipmunk to handle the physics
3) Give them an expirey so that they dissapear after a while

### Part 13 - Create a tractor beam that can suck up the rocks
1) Create the TractorBeam class and set up the activate/deactive methods
2) Edit the player class to accomodate the tractor beam and add controls so that the it can be fired with right mouse
3) Create a chipmunk segment query to handle the tractor beam hitting the map tiles
4) Create a shape query to handle the rocks touching the beam and getting sucked up

### Part 14 - Make the player able to absorb the rocks with an effect

1) Add a Chipmunk sensor to the player

2) Set up a collision handler for when the sensor hits a rock

3) Add an effect for when a rock is hit and use a lambda to position it as the player moves about
