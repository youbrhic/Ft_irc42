/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PASS.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 06:45:46 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/02 08:40:34 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

static void trimNewline(std::string &str)
{
    while (!str.empty() && (str[str.size() - 1] == '\n' || str[str.size() - 1] == '\r'))
        str.erase(str.size() - 1);
}

std::string getclientip(int client_fd)
{
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    char client_ip[INET_ADDRSTRLEN];

    if (getpeername(client_fd, (struct sockaddr *)&client_addr, &client_len) == -1)
		throw std::runtime_error("getpeername failed");
    if (inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip)) == NULL)
		throw std::runtime_error("inet_ntop failed");
    return std::string(client_ip);
}

void	server::PASS(int fdclient, std::string recvmessage)
{
	std::vector<std::string>	partscmd;
	std::string					reponse;
	std::string					recvpassword;
	client						newclient;
	int							i;

	if (this->getclient(fdclient) != this->clients.end())
	{
		std::string nikcname = this->getclient(fdclient)->getnickname();
		if (nikcname == "")
			nikcname = "*";
		reponse = ERR_ALREADYREGISTRED(std::string(nikcname));
		sendReponse(reponse, fdclient); return ;
	}
	partscmd = this->SplitCmd(recvmessage);
	if (partscmd.size() < 2)
	{
		if (partscmd.size() == 1)
			reponse = ERR_NEEDMOREPARAMS(std::string("PASS"));
		else
			reponse = ERR_NEEDMOREPARAMS(std::string("*"));
		sendReponse(reponse, fdclient); return ;
	}
	i = recvmessage.find(partscmd[1]);
	recvpassword = recvmessage.substr(i, recvmessage.size());
	trimNewline(recvpassword);
	if (recvpassword != this->password)
	{
		reponse = ERR_PASSWDMISMATCH(std::string("*"));
		sendReponse(reponse, fdclient); return ;
	}
	newclient.setfd(fdclient);
	newclient.setnickname("");
	newclient.setusername("");
	newclient.setipadd(getclientip(fdclient));
	this->clients.push_back(newclient);
}