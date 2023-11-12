#include "CompilerParser.h"
#include <iostream>
using namespace std;



CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
    this->currentToken = this->tokens.begin();
}


ParseTree* CompilerParser::compileProgram() {
    ParseTree* program = new ParseTree("class", "");
   
    if (have("keyword", "class")) {
        program->addChild(new ParseTree("keyword", "class"));
        next();
    } else {
        throw ParseException();
    }
    
    
    if (have("identifier", current()->getValue())) {
        program->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    
    if (have("symbol", "{")) {
        program->addChild(new ParseTree("symbol", "{"));
        next();
    } else {
        throw ParseException();
    }

    if (have("symbol", "}")) {
        program->addChild(new ParseTree("symbol", "}"));
    } else {
        throw ParseException();
    }

    return program;
}

ParseTree* CompilerParser::compileClass() {
    ParseTree* class1 = new ParseTree("class", "");

      if (have("keyword", "class")) {
        class1->addChild(new ParseTree("keyword", "class"));
        next();
    } else {
        throw ParseException();
    }

    if (have("identifier", current()->getValue())) {
        class1->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    if (have("symbol", "{")) {
        class1->addChild(new ParseTree("symbol", "{"));
        next();
    } else {
        throw ParseException();
    }

    class1->addChild(compileClassVarDec());
    


    if (have("symbol", "}")) {
        class1->addChild(new ParseTree("symbol", "}"));
    } else {
        throw ParseException();
    }


    

    return class1;
}


ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* classVarDec = new ParseTree("classVarDec", "");

    if (have("keyword", "static")) {
        classVarDec->addChild(new ParseTree("keyword", "static"));
        next();
    } else {
        throw ParseException();
    }

    
    if (have("keyword", "int")) {
        classVarDec->addChild(new ParseTree("keyword", "int"));
        next();
    } else {
        throw ParseException();
    }

    
    if (have("identifier", current()->getValue())) {
        classVarDec->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

   
    if (have("symbol", ";")) {
        classVarDec->addChild(new ParseTree("symbol", ";"));
        next();
    } else {
        throw ParseException();
    }

    return classVarDec;
}


ParseTree* CompilerParser::compileSubroutine() {
    return NULL;
}


ParseTree* CompilerParser::compileParameterList() {
    ParseTree* parameter = new ParseTree("parameterList", "");

    if (have("keyword", "int")) {
        parameter->addChild(new ParseTree("keyword", "int"));
        next();
    } else {
        throw ParseException();
    }

    if (have("identifier", current()->getValue())) {
        parameter->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    if (have("symbol", ",")) {
        parameter->addChild(new ParseTree("symbol", ","));
        next();
    } else {
        throw ParseException();
    }



    if (have("keyword", "char")) {
        parameter->addChild(new ParseTree("keyword", "char"));
        next();
    } else {
        throw ParseException();
    }

    if (have("identifier", current()->getValue())) {
        parameter->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }
    return parameter;
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* vardec = new ParseTree("VarDec", "");

    if (have("keyword", "var")) {
        vardec->addChild(new ParseTree("keyword", "var"));
        next();
    } else {
        throw ParseException();
    }

    if (have("keyword", "int")) {
        vardec->addChild(new ParseTree("keyword", "int"));
        next();
    } else {
        throw ParseException();
    }

    if (have("identifier", current()->getValue())) {
        vardec->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    if (have("symbol", ";")) {
        vardec->addChild(new ParseTree("symbol", ";"));
    } else {
        throw ParseException();
    }




   

   
    return vardec;
    return NULL;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
      if (currentToken != tokens.end()) {
            ++currentToken;
            }
    return;
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    if (currentToken != tokens.end()) {
               return *currentToken;
            }
    return NULL;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
     if (currentToken != tokens.end() && (*currentToken)->getType() == expectedType && (*currentToken)->getValue() == expectedValue) {
        return true;
         }
    else{
    return false;
    }
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if (have(expectedType, expectedValue)) {
        Token* token = *currentToken;
        next();
        return token;
            } else {
        throw ParseException();
        }
    return NULL;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
