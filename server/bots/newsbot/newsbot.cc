#include "newsbot.h"

std::time_t Newsbot::DateToTime(int year, int month, int day) {
	tm tmp = tm();
	tmp.tm_mday = day;
	tmp.tm_mon = month-1;
	tmp.tm_year = year - 1900; // дать имя магическим константам
	return mktime(&tmp);
}

 Newsbot::Newsbot() {
 	period_time = 600;
 }

void Newsbot::DatabaseNewFeed(std::string &url) {
	
	//добавляем в бд новую строчку url для конкретной "комнаты"
}


void Newsbot::UpdateFeed(std::string &current_url){
	TiXmlDocument doc = LoadFile(current_url);
	ShowParsedResult( RssParse(doc) );

}

void Newsbot::set_period_time(int time) {
	period_time = time;
}

std::vector< std::vector<std::string> > Newsbot::RssParse(TiXmlDocument &doc) {
	 TiXmlElement* root = doc.FirstChildElement("rss")->FirstChildElement("channel")->FirstChildElement("item");	
	 std::vector<std::string> single_news(4);
	 std::vector< std::vector<std::string> > all_news; 

	 if(!root) {
	 	std::cout << "Не удалось распознать XML файл\n";
	 	single_news[0] = "";
	 	all_news.push_back(single_news);
	 	return all_news;
	 }
 
	 bool time_check = true;
     
     while(time_check == true && root != NULL) {
         const std::string title = root->FirstChildElement("title")->GetText();
         const std::string link = root->FirstChildElement("link")->GetText();
         const std::string description = root->FirstChildElement("description")->GetText();
         const std::string pubDate = root->FirstChildElement("pubDate")->GetText();
         
         std::time_t pubDate_t = DateParse(pubDate);
         auto current_time = std::chrono::system_clock::now();
         std::time_t current_time_t = std::chrono::system_clock::to_time_t(current_time);
         //if(current_time_t - period_time*60 < pubDate_t){
         //	time_check = false;
         //} else {
         	single_news[0] = title;
         	single_news[1] = link;
         	single_news[2] = description;
         	single_news[3] = pubDate;
         	all_news.push_back(single_news);
         //}  
         time_check = false;
         root = root->NextSiblingElement("item");
     }

     return all_news;
}

std::time_t Newsbot::DateParse(const std::string &pubDate) {
	char week[4], ch_month[5], time_zone[5];
	int day, year, hour, minute, second;
	std::sscanf(pubDate.c_str(), "%[A-Za-z], %d %[A-Za-z] %d %d:%d:%d %s", &week, &day, &ch_month, &year, &hour, &minute, &second, &time_zone);
	std::string month(ch_month);
	std::map <std::string, int> mapping;
	std::map <std::string, int>::iterator it;
	

	mapping["Jan"] = 1;
	mapping["Feb"] = 2;
	mapping["Mar"] = 3;
	mapping["Apr"] = 4;
	mapping["May"] = 5;
	mapping["Jun"] = 6;
	mapping["Jul"] = 7;
	mapping["Aug"] = 8;
	mapping["Sept"] = 9;
	mapping["Oct"] = 10;
	mapping["Nov"] = 11;
	mapping["Dec"] = 12;
	
	int month_t = 0;
	
	it = mymap.find(month);
	if (it != mymap.end()){
	  month_t = it->second;
	} else {
	  std::cout << "Месяц не распознан"<< std::endl;
	  return 0;
	}

	DatabaseNewFeed(url);
	
	std::cout << "Хотите увидеть новости за последнее время?\n"; 
	std::string last_news_choice;
	std::cin >> last_news_choice;
	if (last_news_choice == "y" || last_news_choice == "\n") {
		UpdateFeed(url);
	}
	return 0;
}

TiXmlDocument Newsbot::LoadFile(std::string &new_url) {
	TiXmlDocument doc(new_url);
	bool isOkay = doc.LoadFile();
	if(isOkay){
		return doc;
	} else {
		return 0;
	}
}

std::string Newsbot::Hello() {
	std::string command;
	std::cout << "Привет! Введи команду или посмотри их список с помощью /Nhelp" << std::endl;
	std::cin >> command;
	return command;
}

bool Newsbot::CommandManager(std::string command) {
	std::map <std::string, int> mapping;
	mapping["/Nhelp"] = 1;
	mapping["/Nadd"] = 2;
	mapping["/Nsettings"] = 3;
	mapping["/Ndelete"] = 4;

	bool back_to_settings = true, back_to_add_url = true;
	switch(mapping[command]) {
		case 1: HelpInfo();
				return 1;
		case 2: while (back_to_add_url) {
					back_to_add_url = AddUrl();
				}
				return 1;
		case 3: while(back_to_settings){
					back_to_settings = SettingsManager();
				}
				return 1;
		case 4: DeleteUrl();
				return 1;
		default: std::cout << "Похоже, вы ввели не команду!"<< std::endl;
				 return 0;
	}
	return 0;
}

bool Newsbot::SettingsManager() {
	std::cout << "Вы можете изменить следующие параметры (нажмите цифру для соответствующего выбора):\n";
	std::cout << "1. Установить время обновления новостей (минуты): " << period_time << " minute" << std::endl;
	std::cout << "2. Показать все доступные новостные ленты." << std::endl;
	int choice = 0;
	std::cin >> choice;
	switch(choice){
		case 1: std::cout << "Введите время обновления в минутах: \n";
				int temp_time;
				std::cin >> temp_time;
				if(temp_time > 1440){
					std::cout << "Время обновления не может быть больше 24ч";
					return 1;
				}
				set_period_time(temp_time);
				return 1;
		case 2: ShowAllUrl();
				return 1;
		default: break;
	}
	return 0;
}

void Newsbot::ShowAllUrl() {
	std::cout << url << std::endl;
	//запррс в бд select * from RSS.URL_adress;
}

void Newsbot::DeleteUrl(){
	ShowAllUrl();
	std::string some_url;
	std::cout << "Напишите название url который вы хотите удалить:\n";
	std::cin >> some_url;
	//проверка есть ли такой url в бд select URL from RSS.URL_adress where URL = some_url;
	//если есть, то удаление, если нет, то сообщение об ошибке и возврат к настройкам
	//удаление из бд delete from RSS.URL_adress where URL = some_url;
}

int main(){
	Newsbot newsbot;
	while(true){
		bool NeedCommand = true;
		while(NeedCommand){
			NeedCommand = newsbot.CommandManager(newsbot.Hello());
		}
	}
	return 0;
}
