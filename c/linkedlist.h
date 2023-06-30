typedef struct LinkedListInt {
  int data;
  struct LinkedListInt *next;
} linked_list_int;

linked_list_int *lli_new(int data) {
  struct LinkedListInt *new_node =
      (struct LinkedListInt *)malloc(sizeof(struct LinkedListInt));
  new_node->data = data;
  return new_node;
}

void *lli_free(linked_list_int **l) {
  if (*l != NULL) {
    if (l->next != NULL) {
    }
  }

  return;
}

int lli_peek(linked_list_int **l) { return l->data; }
