/**
 * assigment # 2
 *
 */

import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {

  private class Node {
    public Item value = null;
    public Node next = null;
    public Node prev = null;
  }

  private int size;

  private Node head, tail;

  // construct an empty deque
  public Deque() {
    size = 0;
    head = null;
    tail = null;
  }

  // is the deque empty?
  public boolean isEmpty()
  {
    return (size == 0);
  }

  // return the number of items on the deque
  public int size()
  {
    return size;
  }

  // add the item to the front
  public void addFirst(Item item)
  {
    if (item == null)
      throw new java.lang.NullPointerException();

    Node insertNode = new Node();
    insertNode.value = item;

    if (head != null) {
      insertNode.next = head;
      head.prev = insertNode;
      head = insertNode;
    } else {
      insertNode.next = null;
    }
    head = insertNode;
    size++;

    if (tail == null)
      tail = head;
  }

  // add the item to the end
  public void addLast(Item item)
  {
    if (item == null)
    throw new java.lang.NullPointerException();

    Node insertNode = new Node();
    insertNode.value = item;

    if (tail != null) {
      insertNode.prev = tail;
      tail.next = insertNode;
      tail = insertNode;
    } else {
      insertNode.prev = null;
    }

    tail = insertNode;
    size++;

    if (head == null)
      head = tail;
  }

  // remove and return the item from the front
  public Item removeFirst()
  {
    if (isEmpty())
      throw new java.util.NoSuchElementException();

      Item result = head.value;
      if (size == 1) {
        head = null;
        tail = null;
      }
      else {
        head = head.next;
        head.prev = null;
      }
      size--;
      return result;
  }

  // remove and return the item from the end
  public Item removeLast()
  {
    if (isEmpty())
      throw new java.util.NoSuchElementException();

      Item result = tail.value;
      if (size == 1) {
        head = null;
        tail = null;
      }
      else {
        tail = tail.prev;
        tail.next = null;
      }
      size--;
      return result;
  }

  // return an iterator over items in order from front to end
  public Iterator<Item> iterator()
  {
    return new DequeIterator();
  }

  private class DequeIterator implements Iterator<Item>
  {
    private Node currentNode = head;
    
    @Override
  public boolean hasNext()
    {
   return currentNode!=null;
  }

  @Override
  public Item next()
    {
   if (!hasNext())
        throw new java.util.NoSuchElementException();
   Item item = currentNode.value;
   currentNode = currentNode.next;
   return item;
  }

  @Override
  public void remove()
    {
   throw new UnsupportedOperationException();
  }
  }

  // unit testing (optional)
  public static void main(String[] args)
  {

  }

}
