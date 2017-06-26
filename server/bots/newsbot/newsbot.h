//Author: Parpibaev Artur
//Typical RSS bot with few settings
//For now database is not connected, sorry ;(
#include <../../../libraries/tinyxml/tinyxml.cpp>
#include <../../../libraries/tinyxml/tinyxml.h>
#include <../../../libraries/tinyxml/tinyxmlerror.cpp>
#include <../../../libraries/tinyxml/tinyxmlparser.cpp>
#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <vector>
#include <ctime>
class Newsbot
{	
   public:
	Newsbot();
	//Приветственное сообщение
	std::string Hello();
	//менеджер комманд и менеджер настроек
	bool CommandManager(std::string command);
	bool SettingsManager();
	//команды
	bool AddUrl();
	void DeleteUrl();
	void HelpInfo();
	//работа со временем
	std::time_t DateToTime(int year, int month, int day);
	std::time_t DateParse(const std::string &pubDate);
	//парсинг xml файла
	std::vector< std::vector< std::string > > RssParse(TiXmlDocument &doc); //описание парсится пока с тегами((
	TiXmlDocument LoadFile(std::string &url);
	void ShowParsedResult(std::vector< std::vector<std::string> > ParsedDoc);
	//добавление в бд
	void DatabaseNewFeed(std::string &url);
	//обновление ленты
	void UpdateFeed(std::string &current_url);
	//настройки
	void ShowAllUrl();
	void set_period_time(int time);
   private:
	int period_time;
	std::string url; //test.xml file
};
