/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 05:55:10 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/08 13:13:49 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h> 
#include <arpa/inet.h>
#include <poll.h>
#include <csignal>
#include "client.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <libc.h>
#include "Replies.hpp"
#include "channel.hpp"


#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"

class client;
class Channel;

class server
{
    private :

        int							port;
		std::string					password;
		int							fdsocket;

		static	int					shutdown;

		std::vector<struct pollfd> 	fds;
		std::vector<client> 		clients;
		std::vector<Channel>		channels;
		std::map<int, std::string>	clientsmap;

	public :

		server(int port, std::string password);

		void		launchSever();
		void		createServerSocket();
		void 		addNewClient();
		void 		receiveNewData(int fdclient);
		void		ReponsetoClient(int fdclient, char *recvmessage);

		bool		PrintableDate(std::string str);

		std::string	getcmd(std::string message);

		// getters
		int								getPort();
		std::string						getPassword();
		int								getFdsocket();
		std::vector<client>::iterator	getclient(int fd);
		std::vector<client>::iterator	getclient(std::string nickname);
		std::vector<Channel>::iterator	getchannel(std::string channelname);
	
		// commands
		void						excevcmd(int fdclient, std::string	recvmessage);
		void						PASS(int fdclient, std::string recvmessage);
		void						USER(int fdclient, std::string recvmessage);
		void						NICK(int fdclient, std::string recvmessage);
		void						PRIVMSG(int fdclient, std::string recvmessage);
		void						sendReponse(std::string reponse, int fdclient);
		std::vector<std::string>	SplitCmd(std::string recvmessage);
		std::vector<std::string>	SplitCmd_Sep(std::string recvmessage);
		
		void 						Kick(int clientFd, const std::string& input, std::vector<Channel>& channels, std::vector<client>& clients);
		
		void						Join(int clientFd, const std::string& input, std::vector<Channel>& channels);
		void						addClientToChannel(Channel* channel, client& currentClient);
		bool						canJoinChannel(Channel* channel, client& currentClient, const std::string& key);
		
		void						Topic(int clientFd, const std::string& input, std::vector<Channel>& channels);

		void						INVITE(int clientFd, const std::string& input, std::vector<Channel>& channels, std::vector<client>& clients);

		void						MODE(int clientFd, const std::string& input, std::vector<Channel>& channels, std::vector<client>& clients); 
		void						processModeCommands(const std::vector<std::string>& params, Channel& channel, int clientFd) ;
		void						handleInviteMode(const std::string& param, Channel& channel, int clientFd, client currentClient);
		void						handleUserLimitMode(const std::vector<std::string>& params, size_t& i, Channel& channel, int clientFd, client currentClient);
		void						handleKeyMode(const std::vector<std::string>& params, size_t& i, Channel& channel, int clientFd, client currentClient);
		void						handleTopicMode(const std::string& param, Channel& channel, int clientFd, client currentClient) ;
		void						handleQuit(int fdclient);
		void						handleOperatorMode(const std::string& param, Channel& channel, int clientFd, client currentClient, const std::string& targetNickname);
		
		static	void	active_shutdown(int sig);

		void MessageToAllClinets(Channel channel, std::string msg);

		~server();
};

#endif