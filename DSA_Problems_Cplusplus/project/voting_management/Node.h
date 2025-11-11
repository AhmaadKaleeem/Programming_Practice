#pragma once
template <typename t>
class Node
{

public::
  t data;
  Node *next;

  Node() : data(t()), next(nullptr) {}
  Node(t value) : data(value), next(nullptr) {}
  
  
};