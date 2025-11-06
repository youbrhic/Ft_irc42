/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:26:44 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/04 16:09:58 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bot.hpp"

bot::bot(int serverport, char *hostname, char *password)
{
	this->serverport = serverport;
	this->indexquiz = 0;
	this->serverhostname = hostname;
	this->password = password;
	this->fdsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->fdsocket < 0)
        throw std::runtime_error("socket() failed");
}

void	bot::connecttoserver()
{
	struct hostent		*server;
	struct sockaddr_in	serv_addr;

	fdsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (fdsocket < 0)
        throw std::runtime_error("socket() failed");
	server = gethostbyname(serverhostname);
	if (!server)
		throw std::runtime_error("gethostbyname() failed");
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serverport);
	if (connect(fdsocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		throw std::runtime_error("connect() failed");
}

void	bot::authenticate(std::string user, std::string nickname)
{
	std::string	cmds[3] = {"PASS ", "USER ", "NICK "};
	std::string	info[3] = {std::string(password), user, nickname};
	std::string	message;
	int			i;

	i = -1;
	while (++i < 3)
	{
		message = cmds[i] + info[i] + "\r\n";
		if (send(fdsocket, message.c_str(), message.length(), 0) < 0)
			throw std::runtime_error("send() failed");
		usleep(90);
	}
}

std::string	getmessage(std::string recevdata)
{
	std::string	message;
	int			i;

	i = (recevdata.substr(1, recevdata.size())).find(":");
	message = recevdata.substr(i + 2, recevdata.size());
	while ((message[message.size() - 1] == '\n' || message[message.size() - 1] == '\r'))
        message.erase(message.size() - 1);
	return (message);
}

std::string	getSenderNickname(std::string recevdata)
{
	int			i;
	std::string	nickname;

	i = 0;
	while (recevdata[++i])
	{
		if (!std::isalnum(recevdata[i]))
			break ;
	}
	if (!std::isalnum(recevdata[i]))
		i--;
	nickname = recevdata.substr(1, i);
	return (nickname);
}

void	bot::sendRepone(int sockfd, std::string message, std::string senderNickname)
{
	if (senderNickname == "IRCServer")
		return ;
	if (message == "game" || message == "GAME" || getplayer(senderNickname) != players.end())
		playgame(sockfd, message, senderNickname);
	else
	{
		std::string  reponse = "PRIVMSG " + senderNickname + " : ";
		reponse += "\x03" "12 Hi Mr " + senderNickname + " , if you want to play Quiz Emoji game, send`game` or `GAME` " + "\r\n";
		std::cout << "reponse : " << reponse << "\n";
		if (send(sockfd, reponse.c_str(), reponse.size(), 0) < 0)
			return;
	}
}

void	bot::startbot()
{
	char 				buffer[512];
	std::string			message;
	std::string			senderNickname;

    while (true)
    {
        int bytesRead = recv(fdsocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0)
        {
            std::cerr << "Disconnected from server or error reading data" << std::endl; break;
        }
		buffer[bytesRead] = '\0';
		std::cout << buffer << '\n';
		message = getmessage(std::string(buffer));
		senderNickname = getSenderNickname(std::string(buffer));
		sendRepone(fdsocket, message, senderNickname);
    }
}

void	bot::init()
{
	connecttoserver();
	authenticate(std::string("bot bot bot bot "), std::string("bot"));
	startbot();
}

std::vector<player>::iterator	bot::getplayer(std::string nickname)
{
	std::vector<player>::iterator	it;

	it = this->players.begin();
	while (it != this->players.end())
	{
		if (it->nickname == nickname)
			return (it);
		it++;
	}
	return (this->players.end());
}

std::vector<std::string>	splitword(const std::string& input)
{
	std::vector<std::string> result;
    std::string line;
    std::istringstream stream(input);

    while (std::getline(stream, line, '\n'))
	{
        if (!line.empty())
            result.push_back(line);
    }
    return result;
}

void	sendQuations(int fdsocket, std::string reponse, QuizQuestion quiz)
{
	int								orderOfranswer;
	std::string						answers[3];
	std::string						sendone;
	std::string						firstsend;
	std::string						sendmessage[4];

	srand(time(NULL));
	firstsend = reponse;
	orderOfranswer = rand() % 3;
	sendmessage[0] = std::string("what is this ") + quiz.emojis + "\r\n";
	for (int i = 0; i < 3 ; i++)
		answers[i] = quiz.wrong_answers[i];
	answers[orderOfranswer] = quiz.correct_answer;
	for(int i = 0,  j = 1; i < 3 ; i++, j++)
		sendmessage[j] = answers[i];
	for (int i = 0 ; i < 4 ; i ++)
	{
		sendone = reponse + sendmessage[i] + "\r\n";
		std::cout << "sendone |" << sendone << "|\n";
		if (send(fdsocket, sendone.c_str(), sendone.size(), 0) < 0)
			return ;
		usleep(50);
	}
}

void	bot::playgame(int fdsocket, std::string message, std::string senderNickname)
{
	std::string 					reponse = "PRIVMSG " + senderNickname + " : ";
	QuizQuestion					quiz[] = QUIZ_QUESTIONS_DATA;
	player							p;
	int								index;
	std::vector<player>::iterator	it;

	srand(time(NULL));
	it = getplayer(senderNickname);
	if (it != players.end())
	{
		if (quiz[it->indexquize].correct_answer == message)
    		reponse += "\x03" "03" + std::string("Right answer") + ", well done";
		else
			reponse += "\x03" "04" + std::string("Wrong answer. ") + "The correct one is: " + quiz[it->indexquize].correct_answer;
		reponse +=  std::string("\r\n");
		players.erase(it);
		if (send(fdsocket, reponse.c_str(), reponse.size(), 0) < 0)
			return;
	}
	else
	{
		index =  this->indexquiz + rand() % (QUIZ_QUESTIONS_COUNT - this->indexquiz + 1);
		p.indexquize = index;
		p.nickname = senderNickname;
		this->players.push_back(p);
		this->indexquiz++;
		if (this->indexquiz >= QUIZ_QUESTIONS_COUNT)
			this->indexquiz = 0;
		std::cout << this->indexquiz  << "|" << index << "\n";
		sendQuations(fdsocket, reponse, quiz[index]);
	}
}

bot::~bot()
{
	close(this->fdsocket);
}