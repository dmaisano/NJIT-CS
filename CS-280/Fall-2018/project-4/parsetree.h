/*
 * parsetree.h
 */

#ifndef PARSETREE_H_
#define PARSETREE_H_

#include "lexer.h"
#include "value.h"
#include <map>
#include <vector>
using namespace std;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE, BOOLTYPE };

extern map<string, Value> symbols;
extern void RunTimeError(string);
// a "forward declaration" for a class to hold values
class Value;

class ParseTree {
  int linenum;

protected:
  ParseTree *left;
  ParseTree *right;

public:
  ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0) : linenum(linenum), left(l), right(r) {}

  virtual ~ParseTree() {
    delete left;
    delete right;
  }

  int GetLinenum() const { return linenum; }

  virtual NodeType GetType() const { return ERRTYPE; }

  int LeafCount() const {
    int lc = 0;
    if (left)
      lc += left->LeafCount();
    if (right)
      lc += right->LeafCount();
    if (left == 0 && right == 0)
      lc++;
    return lc;
  }

  virtual bool IsIdent() const { return false; }
  virtual bool IsString() const { return false; }

  virtual string GetId() const { return ""; }

  int IdentCount() const {
    int cnt = 0;
    if (left)
      cnt += left->IdentCount();
    if (right)
      cnt += right->IdentCount();
    if (IsIdent())
      cnt++;
    return cnt;
  }

  int StringCount() const {
    int cnt = 0;
    if (left)
      cnt += left->StringCount();
    if (right)
      cnt += right->StringCount();
    if (IsString())
      cnt++;
    return cnt;
  }

  void GetVars(map<string, int> &var) {
    if (left)
      left->GetVars(var);
    if (right)
      right->GetVars(var);
    if (IsIdent())
      var[this->GetId()]++;
  }

  virtual Value Eval() { return Value(); }
};

class StmtList : public ParseTree {

public:
  StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}

  Value Eval() {
    left->Eval();
    if (right) {
      right->Eval();
    }

    return Value();
  }
};

class IfStatement : public ParseTree {
public:
  IfStatement(int line, ParseTree *ex, ParseTree *stmt) : ParseTree(line, ex, stmt) {}

  Value Eval() {
    Value v = left->Eval();
    if (v.isBoolType() == true) {
      if (v.getBoolean()) {
        return right->Eval();
      }
    } else {
      RunTimeError("if expression is not boolean typed");
    }
    return Value();
  }
};

class Assignment : public ParseTree {
public:
  Assignment(int line, ParseTree *lhs, ParseTree *rhs) : ParseTree(line, lhs, rhs) {}
  // eval expression then add to symbols
  Value Eval() {

    if (left->IsIdent()) {

      Value r = right->Eval();
      string l = left->GetId();
      symbols[l] = r;
      return r;
    } else {
      RunTimeError("Isn't an identifier");
    }
    return Value();
  }
};

class PrintStatement : public ParseTree {
public:
  PrintStatement(int line, ParseTree *e) : ParseTree(line, e) {}

  // eval then cout
  Value Eval() override {
    Value v = left->Eval();
    if (v.isIntType()) {
      cout << v.getInteger() << endl;
    } else if (v.isStringType()) {
      cout << v.getString() << endl;
    } else if (v.isBoolType()) {
      cout << v << endl;
    }
    return Value();
  }
};

class PlusExpr : public ParseTree {
public:
  PlusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  Value Eval() {
    auto r = right->Eval();
    auto l = left->Eval();
    return l + r;
  }
};

class MinusExpr : public ParseTree {
public:
  MinusExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  Value Eval() {
    auto r = right->Eval();
    auto l = left->Eval();
    return l - r;
  }
};

class TimesExpr : public ParseTree {
public:
  TimesExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  Value Eval() {
    auto r = right->Eval();
    auto l = left->Eval();
    return l * r;
  }
};

class DivideExpr : public ParseTree {
public:
  DivideExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  Value Eval() {
    auto r = right->Eval();
    auto l = left->Eval();
    return l / r;
  }
};

class LogicAndExpr : public ParseTree {
public:
  LogicAndExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  NodeType GetType() const { return BOOLTYPE; }

  Value Eval() {
    Value r = right->Eval();
    Value l = left->Eval();

    if (r.isBoolType() && l.isBoolType()) {
      return r.isTrue() && l.isTrue();
    } else {
      RunTimeError("First operator not boolean");
    }
    return Value();
  }
};

class LogicOrExpr : public ParseTree {
public:
  LogicOrExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  NodeType GetType() const { return BOOLTYPE; }

  Value Eval() {
    Value r = right->Eval();
    Value l = left->Eval();

    if (r.isBoolType() || l.isBoolType()) {
      return r.isTrue() || l.isTrue();
    }

    else {
      RunTimeError("First operator not boolean");
    }
    return Value();
  }
};

class EqExpr : public ParseTree {
public:
  EqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  NodeType GetType() const { return BOOLTYPE; }

  Value Eval() { return right->Eval() == left->Eval(); }
};

class NEqExpr : public ParseTree {
public:
  NEqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  NodeType GetType() const { return BOOLTYPE; }

  Value Eval() { return right->Eval() != left->Eval(); }
};

class LtExpr : public ParseTree {
public:
  LtExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  Value Eval() { return right->Eval() < left->Eval(); }

  NodeType GetType() const { return BOOLTYPE; }
};

class LEqExpr : public ParseTree {
public:
  LEqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  Value Eval() { return right->Eval() <= left->Eval(); }

  NodeType GetType() const { return BOOLTYPE; }
};

class GtExpr : public ParseTree {
public:
  GtExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  Value Eval() { return right->Eval() > left->Eval(); }

  NodeType GetType() const { return BOOLTYPE; }
};

class GEqExpr : public ParseTree {
public:
  GEqExpr(int line, ParseTree *l, ParseTree *r) : ParseTree(line, l, r) {}

  Value Eval() { return right->Eval() >= left->Eval(); }

  NodeType GetType() const { return BOOLTYPE; }
};

class IConst : public ParseTree {
  int val;

public:
  IConst(int l, int i) : ParseTree(l), val(i) {}
  IConst(Token &t) : ParseTree(t.GetLinenum()) { val = stoi(t.GetLexeme()); }

  NodeType GetType() const { return INTTYPE; }

  Value Eval() { return Value(val); }
};

class BoolConst : public ParseTree {
  bool val;

public:
  BoolConst(Token &t, bool val) : ParseTree(t.GetLinenum()), val(val) {}

  NodeType GetType() const { return BOOLTYPE; }
  Value Eval() { return Value(val); }
};

class SConst : public ParseTree {
  string val;

public:
  SConst(Token &t) : ParseTree(t.GetLinenum()) { val = t.GetLexeme(); }

  NodeType GetType() const { return STRTYPE; }
  bool IsString() const { return true; }

  Value Eval() { return Value(val); }
};

class Ident : public ParseTree {
  string id;

public:
  Ident(Token &t) : ParseTree(t.GetLinenum()), id(t.GetLexeme()) {}

  bool IsIdent() const { return true; }
  string GetId() const { return id; }

  Value Eval() {
    if (!symbols.empty() && symbols.count(id)) {
      return symbols[id];
    } else {
      RunTimeError("Variable is already in map");
      return Value();
    }
    return Value();
  }
};

#endif /* PARSETREE_H_ */
