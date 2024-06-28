
NAME = Cub3D

S = src/
O = obj/
L = libft/
I = inc/
D = dep/
M = minilibx-linux/


CC = cc

LDFLAGS = -L$L -lft -L$M -lmlx -lXext -lX11 -lm
CFLAGS	+=	-I$I -I$L$I -I$M

SRCS	=	$(addprefix $Sparsing/, \
				check_file.c \
				error.c \
				check_empty_lines.c \
				check_file_elements.c \
				utils.c \
				utils_2.c \
				get_next_line.c \
				get_next_line_utils.c \
				check_file_path.c \
				parse_map.c \
				convert_hexa.c \
				init.c \
				check_map.c) \
			$(addprefix $Sexecution/, \
				dda.c \
				raycasting.c \
				render.c \
				set_values.c \
				utils.c \
				update_player_position.c \
				rotate_player.c \
				handle_user_input.c) \
			$Smain.c
		
#		$(addprefix $S, examplefolder/)

RM	=	/bin/rm -rf

OBJS =	$(SRCS:$S%=$O%.o)

DEP =	$(SRCS:$S%=$D%.d)

all : lib $(NAME)

$O:
	@mkdir -p $@

$(OBJS): | $O

$(OBJS): $O%.o: $S%
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$D:
	@mkdir -p $@

$(DEP): | $D

$(DEP): $D%.d: $S%
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MM -MF $@ -MT "$O$*.o $@" $<


$(NAME): $(OBJS) $(DEP)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

lib:
	@make -C $L 
	@make -C $M 

cleanobjs:
	$(RM) $(OBJS) $(O)

cleandep: 
	$(RM) $(DEP) $(D)

clean: cleanobjs cleandep

lclean:
	@make clean -C minilibx-linux/
	@make fclean -C libft/

fclean : clean lclean
	$(RM) $(NAME)

re: fclean all

include $(DEP)

.PHONY: all clean fclean lclean re debug lib