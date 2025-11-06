/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:32:23 by sdiouane          #+#    #+#             */
/*   Updated: 2025/02/08 12:20:32 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/channel.hpp"
#include "../include/server.hpp"


static  Channel*    ChannelFinder(const std::string& chann_name, std::vector<Channel>& channels) {
    for (size_t i = 0; i < channels.size(); ++i) {  
        if (channels[i].getName() == chann_name) {
            return &channels[i]; 
        }
    }
    return NULL;  
}

static  client* findClient(const std::string& targetNickname, std::vector<client>& clients) {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i].getnickname() == targetNickname) {
            return &clients[i]; 
        }
    }
    return NULL; 
}

void    server::INVITE(int clientFd, const std::string& input, std::vector<Channel>& channels, std::vector<client>& clients) {
    if (input.empty()) {
        sendReponse("Invalid command input.", clientFd);
        return;
    }

    std::vector<std::string> params = SplitCmd(input);
    if (params.size() < 3) {
        sendReponse(ERR_NEEDMOREPARAMS(std::string("INVITE")), clientFd);
        return;
    }

    std::string nicknameToInvite = params[1];
    std::string channelName = params[2];

    Channel* channel = ChannelFinder(channelName, channels);
    if (!channel) {
        sendReponse(ERR_NOSUCHCHANNEL(channelName), clientFd);
        return;
    }

    std::vector<client>::iterator inviterIt = getclient(clientFd);
    if (inviterIt == clients.end()) {
        sendReponse("Client not found", clientFd);
        return;
    }

    client& inviterClient = *inviterIt;
    client* invitee = findClient(nicknameToInvite, clients);
    if (!invitee) {
        sendReponse(ERR_NOSUCHNICK(nicknameToInvite), clientFd);
        return;
    }

    if (channel->hasInvite(*invitee)) {
        sendReponse("Client already invited to this channel.", clientFd);
        return;
    }

    invitee->setInvited(true);
    channel->addInvitedClient(*invitee);

    sendReponse(RPL_INVITING(inviterClient.getnickname(), nicknameToInvite, channelName), clientFd);

    sendReponse(RPL_INVITE(inviterClient.getnickname(), nicknameToInvite, channelName), invitee->getfd());
}
