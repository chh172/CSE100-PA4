
* readme.md
* Author: Chuhuan Huang Junyi Wu
* Date:  May, 31st, 2019
*
* Answers of the readme questions

1.
choose a vertex v0 arbitrarily
for each other vertex v in our graph
  check if there exists a path between v and v0 // mostly Dijkstra O(ElogE + V)
  (namely check if the path we construct is empty )
  break the loop if doesn't

worst case time complexity will be O(|V|^2 + VElogE)

2.
V = set of all vertex in our graph
while V is not empty {
  choose a vertex v arbitrarily from V
  set V' = {v}
  for each other vertex v' in our V
    check if there exists a path between v and v'// mostly Dijkstra O(ElogE + V)
    if so add v' to V'
  V = V \ V'
}
worst case time complexity will be O(|V|^3 + V^2 * ElogE) where V is the set of
all vertex

3.
v0 is the ActorNode of Kevin Bacon
for each other vertex v in our graph
  construct the path // mostly Dijkstra
  count the length of path
  if the path length > 6
    set up flag and break the loop
check if the flag is set up
time complexity will be O(|V|^2 + |V|ElogE)    
