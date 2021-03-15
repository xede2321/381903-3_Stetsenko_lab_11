#ifndef _POLISH_H_
#define _POLISH_H_

#include "../StackLib/Stack.h"
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

class IOper
{
public:
  virtual int Priority() = 0;
  virtual int GetNumber() = 0;
  virtual IOper* Calc(IOper* a, IOper* b) = 0;
};

class TNum : public IOper 
{
protected:
  int data;
public:
  TNum(int _d);
  TNum(TNum& _v);
  TNum(char* s);

  virtual int Priority();
  virtual int GetNumber();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TOper : public IOper 
{
protected:
  char data;

public:
  TOper(char _d);
  TOper(TOper& _v);

  virtual int GetNumber();
};

class TPlus : public TOper
{
public:
  TPlus(char _d) : TOper(_d) {}

  virtual int Priority();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TMinus : public TOper
{
public:
  TMinus(char _d) : TOper(_d) {}

  virtual int Priority();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TMultiplication : public TOper
{
public:
  TMultiplication(char _d) : TOper(_d) {}

  virtual int Priority();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TDivision : public TOper
{
public:
  TDivision(char _d) : TOper(_d) {}

  virtual int Priority();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TOpenBracket : public TOper
{
public:
  TOpenBracket(char _d) : TOper(_d) {}

  virtual int Priority();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TCloseBracket : public TOper
{
public:
  TCloseBracket(char _d) : TOper(_d) {}

  virtual int Priority();
  virtual IOper* Calc(IOper* a, IOper* b);
};

class TOperFactory 
{
public:
  static void Create(char* s, int& n, IOper**& opers);
};

class TPolish 
{
public:
  static int Calculate(char* s);
};

#endif