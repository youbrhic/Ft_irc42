/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 10:55:41 by sdiouane          #+#    #+#             */
/*   Updated: 2025/02/08 13:04:08 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/channel.hpp"
#include "../include/server.hpp"

static Channel* ChannelFinder(const std::string& chann_name, std::vector<Channel>& channels) {
    for (size_t i = 0; i < channels.size(); ++i) {  
        if (channels[i].getName() == chann_name)
            return &channels[i];
    }
    return nullptr;
}

static client*  findClientByFd(int clientFd, std::vector<client>& clients) {
    for (size_t i = 0; i < clients.size(); ++i) {
        if (clients[i].getfd() == clientFd)
            return &clients[i];
    }
    return nullptr;
}

void server::MessageToAllClinets(Channel channel, std::string msg) {    
    for (std::vector<client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        channel.broadcastMessage(msg, it->getfd());
    }
}

void    server::handleInviteMode(const std::string& param, Channel& channel, int clientFd, client currentClient) {

    if (param[0] == '+')
    {
        channel.setInviteOnly(true);
        channel.broadcastMessage(RPL_CHANGEMODE(currentClient.getHostname(), channel.getName(), "+i"), clientFd);
    }
    else if (param[0] == '-')
    {
        channel.setInviteOnly(false);
        channel.broadcastMessage(RPL_CHANGEMODE(currentClient.getHostname(), channel.getName(), "-i"), clientFd);
    }
}

void    server::handleUserLimitMode(const std::vector<std::string>& params, size_t& i, Channel& channel, int clientFd, client currentClient) {

    if (params[i][0] == '+') {
        if (i + 1 >= params.size() || params[i + 1].empty()) {
            sendReponse(ERR_NEEDMODEPARM(channel.getName(), "+l"), clientFd);
            return;
        }
        int limit = std::stoi(params[i + 1]);
        if (limit <= 0) {
            sendReponse(ERR_INVALIDMODEPARM(channel.getName(), "l"), clientFd);
            return;
        }
        channel.setUserLimit(limit);
        channel.broadcastMessage(RPL_UMODEIS(currentClient.getHostname(), channel.getName(), "+l", std::to_string(channel.getUserLimit())), clientFd);
        i++; 
    } else if (params[i][0] == '-') {
        channel.removeUserLimit();
        channel.broadcastMessage(RPL_UMODEIS(currentClient.getHostname(), channel.getName(), "-l", std::to_string(channel.getUserLimit())), clientFd);
    }
}

void server::handleKeyMode(const std::vector<std::string>& params, size_t& i, Channel& channel, int clientFd, client currentClient) { 

    if (params[i][0] == '+') {
        if (i + 1 >= params.size() || params[i + 1].empty()) {
            sendReponse(ERR_NEEDMODEPARM(channel.getName(), "+k"), clientFd);
            return;
        }
        channel.setKey(params[i + 1]);
        i++;
        channel.broadcastMessage(RPL_UMODEIS(currentClient.getHostname(), channel.getName(), "+k", channel.getKey()), clientFd);
    } else if (params[i][0] == '-') {
        channel.removeKey();
        channel.broadcastMessage(RPL_UMODEIS(currentClient.getHostname(), channel.getName(), "-k", channel.getKey()), clientFd);
    }
}


void    server::handleTopicMode(const std::string& param, Channel& channel, int clientFd, client currentClient) {       

    if (param[0] == '+')
    {
        channel.setTopicRestricted(true);
        channel.broadcastMessage(RPL_CHANGEMODE(currentClient.getHostname(), channel.getName(), "+t"), clientFd);
    }
    else if (param[0] == '-')
    {
        channel.setTopicRestricted(false);
        channel.broadcastMessage(RPL_CHANGEMODE(currentClient.getHostname(), channel.getName(), "-t"), clientFd);
    }
}

std::vector<client>::iterator findClientByNickname(const std::string& nickname, std::vector<client>& clients) {
    for (std::vector<client>::iterator it = clients.begin(); it != clients.end(); ++it) {
        if (it->getnickname() == nickname) {
            return it;
        }
    }
    return clients.end();
}

void server::handleOperatorMode(const std::string& param, Channel& channel, int clientFd, client currentClient, const std::string& targetNickname) { 
    (void)clientFd;
    std::vector<client>::iterator clientIt = findClientByNickname(targetNickname, clients);
    if (clientIt == clients.end())
        return ;
        
    client& targetClient = *clientIt;
    
    if (targetClient.getnickname() == currentClient.getnickname())
        return ;

    if (param[0] == '+') {
        channel.addFirstOperator(targetClient);
        channel.broadcastMessage(RPL_CHANGEMODE(currentClient.getHostname(), channel.getName(), "+o " + targetNickname), clientFd);
    } else if (param[0] == '-') {
        channel.removeOperator(targetClient);
        channel.broadcastMessage(RPL_CHANGEMODE(currentClient.getHostname(), channel.getName(), "-o " + targetNickname), clientFd);
    }
}

void server::processModeCommands(const std::vector<std::string>& params, Channel& channel, int clientFd) {

    std::vector<client>::iterator clientIt = getclient(clientFd);
    if (clientIt == clients.end()) {
        return;
    }
    client currentClient = *clientIt;
    for (size_t i = 2; i < params.size(); ++i) {
        if (params[i].empty()) continue;

        char mode = params[i][1];
        switch (mode) {
            case 'i':
                handleInviteMode(params[i], channel, clientFd, currentClient);
                break;
            case 'l':
                handleUserLimitMode(params, i, channel, clientFd, currentClient);
                break;
            case 'k':
                handleKeyMode(params, i, channel, clientFd, currentClient);
                break;
            case 't':
                handleTopicMode(params[i], channel, clientFd, currentClient);
                break;
            case 'o':
                if (i + 1 >= params.size()) {
                    if (params[i][0] == '+')
                        sendReponse(ERR_NEEDMOREPARAMS(std::string("MODE +o")), clientFd);
                    else if (params[i][0] == '-')
                        sendReponse(ERR_NEEDMOREPARAMS(std::string("MODE -o")), clientFd);
                    return;
                }
                handleOperatorMode(params[i], channel, clientFd, currentClient, params[i + 1]);
                ++i;
                break;
            default:
                return;
        }
    }
}

void server::MODE(int clientFd, const std::string& input, std::vector<Channel>& channels, std::vector<client>& clients) {
    
    std::vector<std::string> params = SplitCmd(input);

    if (params.size() < 2) {
        sendReponse(ERR_NEEDMOREPARAMS(std::string("MODE")), clientFd);
        return;
    }
    
    Channel* channel = ChannelFinder(params[1], channels);

    if (!channel) {
        sendReponse(ERR_NOSUCHCHANNEL(params[1]), clientFd);
        return;
    }

    client* currentClient = findClientByFd(clientFd, clients);
    
    if (!currentClient) {
        sendReponse(ERR_NOTREGISTERED, clientFd);
        return;
    }

    if (params.size() < 3)
        return;

    if (!channel->isOperator(*currentClient)){
        sendReponse(ERR_CHANOPRIVSNEEDED(params[1]), clientFd);
        return;
    }

    processModeCommands(params, *channel, clientFd);
    
}
