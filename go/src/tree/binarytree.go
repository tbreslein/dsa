// Package binary_tree
package binary_tree

import (
	"github.com/tbreslein/fem-dsa/src/queue"
	"golang.org/x/exp/constraints"
)

// BinaryTree simple binary tree
type BinaryTree[T any] struct {
	value T
	left  *BinaryTree[T]
	right  *BinaryTree[T]
	// parent  *BinaryTree[T]
}

func walkPreOrder[T any](currentNode *BinaryTree[T], path *[]T) *[]T {
  if currentNode == nil {
    return path
  }
  *path = append(*path, currentNode.value)
  walkPreOrder(currentNode.left, path)
  walkPreOrder(currentNode.right, path)
  return path;
}

// PreOrderSearch searches the tree in a pre-order fashion and return the path that was traversed
func PreOrderTraversal[T any](head *BinaryTree[T]) *[]T {
  path := make([]T, 0)
  return walkPreOrder(head, &path)
}

func walkInOrder[T any](currentNode *BinaryTree[T], path *[]T) *[]T {
  if currentNode == nil {
    return path
  }
  walkInOrder(currentNode.left, path)
  *path = append(*path, currentNode.value)
  walkInOrder(currentNode.right, path)
  return path;
}

// InOrderSearch searches the tree in an in-order fashion and return the path that was traversed
func InOrderTraversal[T any](head *BinaryTree[T]) *[]T {
  path := make([]T, 0)
  return walkInOrder(head, &path)
}

func walkPostOrder[T any](currentNode *BinaryTree[T], path *[]T) *[]T {
  if currentNode == nil {
    return path
  }
  walkPostOrder(currentNode.left, path)
  walkPostOrder(currentNode.right, path)
  *path = append(*path, currentNode.value)
  return path;
}

// PreOrderSearch searches the tree in a post-order fashion and return the path that was traversed
func PostOrderTraversal[T any](head *BinaryTree[T]) *[]T {
  path := make([]T, 0)
  return walkPostOrder(head, &path)
}

// BreadthFirstSearch searches the tree for the val and returns whether it found it
func BreadthFirstSearch[T comparable](head *BinaryTree[T], val T) bool {
  queue := queue.NewQueue[*BinaryTree[T]]()
  queue.Push(head)

  for queue.Length() > 0 {
    curr, _ := queue.Pop()
    if curr.value == val {
      return true;
    }
    if curr.left != nil {
      queue.Push(curr.left)
    }
    if curr.right != nil {
      queue.Push(curr.right)
    }
  }

  return false
}

// Compare compare the two binary trees for deep equality
func DeepCompare[T comparable](a *BinaryTree[T], b *BinaryTree[T]) bool {
  if a == nil && b == nil {
    return true
  } else if a == nil || b == nil {
    return false
  } else if a.value != b.value {
    return false
  }

  return DeepCompare(a.left, b.left) && DeepCompare(a.right, b.right)
}

// BinarySearch returns whether the tree contains val. Assumes that our BinaryTree is actually a BinarySearchTree!
func BinarySearch[T constraints.Ordered](current *BinaryTree[T], needle T) bool {
  if current == nil {
    return false
  } else if current.value == needle {
    return true
  }

  if current.value < needle {
    return BinarySearch(current.right, needle)
  }
  return BinarySearch(current.left, needle)
}
