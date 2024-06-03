
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

SRCS =	$Smain.c \
		$Scheck_file.c \
		$Serror.c \
		$Scheck_file_elements.c \
		$Sutils.c \
		$Sget_next_line.c \
		$Sget_next_line_utils.c \
		$Scheck_file_path.c \
		$Scheck_map.c \
		$Splayer_move.c \
		$Srayon.c \
		$Srender.c
		
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