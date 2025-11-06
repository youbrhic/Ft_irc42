/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:52:13 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/05 09:45:13 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

std::string		getsenderinfo(std::vector<client>::iterator	sender)
{
	std::string	username;
	std::string	str;
	int			i;

	username = sender->getusername();
	i = -1;
	while (++i < (int)username.size())
	{
		if (std::isspace(username[i]))
			break;
	}
	username = username.substr(0, i);
	str = sender->getnickname();
	str += "!";
	str += username;
	str += "@";
	str += sender->getipadd();
	return (str);
}

void	sendtochannel(std::vector<client>::iterator	sender, std::string recvmessage, std::vector<std::string> cmd, std::vector<Channel>::iterator channel)
{
	std::vector<client>				clients;
	std::string						sendmessage;
	int								position;
	if (!channel->hasClient(sender->getfd()))
	{
		sendmessage = ERR_NOTONCHANNEL(sender->getnickname() ,channel->getName());
		send(sender->getfd(), sendmessage.c_str(), sendmessage.size(), 0);
		return ;
	}
	position = recvmessage.find(":");
	if (position != static_cast<int>(std::string::npos))
		sendmessage = recvmessage.substr(position + 1, recvmessage.size());
	else
		sendmessage = cmd[2];
	sendmessage = RPL_PRIVMSG(getsenderinfo(sender), cmd[1], sendmessage);
	clients = channel->getClients();
	for (int i = 0 ; i < static_cast<int>(clients.size()) ; i++)
	{
		if (clients[i].getfd() != sender->getfd())
		{
			if (send(clients[i].getfd(), sendmessage.c_str(), sendmessage.size(), 0) < 0)
				return;
		}
	}
}

void	server::PRIVMSG(int fdclient, std::string recvmessage)
{
	std::vector<std::string>		partscmd;
	std::string						reponse = "";
	std::string						recvdata;
	std::vector<client>::iterator	clitarget;
	std::vector<client>::iterator	clitsender;
	int								flag;
	int								i;

	partscmd = SplitCmd(recvmessage);
	flag = 0;
	if (partscmd.size() <= 2)
		reponse = ERR_NEEDMOREPARAMS(std::string("PRIVMSG"));
	else
	{
		clitarget = getclient(partscmd[1]);
		clitsender = getclient(fdclient);
		if ((partscmd[1][0] != '#'  && clitarget == this->clients.end()) 
			|| (partscmd[1][0] == '#' && getchannel(partscmd[1]) == this->channels.end()))
			reponse = ERR_NOSUCHNICK(partscmd[1]);
		else if (partscmd[partscmd.size() - 1] == ":") 
			reponse = ERR_NOTEXTTOSEND();
		else
		{
			if (partscmd[1][0] == '#')
			{
				sendtochannel(getclient(fdclient), recvmessage, partscmd, getchannel(partscmd[1])); return ;
			}
			else
			{
				if ((i = recvmessage.find(":")) != static_cast<int>(std::string::npos))
				{
					recvdata = recvmessage.substr(i + 1, recvmessage.size());
					reponse = RPL_PRIVMSG(getsenderinfo(clitsender), clitarget->getnickname(), recvdata);
				}
				else
					reponse = RPL_PRIVMSG(getsenderinfo(clitsender), clitarget->getnickname(), partscmd[2]);
			}
			flag = 1;
		}
	}
	if (flag)
		sendReponse(reponse, clitarget->getfd());
	else
		sendReponse(reponse, fdclient);
}
