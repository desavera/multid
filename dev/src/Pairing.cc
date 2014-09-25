#ifdef __GNUC__
#pragma implementation
#endif
#include <Pairing.h>
#include <Scene.h>

Pairing &
Pairing::operator = (const Pairing & list)
{
	if (this != &list) {
		PairingNode::dereference(head);
		PairingNode::reference(list.head);
		head = list.head;
		tail = list.tail;
	}
	return *this;
}

void
Pairing::append(const Pairing & list)
{
	PairingNode::reference(list.head);
	if (head == 0)
		head = list.head;
	else {
		tail->next = list.head;
		if (list.head != 0)
			list.head->prev = tail;
	}
	tail = list.tail;
}

void
Pairing::prepend(const Pairing & list)
{
	PairingNode *h = list.head;
	if (h != 0) {
		PairingNode *node = new PairingNode(h->preimage, h->image);
		node->prev = 0;
		PairingNode *trailer = node;
		for (h = h->next; h != 0; h = h->next) {
			PairingNode *n = new PairingNode(h->preimage, h->image);
			trailer->next = n;
			n->prev = trailer;
			trailer = n;
		}
		trailer->next = head;
		if (head != 0)
			head->prev = trailer;
		head = node;
	}
}

void
Pairing::join(const Scene & preimage, const Scene & image)
{
	// NOTE:  The join routine assumes that the GeomObjs on the
	//        preimage and image Scenes are in one-to-one correspondence.
	for (int i = 0; i < preimage.n_geom_objs(); i++)
		add(preimage[i], image[i]);
}

void
Pairing::del(const GeomObj & preimage)
{
	PairingNode *h = head;

	for ( ; ; ) {
		if (h == 0) {
			tail = head = h;
			return;
		}
		else if (h->preimage == preimage) {
			PairingNode *n = h->next;
			if (n != 0)
				n->prev = 0;
			if (--h->ref == 0)
				delete h;
			h = n;
		}
		else
			break;
	}

	PairingNode *prev = h;
	PairingNode *node = h->next;
	while (node != 0) {
		if (node->preimage == preimage) {
			PairingNode *n = node->next;
			if (n != 0)
				n->prev = node->prev;
			if (--node->ref == 0)
				delete node;
			prev->next = n;
			node = n;
		}
		else {
			prev = node;
			node = node->next;
		}
	}
	head = h;
	tail = prev;
}

GeomObj
Pairing::del_last(const GeomObj & preimage)
{
	PairingNode *t = tail;

	if (t == 0)
		throw EmptyList();

	if (t->preimage == preimage) {
		GeomObj image = t->image;
		PairingNode *p = t->prev;
		if (p != 0)
			p->next = 0;
		else
			head = 0;
		tail = p;
		if (--t->ref == 0)
			delete t;
		return image;
	}

	PairingNode *next = t;
	PairingNode *node = t->prev;
	while (node != 0) {
		if (node->preimage == preimage) {
			GeomObj image = node->image;
			PairingNode *p = node->prev;
			if (p != 0)
				p->next = node->next;
			else
				head = next;
			next->prev = p;
			if (--node->ref == 0)
				delete node;
			return image;
		}
		else {
			next = node;
			node = node->prev;
		}
	}

	throw PreimageNotFound();
}
