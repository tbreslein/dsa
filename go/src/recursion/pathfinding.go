// Package recursion foo
package recursion

import (
	"github.com/tbreslein/fem-dsa/src/stack"
)

// Point Coordinate on the map
type Point struct {
	x, y int
}

// SolveMaze Takes an array strings (think of it like a matrix of characters), what the walls of the maze look like,
// as well as the coordinates for where the maze starts and ends, and returns the list of points visited after reaching
// the end of the maze.
func SolveMaze(maze []string, wall string, start Point, end Point) []Point {
	// NOTE: would be more ergonomic using a boolean mask for the coordinates, instead of this set
  visitedTiles := make(map[Point]bool)

	path := stack.NewStack[Point]()
	step(start.x, start.y, &path, &maze, &visitedTiles, &wall, &end)

	// convert stack to array
	pathArray := make([]Point, 0)
  for {
    val, err := path.Pop()
    if err != nil {
      break
    }
		pathArray = append(pathArray, val)
  }
  // reverse the array, because currently it goes end to start
  for i, j := 0, len(pathArray)-1; i < j; i, j = i+1, j-1 {
    pathArray[i], pathArray[j] = pathArray[j], pathArray[i]
  }

	return pathArray
}

func step(j int, i int, path *stack.Stack[Point], maze *[]string, visitedTiles *map[Point]bool, wall *string, end *Point) bool {
	// base cases
	if i < 0 || j < 0 || i >= len((*maze)[0]) || j >= len(*maze) {
		return false
	}
	if string((*maze)[j][i]) == *wall {
		return false
	}
  if j == end.x && i == end.y {
    path.Push(Point{j, i})
    return true
  }
	if _, alreadyVisisted := (*visitedTiles)[Point{j, i}]; alreadyVisisted {
		return false
	}


	// new tile, so add it to the stack, as well as visitedTiles
	path.Push(Point{j, i})
	(*visitedTiles)[Point{j, i}] = true

	if step(j+1, i, path, maze, visitedTiles, wall, end) {
		return true
	}
	if step(j, i+1, path, maze, visitedTiles, wall, end) {
		return true
	}
	if step(j-1, i, path, maze, visitedTiles, wall, end) {
		return true
	}
	if step(j, i-1, path, maze, visitedTiles, wall, end) {
		return true
	}

	path.Pop()

	return false
}
