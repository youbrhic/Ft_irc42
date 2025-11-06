/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:35:52 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/04 06:46:23 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../include/bot.hpp"


static bool setport(std::string str, int &port)
{
    std::istringstream stream(str);

    stream >> port;
    return (stream.eof() && !stream.fail());
}

int main(int ac, char **av)
{
	int port;

	if (ac != 4 || !setport(av[2], port))
		return (std::cerr << "Usage: ./bot <hostname> <port> <password>\n", 1);
	try
	{
		bot b(std::atoi(av[2]), av[1], av[3]);
		b.init();
	}
	catch(std::exception &e)
	{
		std::cout << e.what() << "\n";
		return (1);
	}
}
