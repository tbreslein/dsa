package sort

import (
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestBubbleSort(t *testing.T) {
	foo := []int{1, 3, 7, 4, 2}
	BubbleSort(&foo)
	assert.Equal(t, &foo, &[]int{1, 2, 3, 4, 7}, "it's sorted!")
}

func TestQuickSort(t *testing.T) {
	foo := []int{1, 3, 7, 4, 2}
	QuickSort(&foo)
	assert.Equal(t, &foo, &[]int{1, 2, 3, 4, 7}, "it's sorted!")
}
