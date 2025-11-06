/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 04:50:51 by youbrhic          #+#    #+#             */
/*   Updated: 2025/01/29 04:31:45 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef BOT_HPP
# define BOT_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <vector>
#include "data.hpp"

#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"

struct player
{
	std::string	nickname;
	int			indexquize;
};

class bot
{
    private :

		int							serverport;
		int							fdsocket;
		int							indexquiz;
		char						*serverhostname;
		char						*password;
        std::vector<player>			players;

    public :

		bot(int serverport, char *hostname, char *password);

    	void							authenticate(std::string user, std::string nickname);
		void							playgame(int fdsocket, std::string message, std::string senderNickname);
    	void							connecttoserver();
    	void							startbot();
		void							init();

		std::vector<player>::iterator	getplayer(std::string nickname);
		void							sendRepone(int sockfd, std::string message, std::string senderNickname);

		~bot();
};

#endif