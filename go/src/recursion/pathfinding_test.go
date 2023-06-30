// Package recursion foo
package recursion

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestSolveMaze(t *testing.T) {
  maze := []string{
    "xxxxxxxxxx x",
    "x        x x",
    "x        x x",
    "x xxxxxxxx x",
    "x          x",
    "x xxxxxxxxxx",
  }
  path := SolveMaze(maze, "x", Point {0, 10}, Point {5,1})

	assert.Equal(t, &[]Point{
    {0, 10},
    {1, 10},
    {2, 10},
    {3, 10},
    {4, 10},
    {4, 9},
    {4,8},
    {4,7},
    {4,6},
    {4,5},
    {4,4},
    {4,3},
    {4,2},
    {4,1},
    {5,1},
  }, &path, "it's sorted!")
}
