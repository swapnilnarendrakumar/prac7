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

    if (have("keyword", "static") || have("keyword", "field")) {
        classVarDec->addChild(new ParseTree("keyword", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    if (have("keyword", "int") || have("keyword", "char") || have("keyword", "boolean") || have("identifier", current()->getValue())) {
        classVarDec->addChild(new ParseTree("keyword", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    do {
        if (have("identifier", current()->getValue())) {
            classVarDec->addChild(new ParseTree("identifier", current()->getValue()));
            next();
        } else {
            throw ParseException();
        }

        if (have("symbol", ",")) {
            classVarDec->addChild(new ParseTree("symbol", ","));
            next();
        } else if (have("symbol", ";")) {
            classVarDec->addChild(new ParseTree("symbol", ";"));
        } else {
            throw ParseException();
        }
    } while (!have("symbol", ";"));

    return classVarDec;

    
    return NULL;
}


ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* subroutine = new ParseTree("subroutine", "");

    if (have("keyword", "int")) {
        subroutine->addChild(new ParseTree("keyword", "function"));
        next();
    } else {
        throw ParseException();
    }

    if (have("keyword", "int")) {
        subroutine->addChild(new ParseTree("keyword", "void"));
        next();
    } else {
        throw ParseException();
    }

    if (have("identifier", current()->getValue())) {
        subroutine->addChild(new ParseTree("identifier", current()->getValue()));
        next();
    } else {
        throw ParseException();
    }

    if (have("symbol", "{")) {
        subroutine->addChild(new ParseTree("symbol", "{"));
        next();
    } else {
        throw ParseException();
    }



    return NULL;
}


ParseTree* CompilerParser::compileParameterList() {
     ParseTree* parameterList = new ParseTree("parameterList", "");

    bool firstParameter = true; 

    while (true) {
        if (firstParameter || have("symbol", ",")) {
           
            if (!firstParameter) {
                parameterList->addChild(new ParseTree("symbol", ","));
                next();
            }

           
            if (have("keyword", "int") || have("keyword", "char") || have("keyword", "boolean") || have("identifier", current()->getValue())) {
                parameterList->addChild(new ParseTree("keyword", current()->getValue()));
                next();
            } else {
                throw ParseException();
            }

          
            if (have("identifier", current()->getValue())) {
                parameterList->addChild(new ParseTree("identifier", current()->getValue()));
                next();
            } else {
                throw ParseException();
            }

            firstParameter = false;
        } else {
         
            break;
        }
    }

    return parameterList;
    return NULL;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    return NULL;
}


ParseTree* CompilerParser::compileVarDec() {
   ParseTree* vardec = new ParseTree("varDec", "");

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

    do {
        if (have("identifier", current()->getValue())) {
            vardec->addChild(new ParseTree("identifier", current()->getValue()));
            next();
        } else {
            throw ParseException();
        }

        if (have("symbol", ",")) {
            vardec->addChild(new ParseTree("symbol", ","));
            next();
        } else if (have("symbol", ";")) {
            vardec->addChild(new ParseTree("symbol", ";"));
        } else {
            throw ParseException();
        }
    } while (!have("symbol", ";"));

    return vardec;
   

   
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
    ParseTree* dost = new ParseTree("doStatement", "");
    if (have("keyword", "do")) {
        dost->addChild(current());
        next();
    } else {
        throw ParseException();
    }

    while (have("keyword", "skip")) {
        ParseTree* expression = compileExpression();
        dost->addChild(expression);
        next();
    }

    if (have("symbol", ";")) {
        dost->addChild(current());
        next();
    } else {
        throw ParseException();
    }



    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* return1 = new ParseTree("returnStatement", "");
    if (have("keyword", "return")) {
        return1->addChild(current());
        next();
    } else {
        throw ParseException();
    }

    while (have("keyword", "skip")) {
        ParseTree* expression = compileExpression();
        return1->addChild(expression);
        next();
    }


    if (have("symbol", ";")) {
        return1->addChild(current());
        next();
    } else {
        throw ParseException();
    }
    return return1;
    
}


ParseTree* CompilerParser::compileExpression() {
    ParseTree* expression = new ParseTree("expression", "");

    if (have("keyword", "skip")) {
        expression->addChild(current());
    } else {
        throw ParseException();
    }
    return expression;
   
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
