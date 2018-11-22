#pragma once
#include <string>
#include <vector>

class SpaceController {
 private:
  size_t ClassCounter = 0;

 public:
  void BeginClass() { ++ClassCounter; }

  void EndClass() {
    if (ClassCounter > 0) {
      --ClassCounter;
    }
  }

  std::string AccessModifier() const {
    return std::string(2 * ClassCounter + 2 * (ClassCounter - 1), ' ');
  }

  std::string Declaration() const { return std::string(4 * ClassCounter, ' '); }
};

class FormatVisitor : public BaseVisitor {
 private:
  std::vector<std::string> Result;
  SpaceController Spaces;

  // Flags
  bool IsArgument = false;
  bool WasFirstArgument = false;
  std::string ArgBuffer;

 public:
  void Visit(const BaseNode *const node) override { node->Visit(this); }

  void Visit(const ClassDeclarationNode *const node) override {
    Result.emplace_back(Spaces.Declaration() + "class " + node->ClassName() +
                        " {");
    Spaces.BeginClass();

    const auto pub = node->PublicFields();
    if (!empty(pub)) {
      Result.emplace_back(Spaces.AccessModifier() + "public:");
      for (const auto i : pub) {
        i->Visit(this);
      }
    }

    const auto prot = node->ProtectedFields();
    if (!empty(prot)) {
      if (!empty(pub)) {
        Result.emplace_back("");
      }
      Result.emplace_back(Spaces.AccessModifier() + "protected:");
      for (const auto i : prot) {
        i->Visit(this);
      }
    }

    const auto priv = node->PrivateFields();
    if (!empty(priv)) {
      if (!empty(prot)) {
        Result.emplace_back("");
      }
      Result.emplace_back(Spaces.AccessModifier() + "private:");
      for (const auto i : node->PrivateFields()) {
        i->Visit(this);
      }
    }

    Spaces.EndClass();
    Result.emplace_back(Spaces.Declaration() + "};");
  }

  void Visit(const VarDeclarationNode *const node) override {
    const auto var = node->TypeName() + ' ' + node->VarName();
    if (IsArgument) {
      if (WasFirstArgument) {
        ArgBuffer += ", ";
      }
      ArgBuffer += var;
      WasFirstArgument = true;
    } else {
      Result.emplace_back(Spaces.Declaration() + var + ';');
    }
  }

  void Visit(const MethodDeclarationNode *const node) override {
    IsArgument = true;
    ArgBuffer = Spaces.Declaration() + node->ReturnTypeName() + ' ' +
                node->MethodName() + '(';
    for (const auto i : node->Arguments()) {
      i->Visit(this);
    }
    ArgBuffer += ");";
    Result.push_back(std::move(ArgBuffer));
    IsArgument = false;
    WasFirstArgument = false;
  }

  const std::vector<std::string> &GetFormattedCode() const { return Result; }
};
