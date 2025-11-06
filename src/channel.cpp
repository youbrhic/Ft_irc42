/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:11:11 by sdiouane          #+#    #+#             */
/*   Updated: 2025/02/08 13:13:15 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/channel.hpp"
#include "../include/client.hpp"

// Constructor & Destructor :

Channel::Channel(const std::string& channelName) : name(channelName) {
	inviteOnly = false;
	topicRestricted = false;
	hasUserLimit = false;
	userLimit = 0;
}

Channel::~Channel() {}

// Getters :

const std::string&      Channel::getName() const {
	return name;
}

const std::string&      Channel::getCause() const {
	return cause;
}

const std::string&      Channel::getTopic() const {
	return topic;
}

std::string		Channel::getKey() {
	return key;
}

std::vector<client>&	Channel::getClients() {
	return clients;
}

std::vector<client>&	Channel::getInvitedClient() {
	return invitedClients;
}

bool	Channel::getInviteOnly() {
	return inviteOnly;
}

bool	Channel::isInviteOnly() const { 
	return inviteOnly; 
}

bool	Channel::getTopicRestricted() {
	return topicRestricted;
}

size_t	Channel::getUserLimit() {
	return userLimit;
}

bool	Channel::isUserLimitReached() {
	return hasUserLimit && clients.size() >= userLimit;
}

bool	Channel::isTopicRestricted() {
	return topicRestricted;
}

void Channel::addClient(client newClient) {
    for (std::vector<client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->getfd() == newClient.getfd()) {
            std::cout << "Client FD " << newClient.getfd() << " is already in this channel!" << std::endl;
            return;
        }
    }
    clients.push_back(newClient); 
}


void	Channel::removeClient(int clientFd) {
	for (std::vector<client>::iterator it = clients.begin(); it != clients.end(); ++it) {
		if (it->getfd() == clientFd) {
			clients.erase(it);
			return;
		}
	}
}

bool	Channel::hasClient(int clientFd) const {
	for (std::vector<client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
		if (it->getfd() == clientFd) {
			return true;
		}
	}
	return false;
}

void	Channel::broadcastMessage(const std::string& message, int senderFd) const {
	(void)senderFd;
	for (std::vector<client>::const_iterator it = clients.begin(); it != clients.end(); ++it) {
			if (send(it->getfd(), message.c_str(), message.length(), 0) == -1) {
				return ;
		}
	}
}

void	Channel::kickClient(int clientFd) {
	removeClient(clientFd);
}


bool	Channel::isOperator(client targetClient) {
	for (std::vector<client>::iterator it = operators.begin(); it != operators.end(); ++it) {
		if (it->getfd() == targetClient.getfd()) {
			return true;
		}
	}
	return false;
}

void Channel::removeOperator(client& targetClient) {

    targetClient.setOperator(false);

    for (std::vector<client>::iterator it = operators.begin(); it != operators.end(); ++it) {

        if (it->getfd() == targetClient.getfd()) {
            operators.erase(it);  
            break;  
        }
    }
}


void Channel::removeallOperators() {
    for (std::vector<client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        it->setOperator(false);
    }
	operators.clear();
}

void	Channel::addOperator(client targetClient) {
    targetClient.setOperator(true);
    operators.push_back(targetClient);
}

void Channel::addFirstOperator(client& targetClient)
{
    targetClient.setOperator(true);
    operators.push_back(targetClient);
	std::cout << "size od operators : " << operators.size() << std::endl;
}

bool	Channel::hasInvite(client inviteClient) {
	return inviteClient.getInvited();
}

void	Channel::addInvitedClient(client& newInvClient) {
	for (std::vector<client>::const_iterator it = invitedClients.begin(); it != invitedClients.end(); ++it) {
		if (it->getfd() == newInvClient.getfd()) {
			std::cout << "Client FD " << newInvClient.getfd() << " is already invited to this channel!" << std::endl;
			return;
		}
	}
	invitedClients.push_back(newInvClient);
}

void	Channel::setTopic(const std::string& newTopic) {
	topic = newTopic;
}

void	Channel::setCause(const std::string& newCause) {
	cause = newCause;
}

void	Channel::setInviteOnly(bool value) {
	inviteOnly = value;
}

void	Channel::setTopicRestricted(bool value) {
	topicRestricted = value;
}


void	Channel::setKey(std::string value) {
	key = value;
}

void	Channel::setUserLimit(int limit) {
	userLimit = limit;
	hasUserLimit = true;
}

void	Channel::removeUserLimit() {
	userLimit = 0;
	hasUserLimit = false;
}

void	Channel::removeKey() {
	key = "";
}

std::string Channel::clientChannel_list() {
	
    if (clients.empty()) {
        return "";
    }

    std::string list;
    bool first = true;

    for (std::vector<client>::const_iterator c = clients.begin(); c != clients.end(); ++c) {
        if (!first) {
            list += " ";
        }

        bool isOperator = false;
        for (std::vector<client>::const_iterator op = operators.begin(); op != operators.end(); ++op) {
            if (op->getfd() == c->getfd()) {
                isOperator = true;
                break;
            }
        }
        
        if (isOperator) {
            list += "@";
        }
        list += c->getnickname();
        first = false;
    }

    return list;
}

std::vector<client>     Channel::getOperators()
{
	return operators;
}