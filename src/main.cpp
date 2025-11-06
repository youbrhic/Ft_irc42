/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:18:01 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/08 13:16:57 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.hpp"
#include <stdlib.h>

bool setport(std::string str, int &port)
{
    std::istringstream stream(str);

    stream >> port;
    return ((stream.eof() && !stream.fail()) && !(port < 1024 || port > 65535));
}

bool checkpassowrd(std::string password)
{
	if (password.empty())
		return (0);
	for (int i = 0 ; i < static_cast<int>(password.size()); i++)
	{
		if (std::isspace(password[i]))
			return (0);
	}
	return (1);
}

int main(int ac, char **av)
{
	int			port;
	std::string	password;

	try
	{
		if (ac != 3 || !setport(av[1], port) || !checkpassowrd(av[2]))
			throw std::runtime_error("invalid argument : ./ircserv <port (1024 <->65535) password>");
		server s(port, av[2]);
		s.launchSever();
	} catch (std::exception &e)
	{
		std::cout << RED << e.what() << "\n";
		return (1);
	}
}
