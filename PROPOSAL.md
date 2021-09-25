#Rahul's Project Proposal


#####Project
For my final project, I would like to build a 
Machine Learning based Connect Four game. 

#####Background Knowledge/Extra Info
The game will be visualized using Cinder so that 
the user can play against the trained ML model. The idea is to train
the Model with data from millions of Connect Four games,
and for each move calculate the probability that a 
specific move wins. I then choose the move with the
highest probability to be the move that the model makes.
The training data contains both winning games and losing
games, this makes the move prediction more accurate.

#####Timeline
By the end of Week 1, I am aiming to complete the training
portion of the assignment. By the end of Week 2, I am aiming
to build the application with Cinder (UI, etc). By the
end of Week 3, I am aiming to combine the ML model with
the UI application and implement a leaderboard with SQL
to determine the players with the most wins against the 
model. 

#####Stretch Goals
If I were to finish the project early, I would try to
add functionality that allows gives the user hints
on what moves to make/the most optimal move from the
user which would be computed via the model. Also, I could
improve certain UI aspects of the Connect Four game, such
as allowing the user to choose their color or adding a timed
version of the game. Furthermore, I could try to implement a 
Convolutional Neural Network to help with predicting the optimal move
as opposed to solely relying on feature probabilities.