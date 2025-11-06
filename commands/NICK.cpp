/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:52:00 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/04 16:12:37 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

int		countnicknames(std::vector<client> clients, std::string nickname)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (++i < static_cast<int>(clients.size()))
	{
		if (clients[i].getnickname() == nickname)
			count++;
	}
	return (count);
}

bool	validnickname(std::string nickname)
{
    if (nickname.empty() || !std::isalpha(nickname[0]))
        return false;
    for (size_t i = 1; i < nickname.size(); ++i)
	{
        char ch = nickname[i];
        if (!std::isalnum(ch))
            return (std::cout << ch << "\n", false);
    }
    return true;
}

void removeNewline(std::string &str)
{
    while (!str.empty() && (str[str.size() - 1] == '\n' || str[str.size() - 1] == '\r'))
        str.erase(str.size() - 1);
}

void	server::NICK(int fdclient, std::string recvmessage)
{
	std::vector<std::string>			partscmd;
	std::string							reponse = "";
	std::string							receiveNickname;
	std::vector<client>::iterator		it;
	int									i;

	it = getclient(fdclient);
	partscmd = SplitCmd(recvmessage);
	if (it == this->clients.end())
		reponse = ERR_ALREADYREGISTRED(std::string("*"));
	else if (partscmd.size() < 2)
		reponse = ERR_NEEDMOREPARAMS(std::string("NICK"));
	else
	{
		i = recvmessage.find(partscmd[1]);
		receiveNickname = recvmessage.substr(i, recvmessage.size());
		removeNewline(receiveNickname);
		if (!validnickname(receiveNickname))
			reponse = ERR_ERRONEUSNICKNAME(it->getnickname()); 
		else if (countnicknames(this->clients, receiveNickname) >= 1)
			reponse = ERR_NICKNAMEINUSE(receiveNickname);
	}
	if (reponse == "")
	{
		if (it->getusername() != "")
		{
			if (it->getnickname() == "")
				reponse = RPL_WELCOME(receiveNickname, std::string("Welcome to irc server !1"));	
			else
				reponse = RPL_NICK(it->getnickname(), receiveNickname);
		}
		it->setnickname(receiveNickname);
	}
	if (reponse != "")
		sendReponse(reponse, fdclient);
}
