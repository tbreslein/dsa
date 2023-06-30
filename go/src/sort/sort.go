// Package sort funcs
package sort

import (
	"golang.org/x/exp/constraints"
)

// BubbleSort as the name suggests...
func BubbleSort[T constraints.Ordered](arr *[]T) {
	for i := 0; i < len(*arr); i++ {
		for j := 0; j < len(*arr)-i-1; j++ {
			if (*arr)[j] > (*arr)[j+1] {
				swap(arr, j, j+1)
			}
		}
	}
}

// QuickSort as the name suggests...
func QuickSort[T constraints.Ordered](arr *[]T) {
	qs(arr, 0, len(*arr)-1)
}

func qs[T constraints.Ordered](arr *[]T, lo int, hi int) {
	if lo >= hi {
		return
	}
	pivotIdx := partition(arr, lo, hi)
	qs(arr, lo, pivotIdx-1)
	qs(arr, pivotIdx+1, hi)
}

func partition[T constraints.Ordered](arr *[]T, lo int, hi int) int {
	pivot := (*arr)[hi]
	idx := lo - 1
	for i := lo; i < hi; i++ {
		if (*arr)[i] <= pivot {
			idx++
			swap(arr, idx, i)
		}
	}
	idx++
	swap(arr, hi, idx)
	return idx
}

func swap[T any](arr *[]T, i int, j int) {
	tmp := (*arr)[i]
	(*arr)[i] = (*arr)[j]
	(*arr)[j] = tmp
}
