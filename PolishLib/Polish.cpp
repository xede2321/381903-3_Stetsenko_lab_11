#include "../PolishLib/Polish.h"

void TOperFactory::Create(char* s, int& n, IOper**& opers)
{
  int l = strlen(s);

  for (int i = 0; i < l; i++)
  {
    if (isdigit(s[i]) == 0)
      n++;
  }
  n++;
  n = 2 * n - 1;
  IOper** res = new IOper * [n];
  int start = 0;
  int j = 0;

  for (int i = 0; i < l; i++)
  {
    if (i == 0)
    {
      if (s[i] == '(')
      {
        res[j] = new TOpenBracket('(');
        j++;
        start = i + 1;
        continue;
      }
    }
    else
    {
      if (isdigit(s[i - 1]) != 0)
      {
        char temp[256];
        int _l = i - start + 1;

        for (int k = 0; k < _l - 1; k++)
          temp[k] = s[start + k];
        temp[_l - 1] = 0;
        res[j] = new TNum(temp);
        j++;
      }
      if (s[i] == '(')
      {
        res[j] = new TOpenBracket('(');
        j++;
        start = i + 1;
      }
      else if (s[i] == ')')
      {
        res[j] = new TCloseBracket(')');
        j++;
        start = i + 1;
      }
      else if (s[i] == '+')
      {
        res[j] = new TPlus('+');
        j++;
        start = i + 1;
      }
      else if (s[i] == '-')
      {
        res[j] = new TMinus('-');
        j++;
        start = i + 1;
      }
      else if (s[i] == '*')
      {
        res[j] = new TMultiplication('*');
        j++;
        start = i + 1;
      }
      else if (s[i] == '/')
      {
        res[j] = new TDivision('/');
        j++;
        start = i + 1;
      }
    }
  }

  char temp[256];
  int _l = l - start + 1;
  if (_l > 1)
  {
    for (int k = 0; k < _l - 1; k++)
      temp[k] = s[start + k];
    temp[_l - 1] = 0;
    res[j] = new TNum(temp);
    j++;
  }
  n = j;
  opers = new IOper * [j];

  for (int i = 0; i < j; i++)
    opers[i] = res[i];

  delete[] res;
}

int TPolish::Calculate(char* s)
{
  int n = 0;
  IOper** opers = nullptr;
  TOperFactory::Create(s, n, opers);

  IOper** res = new IOper * [n];
  TStack<IOper*> stack(n);
  int j = 0;

  for (int i = 0; i < n; i++)
  {
    if (opers[i]->Priority() == -1)
    {
      res[j] = opers[i];
      j++;
    }
    else
    {
      if ((opers[i]->Priority() == 1) || (stack.IsEmpty()))
        stack.Put(opers[i]);
      else if (opers[i]->Priority() == 0)
      {
        IOper* temp = stack.Get();
        while (temp->Priority() != 1)
        {
          res[j] = temp;
          j++;
          temp = stack.Get();
        }
      }
      else if (opers[i]->Priority() != 1 && opers[i]->Priority() != 0)
      {
        IOper* temp = stack.Get();
        if (opers[i]->Priority() > temp->Priority())
        {
          stack.Put(temp);
          stack.Put(opers[i]);
        }
        else
        {
          while (opers[i]->Priority() <= temp->Priority())
          {
            res[j] = temp;
            j++;
            if (!stack.IsEmpty())
              temp = stack.Get();
            else
              break;
          }
          if (!stack.IsEmpty())
            stack.Put(temp);
          stack.Put(opers[i]);
        }
      }
    }
  }

  while (!stack.IsEmpty())
  {
    IOper* temp = stack.Get();
    res[j] = temp;
    j++;
  }

  TStack<IOper*> ns(n);

  for (int i = 0; i < j; i++)
  {
    if (res[i]->Priority() == -1)
      ns.Put(res[i]);
    else
    {
      IOper* b = ns.Get();
      IOper* a = ns.Get();
      IOper* c = res[i]->Calc(a, b);
      ns.Put(c);
    }
  }

  IOper* r = ns.Get();

  delete[] opers;
  delete[] res;
  return r->GetNumber();
}

TNum::TNum(int _d)
{
  data = _d;
}

TNum::TNum(TNum& _v)
{
  data = _v.data;
}

TNum::TNum(char* s)
{
  if (strlen(s) == 0)
    throw - 1;
  data = atof(s);
}

int TNum::Priority()
{
  return -1;
}

int TNum::GetNumber()
{
  return data;
}

IOper* TNum::Calc(IOper* a, IOper* b)
{
  throw - 1;
}

TOper::TOper(char _d)
{
  data = _d;
}

TOper::TOper(TOper& _v)
{
  data = _v.data;
}

int TOper::GetNumber()
{
  throw - 1;
}

int TPlus::Priority()
{
  return 2;
}

IOper* TPlus::Calc(IOper* a, IOper* b)
{
  TNum* res = new TNum(a->GetNumber() + b->GetNumber());
  return res;
}

int TMinus::Priority()
{
  return 2;
}

IOper* TMinus::Calc(IOper* a, IOper* b)
{
  TNum* res = new TNum(a->GetNumber() - b->GetNumber());
  return res;
}

int TMultiplication::Priority()
{
  return 3;
}

IOper* TMultiplication::Calc(IOper* a, IOper* b)
{
  TNum* res = new TNum(a->GetNumber() * b->GetNumber());
  return res;
}

int TDivision::Priority()
{
  return 3;
}

IOper* TDivision::Calc(IOper* a, IOper* b)
{
  if (b->GetNumber() == 0)
    throw - 2;
  TNum* res = new TNum(a->GetNumber() / b->GetNumber());
  return res;
}

int TOpenBracket::Priority()
{
  return 1;
}

IOper* TOpenBracket::Calc(IOper* a, IOper* b)
{
  throw - 1;
}

int TCloseBracket::Priority()
{
  return 0;
}

IOper* TCloseBracket::Calc(IOper* a, IOper* b)
{
  throw - 1;
}