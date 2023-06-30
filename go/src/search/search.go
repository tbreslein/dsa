// Package search funcs
package search

import (
  "math"
  "golang.org/x/exp/constraints"
)

// LinearSearch Just walk the array from the beginning till we find the thing we are looking for, and return its index.
//
// Time comp: O(n), since we manually walk every single element
func LinearSearch[T comparable](haystack *[]T, needle T) int {
	for i, a := range *haystack {
		if a == needle {
			return i
		}
	}
	return -1
}

// BinarySearch Assuming that the haystack is a sorted array, binary search the needle and return its index.
//
// Binary search starts at the middle of the array and checks whether it is equal, smaller or greater than our needle.
// If it is equal, return the index. If the needle is greater, we know we should continue our search in the upper half
// of the array.
// With that knowledge, we jump to the middle of that part of the array, and do that check again, and recurse that until
// we find our value.
//
// Time comp: O(log(n)), since we can half the size of the haystack with each step, and we only have to look at a single
// element in each step.
func BinarySearch[T constraints.Ordered](haystack *[]T, needle T) int {
  upperBound := len(*haystack) - 1
  lowerBound := 0
	for lowerBound < upperBound {
    pos := (upperBound + lowerBound) / 2
		if (*haystack)[pos] == needle {
			return pos
		} else if (*haystack)[pos] < needle {
      // already know that the needle is not at pos, so put the lowerBound past it
      lowerBound = pos + 1
		} else {
      // upperBound is exclusive
      upperBound = pos
		}
	}
  return -1
}

// CrystalBall You have two identical crystal balls, find the floor of a tall building at which they break
//
// The idea is that linear search is too slow and binary search by itself cannot be used (because we might break both
// balls before finding the correct floor), so instead we hop from the ground floor upwards in steps of sqrt(height)
// until the first ball breaks, and then we go up from the last safe point we know linearly till our second ball breaks.
//
// Time comp: O(sqrt(n)), since we go up in steps of sqrt(n) initially, and in the "linear" phase after breaking the
// ball we only have to traverse at worst another sqrt(n) steps. So, at worst, we traverse 2*sqrt(n) elements.
func CrystalBall(building *[]bool) int {
  maxHeight := len(*building)
  dist := int(math.Sqrt(float64(maxHeight)))
  lastPos := 0
  for lastPos < maxHeight - 1 {
    nextFloor := int(math.Min(float64(lastPos + dist), float64(maxHeight)))
    if (*building)[lastPos + dist] {
      break;
    }
    lastPos = nextFloor
  }
  for lastPos < lastPos + dist {
    if (*building)[lastPos] {
      break
    }
    lastPos++
  }

  return lastPos;
}
