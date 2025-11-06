/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excevcmd.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 08:51:18 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/08 12:24:51 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"

void	server::excevcmd(int fdclient, std::string recvmessage)
{
	std::string	message = std::string(recvmessage);
	std::string	cmd = this->getcmd(message);

	if (cmd == "PASS")
		PASS(fdclient, recvmessage);
	else if (cmd == "USER")
		USER(fdclient, recvmessage);
	else if (cmd == "NICK")
		NICK(fdclient, recvmessage);
	else if (cmd == "PRIVMSG")
		PRIVMSG(fdclient, recvmessage);
	else if (cmd == "JOIN")
		Join(fdclient, recvmessage, channels);
	else if (cmd == "TOPIC")
		Topic(fdclient, recvmessage, channels) ;
	else if (cmd == "KICK")
		Kick(fdclient, recvmessage, channels, clients);
	else if (cmd == "INVITE")
		INVITE(fdclient, recvmessage, channels, clients);
	else if (cmd == "MODE")
		MODE(fdclient, recvmessage, channels, clients);
	else if (cmd != "PONG" && cmd != "QUIT")
	{
		std::string	reponse = ERR_UNKNOWNCOMMAND(cmd);
		if (send(fdclient, reponse.c_str(), reponse.size(), 0) < 0)
			return ;
	}
}
