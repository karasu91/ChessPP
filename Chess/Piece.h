#pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Piece
{
 public:
  Piece(int, int);
  ~Piece();
  int getColor(void);
  int getType(void);
  int isMoved(void);
  void setMoved(int);
  void addThreatVect(int);
  void resetThreatVector(void);
  vector<int> getThreatVect(void);
 private:
  vector<int> threat;
  int color;
  int type;
  int moved;
};

