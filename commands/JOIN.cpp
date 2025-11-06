/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:49:09 by sdiouane          #+#    #+#             */
/*   Updated: 2025/02/08 12:22:07 by sdiouane         ###   ########.fr       */
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

void server::Join(int clientFd, const std::string& input, std::vector<Channel>& channels) 
{
    std::vector<std::string> params = SplitCmd(input);

    if (params.size() < 2) {
        sendReponse(ERR_NEEDMOREPARAMS(std::string("JOIN")), clientFd);
        return;
    }

    std::string channelList = params[1];
    std::string keyList = params.size() > 2 ? params[2] : "";

    std::vector<std::string> channelNames = SplitCmd_Sep(channelList);
    std::vector<std::string> keys = SplitCmd_Sep(keyList);
    keys.resize(channelNames.size(), ""); 

    for (size_t i = 0; i < channelNames.size(); ++i)
    {
        std::string channelName = channelNames[i];
        std::string key = keys[i];

        if (channelName.empty() || (channelName[0] != '#' && channelName[0] != '&')) {
            sendReponse(ERR_NOSUCHCHANNEL(channelName), clientFd);
            continue;
        }

        std::vector<client>::iterator clientIt = getclient(clientFd);
        if (clientIt == clients.end()) {
            return;
        }
        client currentClient = *clientIt;

        Channel* channel = ChannelFinder(channelName, channels);
        if (!channel)
        {
            channels.push_back(Channel(channelName));
            channel = &channels.back();
            channel->addClient(currentClient);
            channel->addFirstOperator(currentClient);
        }
        else 
        {
            if (channel->hasClient(clientFd))
                continue;

            if (!channel->getKey().empty() && channel->getKey() != key) {
                sendReponse(ERR_INCORPASS(channelName), clientFd);
                continue;
            }

            if (channel->isInviteOnly() && !channel->hasInvite(currentClient)) {
                sendReponse(ERR_INVITEONLYCHAN(currentClient.getnickname(), channelName), clientFd);
                continue;
            }

            if (channel->getUserLimit() && channel->isUserLimitReached())
            {
                sendReponse(ERR_CHANNELISFULL(currentClient.getnickname(), channelName), clientFd);
                continue ;
            }
            channel->addClient(currentClient);
        }

        std::vector<client> channelClients = channel->getClients();
        for (std::vector<client>::iterator it = channelClients.begin(); it != channelClients.end(); ++it) {
            sendReponse(RPL_JOINMSG(currentClient.getHostname(), currentClient.getipadd(), channelName), it->getfd());
        }
        
        if (!channel->getTopic().empty()) {
            sendReponse(RPL_TOPIC(currentClient.getnickname(), channelName, channel->getTopic()), clientFd);
        }
        
        std::string clientList = channel->clientChannel_list();
        sendReponse(RPL_NAMREPLY(currentClient.getnickname(), channelName, clientList), clientFd);
        sendReponse(RPL_ENDOFNAMES(currentClient.getnickname(), channelName), clientFd);
        
    }
}








