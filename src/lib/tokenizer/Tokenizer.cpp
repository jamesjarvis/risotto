//
// Created by rvigee on 10/1/19.
//

#include <string>
#include <utility>
#include <map>
#include <sstream>
#include "Tokenizer.h"
#include "SyntaxError.h"

Tokenizer::Tokenizer(std::string src) : src(std::move(src)) {}

std::vector<Token> Tokenizer::tokenize() {
    while (!isAtEnd()) {
        scan();
    }

    addToken(TOKEN_EOF);

    return tokens;
}

bool Tokenizer::isAtEnd() {
    return current >= src.length();
}

void Tokenizer::scan() {
    start = current;

    auto c = advance();
    switch (c) {
        case ' ':
        case '\r':
        case '\t':
            // Ignore whitespace.
            break;
        case '\n':
            nextLine();
            break;
        case '"':
            lexString();
            break;
        case '(':
            addToken(TokenType::LEFT_PAREN);
            break;
        case ')':
            addToken(TokenType::RIGHT_PAREN);
            break;
        case '{':
            addToken(TokenType::LEFT_CURLY);
            break;
        case '}':
            addToken(TokenType::RIGHT_CURLY);
            break;
        case '[':
            addToken(TokenType::LEFT_SQUARED);
            break;
        case ']':
            addToken(TokenType::RIGHT_SQUARED);
            break;
        case ',':
            addToken(TokenType::COMMA);
            break;
        case '.':
            addToken(TokenType::DOT);
            break;
        case '-':
            if (match('=')) {
                addToken(TokenType::MINUS_EQUAL);
            } else if (match('-')) {
                addToken(TokenType::MINUS_MINUS);
            } else {
                addToken(TokenType::MINUS);
            }
            break;
        case '+':
            if (match('=')) {
                addToken(TokenType::PLUS_EQUAL);
            } else if (match('+')) {
                addToken(TokenType::PLUS_PLUS);
            } else {
                addToken(TokenType::PLUS);
            }
            break;
        case '%':
            addToken(TokenType::PERCENT);
            break;
        case '&':
            addToken(match('&') ? TokenType::AND : TokenType::AMPERSAND);
            break;
        case '|':
            if (match('|')) {
                addToken(TokenType::OR);
            }
            break;
        case ';':
            addToken(TokenType::SEMICOLON);
            break;
        case ':':
            addToken(TokenType::COLON);
            break;
        case '*':
            addToken(match('=') ? TokenType::STAR_EQUAL : TokenType::STAR);
            break;
        case '?':
            addToken(TokenType::QUESTION_MARK);
            break;
        case '!':
            addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
            break;
        case '=':
            addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
            break;
        case '<':
            addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
            break;
        case '>':
            addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
            break;
        case '/':
            if (match('/')) {
                // A comment goes until the end of the line.
                while (!match('\n') && !isAtEnd()) advance();
            } else if (match('*')) {
                // Multiline comment
                while (!isAtEnd()) {
                    if (match('\n')) {
                        nextLine();
                    } else if (match('*')) {
                        if (match('/')) {
                            break;
                        }
                    } else {
                        advance();
                    }
                }
            } else if (match('=')) {
                addToken(TokenType::SLASH_EQUAL);
            } else {
                addToken(TokenType::SLASH);
            }
            break;

        default:
            if (isDigit(c)) {
                number();
            } else if (isAlpha(c)) {
                identifier();
            } else {
                std::stringstream ss;
                ss << "Unexpected character " << c;

                throw SyntaxError(ss.str(), new Position(line, column));
            }
    }
}

void Tokenizer::addToken(TokenType type) {
    addToken(type, "");
}

template<typename T>
TokenValue literalToTokenValue(T literal) {
    throw SyntaxError("Unhandled literal", new Position(0, 0));
}

template<>
TokenValue literalToTokenValue<int>(int literal) {
    return TokenValue{._int = literal};
}

template<>
TokenValue literalToTokenValue<std::string>(std::string literal) {
    return TokenValue{._str = literal.c_str()};
}

template<>
TokenValue literalToTokenValue<const char *>(const char *literal) {
    return TokenValue{._str = literal};
}

template<typename T>
void Tokenizer::addToken(TokenType type, T literal) {
    std::string lexeme = src.substr(start, current - start);
    tokens.emplace_back(type, literalToTokenValue(literal), lexeme, Position(line, column));
}

bool Tokenizer::match(char expected) {
    if (isAtEnd()) return false;
    if (src.at(current) != expected) return false;

    current++;
    return true;
}

void Tokenizer::lexString() {
    while (peek() != '"' && !isAtEnd()) {
        if (peek() == '\n') {
            nextLine();
        };
        advance();
    }

    // Unterminated string.
    if (isAtEnd()) {
        throw SyntaxError("Unterminated string", new Position(line, column));
    }

    // The closing ".
    advance();

    // Trim the surrounding quotes.
    auto value = src.substr(start + 1, current - 1 - (start + 1));
    addToken(TokenType::STRING, value);
}

bool Tokenizer::isDigit(char c) {
    return c >= '0' && c <= '9';
}

void Tokenizer::number() {
    bool isDecimal = false;
    while (isDigit(peek())) advance();

    // Look for a fractional part.
    if (peek() == '.' && isDigit(peekNext())) {
        isDecimal = true;

        // Consume the "."
        advance();

        while (isDigit(peek())) advance();
    }

    auto s = src.substr(start, current - start);

    if (isDecimal) {
        addToken(TokenType::DOUBLE, std::stod(s));
    } else {
        addToken(TokenType::INT, std::stoi(s));
    }
}

char Tokenizer::peek() {
    return peekN(0);
}

char Tokenizer::peekNext() {
    return peekN(1);
}

char Tokenizer::peekN(int n) {
    if (current + n >= src.length()) {
        return '\0';
    }

    return src.at(current + n);
}

bool Tokenizer::isAlpha(char c) {
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           c == '_';
}

std::map<std::string, TokenType> Tokenizer::keywords = {
        {"else",   TokenType::ELSE},
        {"false",  TokenType::FALSE},
        {"for",    TokenType::FOR},
        {"func",   TokenType::FUNC},
        {"if",     TokenType::IF},
        {"nil",    TokenType::NIL},
        {"print",  TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"this",   TokenType::THIS},
        {"new",    TokenType::NEW},
        {"true",   TokenType::TRUE},
        {"while",  TokenType::WHILE},
};

void Tokenizer::identifier() {
    while (isAlphaNumeric(peek())) advance();

    auto text = src.substr(start, current - start);

    TokenType type;
    if (keywords.find(text) == keywords.end()) {
        type = TokenType::IDENTIFIER;
    } else {
        type = keywords.at(text);
    }

    addToken(type, text);
}

bool Tokenizer::isAlphaNumeric(char c) {
    return isAlpha(c) || isDigit(c);
}


char Tokenizer::advance() {
    auto c = src.at(current);
    current++;
    column++;

    return c;
}

void Tokenizer::nextLine() {
    line++;
    column = 0;
}