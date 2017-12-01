#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
enum Command{NotValid, AddNote, DeleteNote, ShowAllNotes};
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
private:
    std::string name;//Имя заметки
    Command command;
    std::string text;
public:
    bool isFull();//Все поля Message заполнены


};
bool Message::isFull()
{
    if(command) return true;
    else return false;
}
class Controller
{
private:
    int chatID;
    //bdConn bd;
    //для БД: string SwitchCommand()
    //string reparseAnswer()
public:
    void parseJSON();
    std::string formJSON(std::string);//Ответ клиенту(отправляется на сервер)
    //Add(insert) - OK,  ожидание строки и т.д..


};
int main()
{

    json j3 =R"({"Andrey":"text"})"_json;
    json j4 = R"({"update_id":869449690,
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
                   "text":"privet"}})"_json;

std::cout<<j4["message"]["text"]<<std::endl;//Вывод текста
    return 0;
}