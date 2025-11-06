/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:08:16 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/08 13:01:36 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

server::server(int port, std::string password) : port(port), password(password)
{}

void	 server::createServerSocket()
{
	struct sockaddr_in			address;
	struct pollfd 				NewPoll;
	int							en = 1;

	this->fdsocket = socket(PF_INET, SOCK_STREAM, 0);

	if (this->fdsocket < 0)
		throw std::runtime_error("socket() failed");

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(this->port);
	
	if(setsockopt(this->fdsocket, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));

	if (fcntl(fdsocket, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("fcntl(fd, F_SETFL, O_NONBLOCK)  failed"));

	if (bind(this->fdsocket, (sockaddr *)&address, sizeof(address)) == -1)
		throw std::runtime_error("bind() failed");

	if (listen(fdsocket, 128) == -1)
		throw std::runtime_error("listen() failed");

	std::cout << GRE << "Server connected \n";
	std::cout << YEL << "waiting for  connection\n";
	
	NewPoll.fd = fdsocket;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	
	fds.push_back(NewPoll);
}

int server::shutdown = 0;

void	server::active_shutdown(int sig)
{
	(void)sig;
	server::shutdown = 1;
}

void    server::launchSever()
{
	createServerSocket();

	signal(SIGINT, server::active_shutdown);
	signal(SIGQUIT, server::active_shutdown);
	signal(SIGPIPE, SIG_IGN);

	while (!server::shutdown)
	{
		if (poll(&fds[0], fds.size(), 0) == -1 && !server::shutdown)
			throw std::runtime_error("poll() failed");
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (!server::shutdown && (this->fds[i].revents & POLLIN))
			{
				if (this->fds[i].fd == fdsocket)
					addNewClient();
				else
					receiveNewData(fds[i].fd);
			}
		}
	}
}

void 	server::addNewClient()
{
	client				c;
	struct sockaddr_in 	cliadd;
	struct pollfd		NewPoll;
	socklen_t			len = sizeof(cliadd);
	int 				incofd = accept(this->fdsocket, (sockaddr *)&(cliadd), &len);

	if (incofd == -1)
		{std::cout << "accept() failed" << std::endl; return;}
		
	NewPoll.fd = incofd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	this->fds.push_back(NewPoll);
	
	this->clientsmap[incofd] = "";
	std::cout << GRE << "Client <" << incofd << "> Connected" << WHI << std::endl;
}

bool server::PrintableDate(std::string str)
{
    for (size_t i = 0; i < str.size(); ++i)
	{
        if (!std::isprint(static_cast<unsigned char>(str[i]))
				&& !std::isspace(static_cast<unsigned char>(str[i])))
            return false;
    }
    return true;
}

void 	server::receiveNewData(int fd)
{
	char 							buff[1024];
	ssize_t 						bytes;
	std::vector<client>::iterator	c;

	memset(buff, 0, sizeof(buff));
	bytes = recv(fd, buff, sizeof(buff) - 1 , 0);
	if (bytes <= 0)
	{
		std::cout << RED << "Client <" << fd << "> Disconnected" << WHI << std::endl;
		c = this->getclient(fd);
		if (c != this->clients.end())
			this->clients.erase(c);
		handleQuit(fd);
		close(fd);
	}
	else
	{
		if (bytes > 1024)
			buff[1023] = '\0';
		else
			buff[bytes] = '\0';
		this->clientsmap[fd] += buff;
		if (this->clientsmap[fd].find_first_of("\r\n") != std::string::npos)
			ReponsetoClient(fd, (char *)this->clientsmap[fd].c_str());
	}
}

std::vector<std::string> splitReceivedMessage(const std::string &input)
{
    std::vector<std::string> result;
    std::string currentCommand;
    
    for (size_t i = 0; i < input.size(); ++i)
	{
        if (input[i] == '\r' || input[i] == '\n')
		{
            if (!currentCommand.empty()) {
                result.push_back(currentCommand);
                currentCommand.clear();
            }
            if (input[i] == '\r' && i + 1 < input.size() && input[i + 1] == '\n')
                ++i;
        }
		else
			currentCommand += input[i];
    }
    if (!currentCommand.empty())
        result.push_back(currentCommand);
    return result;
}

void	server::ReponsetoClient(int fd, char *recvmessage)
{
	std::string						recvcmd;
	std::string 					message = std::string(recvmessage);
	std::vector<client>::iterator	client;

	recvcmd = this->getcmd(message);
	if (recvcmd == "")
		return ;
	client = getclient(fd);
	if (recvcmd != "PASS" && (client == this->clients.end() || (client != this->clients.end()
		&& ((client->getnickname() == ""  || client->getusername() == "")
			&& recvcmd != "USER" && recvcmd != "NICK"))))
	{
		std::string sendmessage = ERR_ALREADYREGISTRED(std::string("*"));
		send(fd, sendmessage.c_str(), sendmessage.size(), 0);
		this->clientsmap[fd] = "";
		return ;
	}
	std::vector<std::string> cmds = splitReceivedMessage(message);
	for (int i = 0 ; i < (int)cmds.size() ; i++)
	{
		excevcmd(fd, cmds[i].c_str());
		usleep(90);
	}
	this->clientsmap[fd] = "";
}

std::string	server::getcmd(std::string message)
{
    std::istringstream stream(message);
	std::string	cmd;

    stream >> cmd;
	return (cmd);
}

int		server::getPort()
{
	return (this->port);
}

std::string		server::getPassword()
{
	return (this->password);
}

int		server::getFdsocket()
{
	return (this->fdsocket);
}

std::vector<std::string>	server::SplitCmd(std::string recvmessage)
{
	std::vector<std::string> partsCmd;
	std::istringstream stream(recvmessage);
    std::string part;

	while (stream >> part)
    {
        partsCmd.push_back(part);
    }
	return(partsCmd);
}

std::vector<std::string>	server::SplitCmd_Sep(std::string recvmessage)
{
    std::vector<std::string> result;
    std::stringstream ss(recvmessage);
    std::string item;

    while (std::getline(ss, item, ','))
	{ 
        if (!item.empty())
            result.push_back(item);
    }
    return result;
}

std::vector<client>::iterator	server::getclient(int fd)
{
	std::vector<client>::iterator it;

	it = this->clients.begin();
	while (it != this->clients.end())
	{
		if (it->getfd() == fd)
			return (it);
		it++;
	}
	return (this->clients.end());
}

std::vector<client>::iterator	server::getclient(std::string nickname)
{
	std::vector<client>::iterator it;

	it = this->clients.begin();
	while (it != this->clients.end())
	{
		if (it->getnickname() == nickname)
			return (it);
		it++;
	}
	return (this->clients.end());	
}

void	server::sendReponse(std::string reponse, int fdclient)
{
	std::cout << "reponse : \n" << reponse << "\n";
	if (send(fdclient, reponse.c_str(), reponse.size(), 0) < 0)
		return ;
}

void	server::handleQuit(int fdclient)
{
	int								i;
	std::vector<client>::iterator 	it;

	i = -1;
	while (++i < static_cast<int>(channels.size()))
	{
		if (channels[i].hasClient(fdclient))
		{
			std::vector<client>	&clients = channels[i].getClients();
			it = clients.begin();
			while (it != clients.end())
			{
				if (fdclient == it->getfd())
				{
					clients.erase(it);
					break;
				}
				it++;
			}
		}
	}
}

std::vector<Channel>::iterator	server::getchannel(std::string channelname)
{
	std::vector<Channel>::iterator	it;

	it = this->channels.begin();
	while (it != this->channels.end())
	{
		if (it->getName() == channelname)
			return (it);
		it++;
	}
	return (this->channels.end());
}

server::~server()
{
	for(size_t i = 0; i < clients.size(); i++)
	{
		std::cout << RED << "Client <" << clients[i].getfd() << "> Disconnected" << WHI << std::endl;
		close(clients[i].getfd());
	}
	if (fdsocket != -1)
	{
		std::cout << RED << "Server <" << fdsocket << "> Disconnected" << WHI << std::endl;
		close(fdsocket);
	}
}

