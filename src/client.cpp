/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 02:06:12 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/08 12:23:18 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/client.hpp"
#include "../include/channel.hpp"
#include <sstream> 

client::client()
{
	is_operator = false;
	is_invited = false;
	this->fd = -1;
}

int		client::getfd() const
{
	return (this->fd);
}

std::string		client::getnickname() const
{
	return (this->nickname);
}

std::string		client::getusername()
{
	return (this->username);
}

std::string		client::getipadd()
{
	return (this->ipadd);
}

void	client::setfd(int fd)
{
	this->fd = fd;
}

void	client::setnickname(std::string nickname)
{
	this->nickname = nickname;
}

void	client::setusername(std::string username)
{
	this->username = username;
}

void	client::setipadd(std::string ip)
{
	this->ipadd = ip;
}

bool client::isOperator(client& currentClient)  {
    return currentClient.getOperator(); 
}


void client::setOperator(bool op)
{
	this->is_operator = op;
}

bool		client::getOperator()
{
	return is_operator;
}

bool		client::getInvited()
{
	return is_invited;
}

void		client::setInvited(bool inv)
{
	this->is_invited = inv;
}

bool client::hasInvite(client& inviteClient){
    return inviteClient.getInvited();
}


void trimNewline(std::string &str)
{
    while (!str.empty() && (str[str.size() - 1] == '\n' || str[str.size() - 1] == '\r'))
        str.erase(str.size() - 1);
}

std::vector<std::string>	Split(std::string recvmessage)
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

std::string client::getHostname() {
	
    std::string username = this->getusername();

    trimNewline(username); 

	std::vector<std::string> splt = Split(username);
	
    return this->getnickname() + "!" + splt[0];
}

std::string client::getHostname_Kick() {

    std::string username = this->getusername();

    trimNewline(username); 
	
	std::vector<std::string> splt = Split(username);
	
    return this->getnickname() + "!~" + splt[0];
}
