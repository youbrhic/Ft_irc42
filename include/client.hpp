/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiouane <sdiouane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 06:38:18 by youbrhic          #+#    #+#             */
/*   Updated: 2025/02/01 04:39:11 by sdiouane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>

class client
{
	private :

		int			fd;
		std::string nickname;
		std::string	username;
		std::string ipadd;
		bool 		is_operator;
		bool		is_invited;

	public :

		client();

		int			getfd() const;
		std::string	getnickname() const;
		std::string	getusername();
		std::string	getipadd();
		bool		getOperator();
		void		setOperator(bool op);
		
		bool		getInvited();
		void		setInvited(bool inv);

		void		setfd(int fd);
		void		setnickname(std::string nickname);
		void		setusername(std::string username);
		void		setipadd(std::string ip);

		
		bool		isOperator(client& currentClient);
		bool 		hasInvite(client& inviteClient);
		std::string getHostname();
		std::string getHostname_Kick();
};


#endif     