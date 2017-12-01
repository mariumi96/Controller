#include <iostream>
#include<cassert>
#include "json.hpp"
using json = nlohmann::json;
//enum Command{NotValid, AddNote, DeleteNote, ShowAllNotes};
/*class Command
{
private:
    std::string commandName;
public:
    bool isValid(std::string InputStr);

};
bool Command::isValid(std::string InputStr)
{

}*/
class Message
{
public:
    bool isFull();//Все поля Message заполнены
    bool setCommand(std::string com);
    void setText(std::string text);
    bool isWaitingText();
    std::string getCommand();
    std::string getText();
private:
    //std::string name;//Имя заметки
    std::string command;
    std::string text;
    bool fullness = false;
    bool waitingText = false;

};
bool isCommand(std::string com)
{
    if(com == "/AddNote" || com == "/DeleteNote") return true;
    return false;
}
std::string Message::getCommand()
{
    assert(isWaitingText()||isFull());
    return command;
}
std::string Message::getText()
{
    assert(isFull());
    return text;
}
bool Message::setCommand(std::string com)
{
    if(isCommand(com))
    {
        this->command = com;
        this->waitingText = true;
        return true;
    }
    return false;
}
bool Message::isFull()
{
    return fullness;
}
bool Message::isWaitingText()
{
    return waitingText;
}
void Message::setText(std::string text)
{
    this->text = text;
    this->fullness = true;
    this->waitingText = false;
}
class Controller
{

public:
    Controller(int id, json input)
    {
        chatID = id;
        std::string command = parseJSON(input);
        //json reparseAnswer(); Ответ на сервер
        if(textMessage.setCommand(command)) std::cout<<"Success! Waiting for text!"<<std::endl;
        else std::cout<<"Invalid command!"<<std::endl;
    };
    std::string parseJSON(json jsonToParse);
    json reparseAnswer();
    void messageInfo();
    //std::string formJSON(std::string);//Ответ клиенту(отправляется на сервер)
    //Add(insert) - OK,  ожидание строки и т.д..
private:
    int chatID;
    Message textMessage;
    //bdConn bd;
    //для БД: string SwitchCommand()
    //string reparseAnswer()

};
std::string Controller::parseJSON(json jsonToParse)
{
    std::string gotText = jsonToParse["message"]["text"];
    if(!textMessage.isWaitingText())
    {
        return gotText;
    }
    textMessage.setText(gotText);
    return gotText;

}

void Controller::messageInfo()
{
    std::cout<<"Waiting for text : "<<std::boolalpha<<textMessage.isWaitingText()<<std::endl;
    if(textMessage.isWaitingText()||textMessage.isFull()) std::cout<<"Command : "<<textMessage.getCommand()<<std::endl;
    std::cout<<"Is full(command got correctly, text got) : "<<std::boolalpha<<textMessage.isFull()<<std::endl;
    if(textMessage.isFull()) std::cout<<"Text : "<<textMessage.getText()<<std::endl;
}
int main()
{
    json j1 = R"({"update_id":869449690,
                    "message":
                 {"message_id":1081,
                    "from":
                 {"id":225462148,
                  "is_bot":false,
                  "first_name":"Andrey\ud83c\ude35",
                  "username":"Andreynnt",
                  "language_code":"en"},
                     "chat":
                  {"id":225462148,
                   "first_name":"Andrey\ud83c\ude35",
                   "username":"Andreynnt",
                   "type":"private"},

                   "date":1510990738,
                   "text":"/AddNote"}})"_json;

    std::cout<<j1["message"]["text"]<<std::endl;//Вывод текста
    int chatID = j1["message"]["chat"]["id"];

    Controller controller(chatID,j1);

    json j2 = R"({"update_id":869449690,
                    "message":
                 {"message_id":1081,
                    "from":
                 {"id":225462148,
                  "is_bot":false,
                  "first_name":"Andrey\ud83c\ude35",
                  "username":"Andreynnt",
                  "language_code":"en"},
                     "chat":
                  {"id":225462148,
                   "first_name":"Andrey\ud83c\ude35",
                   "username":"Andreynnt",
                   "type":"private"},

                   "date":1510990738,
                   "text":"Text of the note"}})"_json;

    std::string result = controller.parseJSON(j2);
    controller.messageInfo();
    return 0;
}