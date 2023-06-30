package search

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestLinearSearch(t *testing.T) {
	foo := []int{10, 12, 13, 11}
	assert.Equal(t, LinearSearch(&foo, 12), 1, "12 is at index 1")
	assert.Equal(t, LinearSearch(&foo, 13), 2, "13 is at index 2")
	assert.Equal(t, LinearSearch(&foo, 14), -1, "no 14 in the array")
	assert.NotEqual(t, LinearSearch(&foo, 14), 2, "no 14 in the array")
}

func TestBinarySearch(t *testing.T) {
	foo := []int{10, 12, 14, 17, 22, 32}
	assert.Equal(t, BinarySearch(&foo, 12), 1, "find 12")
	assert.Equal(t, BinarySearch(&foo, 14), 2, "find 14")
	assert.Equal(t, BinarySearch(&foo, 15), -1, "no 15 in the array")
	assert.NotEqual(t, BinarySearch(&foo, 32), 8, "find 32")
}

func TestCrystalBall(t *testing.T) {
	assert.Equal(t, CrystalBall(&[]bool{false, false, false, true, true, true}), 3, "test1")
	assert.Equal(t, CrystalBall(&[]bool{false, true}), 1, "test2")
	assert.Equal(t, CrystalBall(&[]bool{true, true, true, true, true, true}), 0, "test3")
}
