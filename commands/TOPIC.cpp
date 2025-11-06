/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:52:01 by sdiouane          #+#    #+#             */
/*   Updated: 2025/02/08 12:21:10 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/channel.hpp"
#include "../include/server.hpp"

Channel* findChannelByName(const std::string& name, std::vector<Channel>& channels) {
    for (std::vector<Channel>::iterator it = channels.begin(); it != channels.end(); ++it) {
        if (it->getName() == name) {
            return &(*it);
        }
    }
    return nullptr;
}

void server::Topic(int clientFd, const std::string& input, std::vector<Channel>& channels) {
    std::vector<std::string> params = SplitCmd(input);

    if (params.size() < 2) {
        sendReponse(ERR_NEEDMOREPARAMS(std::string("TOPIC")), clientFd);
        return;
    }

    std::string channelName = params[1];

    Channel* existingChannel = findChannelByName(channelName, channels);
    if (!existingChannel) {
        sendReponse(ERR_NOSUCHCHANNEL(channelName), clientFd);
        return;
    }

    std::vector<client>::iterator clientIt = getclient(clientFd);
    if (clientIt == clients.end()) {
        return; 
    }

    client& currentClient = *clientIt;

    if (!existingChannel->hasClient(clientFd)) {
        sendReponse(ERR_NOTONCHANNEL(channelName, currentClient.getnickname()), clientFd);
        return;
    }

    if (params.size() > 2) {
        if (existingChannel->isTopicRestricted() && !existingChannel->isOperator(currentClient)) {
            sendReponse(ERR_CHANOPRIVSNEEDED(channelName), clientFd);
            return;
        }

        std::string topic = input.substr(input.find(":") + 1);

        if (topic.empty()) {
            existingChannel->setTopic("");
            sendReponse(RPL_TOPIC(currentClient.getnickname(), channelName, "The topic has been cleared"), clientFd);
        } else {
            existingChannel->setTopic(topic);
            std::string rpl = ":" + currentClient.getHostname() + "@localhost TOPIC " + channelName + " :" + topic + "\r\n"; 
            sendReponse(rpl, clientFd);
        }
    } else {
        std::string currentTopic = existingChannel->getTopic();
        if (currentTopic.empty()) {
            sendReponse(RPL_NOTOPIC(currentClient.getnickname(), channelName), clientFd);
        } else {
            sendReponse(RPL_TOPIC(currentClient.getnickname(), channelName, currentTopic), clientFd);
        }
    }
}
