/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   USER.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:51:43 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/06 16:44:29 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

void	server::USER(int fdclient, std::string recvmessage)
{
	std::vector<std::string>			partscmd;
	std::string							reponse;
	std::string							receiveUsername;
	std::vector<client>::iterator		it;
	int									i;

	it = getclient(fdclient);
	if (it == this->clients.end())
	{
		reponse = ERR_ALREADYREGISTRED(std::string("*"));
		sendReponse(reponse, fdclient); return ;
	}
	if ((it != this->clients.end() && it->getusername() != "") || it == this->clients.end())
	{
		std::string nikcname = it->getnickname();
		if (nikcname == "")
			nikcname = "*";
		reponse = ERR_ALREADYREGISTRED(std::string(nikcname));
		sendReponse(reponse, fdclient); return ;
	}
	partscmd = SplitCmd(recvmessage);
	if (partscmd.size() < 5)
	{
		reponse = ERR_NEEDMOREPARAMS(std::string("USER"));
		sendReponse(reponse, fdclient); return ;
	}
	i = recvmessage.find(partscmd[1]);
	receiveUsername = recvmessage.substr(i, recvmessage.size());
	it->setusername(receiveUsername);
	if (it->getnickname() != "")
	{
		reponse = RPL_WELCOME(it->getnickname(), std::string("Welcome to irc server !2"));
		sendReponse(reponse, fdclient); return ;
	}
}

