#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Source: http://code.runnable.com/VHb0hWMZp-ws1gAr/splitting-a-string-into-a-vector-for-c%2B%2B
vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  
  return internal;
}



class Game {

public:
  void sayHello(std::vector<std::string> * params);
  void sayBye(std::vector<std::string> * params);
  void go(std::vector<std::string> * params);


};


// Make type of command function pointer
typedef void (Game::*commandPointer)(std::vector<std::string> *);


void Game::sayHello(std::vector<std::string> * params) {
  cout << "Dude ... HELLLLLLOOOOO ......" << endl;
}

void Game::sayBye(std::vector<std::string> * params) {
  cout << "Dude ... BE GONEEEEE ......" << endl;
}

void Game::go(std::vector<std::string> * params) {
  if (params->size() >= 1) {
    cout << "Going to room " << (*params)[0] << endl;
  }
}

class Command {
  public:
    std::string key;
    commandPointer function;

  public:
    Command(std::string key, commandPointer function);
};

Command::Command(std::string key, commandPointer function) {
  this->key = key;
  this->function = function;
}


class CommandParser {

private:
  std::vector<Command *> commands;

  public:
    CommandParser();
    ~CommandParser();
    void registerCommand(std::string key, commandPointer function);
    Command * listen(Game * game);
};

CommandParser::CommandParser() {}


CommandParser::~CommandParser() {
  for (int i = 0; i < commands.size(); i++) {
    delete commands[i];
    commands[i] = NULL;
  }

  commands.clear();
}

void CommandParser::registerCommand(std::string key, commandPointer function) {
  Command * cmd = new Command(key, function);
  commands.push_back(cmd);
}

Command * CommandParser::listen(Game * game) {

  std::string line;
  std::getline(std::cin, line);

  // Tokenize
  vector<string> params = split(line, ' ');

  int i = 0;
  while (i < commands.size() &&
    commands[i]->key.compare(params[0]) != 0) {

    i++;
  }

  if (i < commands.size()) {
    cout << "Command found, You typed " << line << endl;
    params.erase(params.begin());   // Remove actual command


    commandPointer ptr = commands[i]->function;

    (*game.*ptr)(&params);
    // (*this.*(commands[i]->function(&params));
  } else {
    cout << "Unknown command" << endl;
  }


  return NULL;
}


int main(void) {

  CommandParser parser;
  Game game;

  parser.registerCommand("sayhello", &Game::sayHello);
  parser.registerCommand("saybye", &Game::sayBye);
  parser.registerCommand("go", &Game::go);

  parser.listen(&game);

  return 0;

} 