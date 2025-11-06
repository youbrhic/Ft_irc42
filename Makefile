# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: youbrhic <youbrhic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/17 02:33:47 by youbrhic          #+#    #+#              #
#    Updated: 2025/02/08 13:12:20 by youbrhic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

BOT = bot

CPP = c++

FLAGS = -Wall -Werror -Wextra -std=c++98

BONUSFILES = bonus/bot.cpp bonus/main.cpp

BONUSOBJECT = $(BONUSFILES:.cpp=.o)

FILES = src/client.cpp src/main.cpp src/server.cpp src/channel.cpp commands/NICK.cpp commands/PASS.cpp  commands/USER.cpp commands/excevcmd.cpp commands/JOIN.cpp commands/TOPIC.cpp  commands/KICK.cpp commands/INVITE.cpp  commands/MODE.cpp  commands/PRIVMSG.cpp

OBJS = $(FILES:.cpp=.o)

INCLUDES = include/client.hpp include/server.hpp include/channel.hpp include/Replies.hpp 

INCLUDES_BONUS = include/bot.hpp include/data.hpp

RM = rm -rf 

all : $(NAME)

%.o : %.cpp $(INCLUDES)
	$(CPP) $(FLAGS) -c $< -o $@ 

bonus/%.o : bonus/%.cpp $(INCLUDES_BONUS)
	$(CPP) $(FLAGS) -c $< -o $@ 

bonus : $(BOT)

$(BOT) : $(BONUSOBJECT)
	$(CPP) $(FLAGS) -o $(BOT) $(BONUSOBJECT)

$(NAME) : $(OBJS)
	$(CPP) $(FLAGS) -o $(NAME) $(OBJS)

clean :
	$(RM) $(OBJS) $(BONUSOBJECT)

fclean : clean 
	$(RM) $(NAME) $(BOT)

re : fclean all 