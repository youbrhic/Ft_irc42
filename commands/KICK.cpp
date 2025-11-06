/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:51:00 by sdiouane          #+#    #+#             */
/*   Updated: 2025/02/08 12:21:26 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/channel.hpp"
#include "../include/server.hpp"

static Channel* ChannelFinder(const std::string& chann_name, std::vector<Channel>& channels) {
    for (size_t i = 0; i < channels.size(); ++i) {  
        if (channels[i].getName() == chann_name) {
            return &channels[i]; 
        }
    }
    return NULL;  
}

client* findClient(const std::string& targetNickname, std::vector<client>& clients) {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i].getnickname() == targetNickname) {
            return &clients[i]; 
        }
    }
    return NULL; 
}

client* findClientByFd(int clientFd, std::vector<client>& clients) {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i].getfd() == clientFd) { 
            return &clients[i];
        }
    }
    return NULL;
}

void server::Kick(int clientFd, const std::string& input, std::vector<Channel>& channels, std::vector<client>& clients) {

    std::vector<std::string> params = SplitCmd(input);

    if (params.size() < 3) {
        sendReponse(ERR_NEEDMOREPARAMS(std::string("KICK")), clientFd);
        return;
    }

    std::string channelName = params[1];
    std::string targetNickname = params[2];
    std::string cause;

    if (params.size() > 3)
        cause = input.substr(input.find(":") + 1);
    else
        cause = "";

    Channel* channel = ChannelFinder(channelName, channels);
    if (!channel) {
        sendReponse(ERR_NOSUCHCHANNEL(channelName), clientFd);
        return;
    }

    client* currentClient = findClientByFd(clientFd, clients);
    if (!currentClient) {
        sendReponse(ERR_NOTREGISTERED, clientFd);
        return;
    }

    if (!findClient(currentClient->getnickname(), channel->getClients())) {
        sendReponse(ERR_NOTONCHANNEL(currentClient->getnickname(), channelName), clientFd);
        return;
    }

    client* targetClient = findClient(targetNickname, channel->getClients());
    if (!targetClient) {
        sendReponse(ERR_USERNOTINCHANNEL(targetNickname, channelName), clientFd);
        return;
    }

    if (channel->isOperator(*currentClient)) {

        std::stringstream ss;
        ss << ":" << currentClient->getHostname_Kick() << "@" << "localhost" << " KICK " << channelName << " " << targetNickname;

        if (!cause.empty())
            ss << " :" << cause;
        ss << "\r\n";

        std::string message = ss.str();

        for (std::vector<client>::iterator it = channel->getClients().begin(); it != channel->getClients().end(); ++it) {
            if (targetClient->getfd() != it->getfd())
                sendReponse(message, it->getfd());
        }
        
        sendReponse(message, targetClient->getfd());

        if (channel->isOperator(*targetClient)) {
            channel->removeOperator(*targetClient);
            channel->removeClient(targetClient->getfd());
        } else
            channel->removeClient(targetClient->getfd());
                
    }
    else
        sendReponse(ERR_CHANOPRIVSNEEDED(channelName), clientFd);

}
