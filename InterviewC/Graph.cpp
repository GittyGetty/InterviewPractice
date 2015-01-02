struct node2 {
	int data;
	node2 *next = nullptr;
	node2 *other = nullptr;
};

node2* copy_linked_list(node2* list) {
	if (list == nullptr) return list;

	// Pass 1: Insert copies into linked list.
	node2 *n = list;

	while (n != nullptr) {
		node2* copy = new node2();
		copy->data = n->data;
		copy->next = n->next;
		n->next = copy;
		n = n->next->next;
	}

	// Pass 2: Set other pointers.
	while (n != nullptr) {
		n->next->other = n->other->next;
		n = n->next->next;
	}

	// Pass 3: Separate interweaved lists.
	node2* copy_list = nullptr;

	while (n != nullptr) {
		node2 *tmp = n->next;

		if (copy_list == nullptr)
			copy_list = tmp;
		else
			copy_list->next = tmp;

		n->next = n->next->next;
		n = n->next;
	}

	return copy_list;
}
