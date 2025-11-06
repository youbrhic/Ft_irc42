/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 18:29:14 by sdiouane          #+#    #+#             */
/*   Updated: 2025/02/08 13:13:27 by youbrhic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP


#include "Replies.hpp"
#include "server.hpp"
#include <sstream> 
#include "client.hpp"

class client;

class Channel {
private:
    // Channel settings
    bool                    inviteOnly;         
    bool                    hasUserLimit;        
    bool                    topicRestricted;     
    size_t                  userLimit;          
    std::string             key;                 
    std::string             name;                
    std::string             cause;              
    std::string             topic;               

    // Client lists
    std::vector<client>     clients;             
    std::vector<client>     invitedClients;      
    std::vector<client>     operators;           

public:
    // Constructor & Destructor
    Channel(const std::string& channelName);     
    ~Channel();                                  

    // Operator management
    void                    removeOperator(client& targetClient); 
    bool                    isOperator(client targetClient);   
    void                    addOperator(client targetClient);       
    void                    addFirstOperator(client& targetClient);      
    void                    removeallOperators();
    std::vector<client>     getOperators(); 

    // Topic settings
    bool                    getTopicRestricted();               
    void                    setTopicRestricted(bool value);     
    bool                    isTopicRestricted();                

    // Channel key management
    void                    setKey(std::string value);          
    std::string             getKey();                           
    void                    removeKey();                        

    // User limit management
    size_t                  getUserLimit();                     
    void                    setUserLimit(int limit);            
    void                    removeUserLimit();                 
    bool                    isUserLimitReached();               

    // General channel information
    const std::string&      getName() const;                    
    std::vector<client>&    getClients();                 

    // Topic management
    const std::string&      getTopic() const;             
    void                    setTopic(const std::string& newTopic);

    // Cause (Reason for actions like kicks)
    const std::string&      getCause() const;               
    void                    setCause(const std::string& newCause); 

    // Invitation system
    bool                    getInviteOnly();                   
    void                    setInviteOnly(bool value);        
    bool                    isInviteOnly() const;               
    bool                    hasInvite(client inviteClient);     
    void                    addInvitedClient(client& newInvClient); 
    std::vector<client>&    getInvitedClient();              

    // Client management
    void                    addClient(client newClient);       
    void                    removeClient(int clientFd);         
    bool                    hasClient(int clientFd) const;      
    void                    kickClient(int clientFd);           

    // Message broadcasting
    void                    broadcastMessage(const std::string& message, int senderFd) const; 

    std::string             clientChannel_list();
};



#endif
					 