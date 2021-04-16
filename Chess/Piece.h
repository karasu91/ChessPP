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
  void addThreat(Piece*);
  void resetThreatVector(void);
  void setAvailableMoves(vector<string>);
  void clearAvailableMoves();
  vector<string> getAvailableMoves();
  string toString(void);
  vector<Piece*> getThreatVector(void);
 private:	 
  vector<Piece*> threats;
  vector<string> availableMoves;
  int color;
  int type;
  int hasMoved;
};

