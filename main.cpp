#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

// Make type of command function pointer
typedef void (*commandPointer)(std::vector<std::string> *);

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


void sayHello(std::vector<std::string> * params) {
  cout << "Dude ... HELLLLLLOOOOO ......" << endl;
}

void sayBye(std::vector<std::string> * params) {
  cout << "Dude ... BE GONEEEEE ......" << endl;
}

void go(std::vector<std::string> * params) {
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
    Command * listen(void);
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

Command * CommandParser::listen(void) {

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
    commands[i]->function(&params);
  } else {
    cout << "Unknown command" << endl;
  }


  return NULL;
}


int main(void) {

  CommandParser parser;

  parser.registerCommand("sayhello", sayHello);
  parser.registerCommand("saybye", sayBye);
  parser.registerCommand("go", go);

  parser.listen();

  return 0;

} 