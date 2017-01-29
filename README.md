# AI-Challenge-2016

  The [AI-Challenge](http://aichallenge.sharif.edu) is an anual coding competition held by Sharif University of Technology.

  Complete discription of the game is included in the link above. In the following I will give an abstract discription and explain what our approach was.

## Game Rules
  The game takes place on a vertex-weighted graph where each vertex is initially empty and becomes a player's property as the game continues. Each player has a number of soldiers on several vertices, each vertex containing soldiers of at most one player and the weight representing the number of soldiers. For each vertex in possesion one choses an adjecent vertex to move some soldiers to, regarding that there must be at least one soldier left behind. If two different teams try to move to a single vertex at one turn a battle takes place. Player's soldiers increase by a certain amount when they win a battle or move to an empty vertex.
  The game ends when one of the players takes all the vertices. The player with the highest number of soldiers wins.
  
  Competing teams were given the code of the game; but were only allowed to write "doTurn" function in the "AI" class.
  
## Our Algorithm
  We approached this problem with a gready algorithm. Each turn for each vertex we determined the nearest route to the closest vertex not belonging to us, and depending on the state of that cell (empty,enemy's) we lead a calculated portion of the army (now present in that cell) to the next vertex of the desired route.
  
## Running the Game
  To run this game open FlowsGameServer-*.jar and then chose a map file to play in. Then in the Us_three folder run the command "make all". Now run the generated .jar file to start the game versus a desired AI, note that you should do the same with the oponents AI, if it is written in the same cpp format. For a test AI you can use the RandomClient AI that is represented in the repository.
  
## Pictures
  Below you can find some of the game's photos.
  
![alt tag](https://cloud.githubusercontent.com/assets/19167068/22404262/63b78b20-e642-11e6-9b82-120f4b5b7438.png)
![alt tag](https://cloud.githubusercontent.com/assets/19167068/22404264/6d41949c-e642-11e6-99e9-00a1fc55b7da.png)
![alt tag](https://cloud.githubusercontent.com/assets/19167068/22404266/786af0b6-e642-11e6-8be5-1b63bfa37dcb.png)
  
