/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhervy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 16:50:26 by dhervy            #+#    #+#             */
/*   Updated: 2017/04/04 16:50:28 by dhervy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <curses.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

# define LINE1   "________________________________/\\\\\\_______"
# define LINE1B  "/\\\\\\\\\\\\\\\\\\_________________________\n"
# define LINE2   " ______________________________/\\\\\\\\\\_____"
# define LINE2B  "/\\\\\\///////\\\\\\_______________________\n"
# define LINE3   "  ____________________________/\\\\\\/\\\\\\____"
# define LINE3B  "\\///______\\//\\\\\\______________________\n"
# define LINE4   "   __________________________/\\\\\\/\\/\\\\\\_"
# define LINE4B  "_____________/\\\\\\/_______________________\n"
# define LINE5   "    ________________________/\\\\\\/__\\/\\\\\\_"
# define LINE5B  "__________/\\\\\\//_________________________\n"
# define LINE6   "     ______________________/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_"
# define LINE6B  "____/\\\\\\//____________________________\n"
# define LINE7   "      _____________________\\///////////\\\\\\//___"
# define LINE7B  "_/\\\\\\/_______________________________\n"
# define LINE8   "       _______________________________\\/\\\\\\__"
# define LINE8B  "___/\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\_____________________\n"
# define LINE9   "        _______________________________\\///___"
# define LINE9B  "__\\///////////////______________________\n"
# define LINE10  "                                                  "
# define LINE10B "               21sh by dhervy @ 42\n\n\n"

# define GREEN   "\033[32m"
# define RED     "\033[31m"
# define UP      4283163
# define DOWN    4348699
# define LEFT    4479771
# define RIGHT   4414235
# define CUP     71696882162459
# define OUP     1096489755
# define CDOWN   72796393790235
# define ODOWN   1113266971
# define CLEFT   74995417045787
# define OLEFT   1146821403
# define CRIGHT  73895905418011
# define ORIGHT  1130044187
# define HOME    4741915
# define END     4610843
# define DEL     127
# define CTRLD   4
# define ENTER   10
# define TAB     9
# define ESC     27
# define SPC     32
# define OX      8948194
# define OC      42947
# define OV      10127586
# define PIPE    1
# define PVIR    2
# define CMD     3
# define REDIG   4
# define REDID   5
# define DREDIG  6
# define DREDID  7
# define AGRE    8

typedef struct	s_winsize
{
	int					y;
	int					x;
}				t_winsize;

typedef struct	s_history
{
	char				*value;
	size_t				size;
	struct s_history	*prev;
	struct s_history	*next;
}				t_history;

typedef	struct	s_auto
{
	char				*value;
	int					select;
	struct s_auto		*prev;
	struct s_auto		*next;
}				t_auto;

typedef struct	s_commande
{
	char				*cmd;
	int					token;
	struct s_commande	*next;
	struct s_commande	*prev;
	struct s_commande	*right;
}				t_commande;

typedef struct	s_arbre
{
	int					token;
	char				*cmd;
	struct s_arbre		*left;
	struct s_arbre		*right;
	struct s_arbre		*top;
}				t_arbre;

typedef struct	s_all
{
	char				*pwd;
	char				*pastpwd;
	char				**env;
	char				**envcpy;
	struct termios		term;
	struct termios		termcpy;
	char				*name_term;
	int					pos_x;
	int					size;
	t_winsize			winsize;
	char				*copy;
	int					fork;
	int					in;
	int					out;
	char				*cmd;
	int					tabfd[256];
	int					column;
	int					ligne;
	int					prompt;
	int					i;
	int					j;
	int					k;
}				t_all;

t_all			*ft_singleton(void);
void			ft_caps(char *cmd, int fd);
int				ft_init_term(t_all	*all);
char			*ft_get_line(t_all *all, t_history **history);
void			ft_add_history(t_history *new_history, t_history **history);
t_history		*ft_init_history(t_history *new_history);
void			*ft_realloc(void *line, int newsize, char c, t_all *all);
void			ft_goto(int x, int y);
t_all			*ft_get_winsize(t_all *all);
int				ft_move_left(t_all *all, char *line);
int				ft_move_right(t_all *all, char *line);
void			ft_write_middle(t_all *all, char *str);
int				ft_copy_line(t_all *all, char **line, unsigned long key);
void			ft_delete(t_all *all, char **line);
void			ft_paste_line(t_all *all, char **line);
int				ft_parse_line(t_all *all, char *line);
int				ft_check_point_virgule(char *line);
int				ft_check_pipe(char *line);
int				ft_check_quote(char *line, int i);
char			*ft_delete_space(char *line);
char			*ft_clean_space(char *line);
void			ft_push_commande(t_commande **commande, char *cmd, int token);
int				ft_check_token(char *line, int i);
void			ft_get_token(t_all *all, t_commande **commande, char *line);
int				ft_get_parser(char **multi_line);
int				ft_token_pipe(char *line, int i);
int				ft_token_dredir_left(char *line, int i);
int				ft_token_dredir_right(char *line, int i);
int				ft_token_redir_left(char *line, int i);
int				ft_token_redir_right(char *line, int i);
int				ft_token_agre(char *line, int i);
int				ft_lexer(t_commande **commande);
int				ft_print_error(char *str);
t_history		*ft_search_history_up(t_history **start, char *line, int pos);
t_history		*ft_search_history_down(t_history **start, char *line, int pos);
char			*ft_searchenv(char **env, char *str);
void			ft_edit_var_env(t_all *all, t_commande *comande);
int				ft_get_arbre(t_commande *commande);
void			ft_exec_arbre(t_arbre **arbre);
int				ft_exec(t_all *all, char **cmd, char **env);
void			ft_exec2(t_all *all, char **cmd, char **env, char *str);
void			ft_create_arbre(t_arbre **arbre, t_arbre *top, \
				t_commande **commande);
char			*ft_auto_complet(char **str, t_all *all);
int				ft_clean_commande(t_commande *commande);
char			*ft_get_heredoc(t_all *all, char *cmp);
int				ft_get_key(unsigned long buf, t_all *all, char **line, \
				t_history **start);
int				ft_count_line_histoy(char *line, t_all *all);
void			ft_replace_cursor(char *line, t_all *all);
int				ft_reset_term(t_all *all);
int				ft_push_term(t_all *all);
void			ft_putprompt(t_all *all);
void			ft_exitshell(char **str);
void			ft_echoshell(char **str, int n, int i);
void			ft_cdshell(t_all *all, char **str);
char			**ft_removenv(char **env, char *str);
char			**ft_addenv(char **env, char *str, char *newstr);
char			*ft_searchenv(char **env, char *str);
void			ft_envshell(t_all *all, char **str);
void			ft_setenvshell(t_all *all, char **str);
int				ft_env(t_all *all, char **str, int i);
void			ft_envi(t_all *all);
int				ft_envu(t_all *all, char **str, int i);
void			ft_envshell2(char **str, int i, int j, int *arg);
int				ft_envshell5(char **str, int i, int j, int *arg);
int				ft_envshell4(char **str, int i, int j, int *arg);
void			ft_initenvshell(t_all *all, char **str);
int				ft_envshell3(t_all *all, char **str, int i, int *arg);
char			**ft_envdelet(char **env, int sup);
char			**ft_envcopy(char **env, char *str);
int				ft_checkvar(char *str);
void			ft_errorvar(void);
void			ft_free_commande(t_commande *commande);
void			ft_free_arbre(t_arbre **arbre);
int				ft_check_only_env(char **str);
void			ft_create_arbre_cmd(t_arbre *new_arbre, t_arbre *top, \
				char *str);
int				ft_create_arbre_redi(t_arbre **arbre, t_arbre *top, \
				t_commande **commande, t_arbre *new_arbre);
void			ft_create_arbre_redi2(t_arbre *new_arbre, t_arbre *top, \
				t_commande *tmp, t_commande **commande);
int				ft_create_arbre_pipe(t_arbre **arbre, t_arbre *top, \
				t_commande **commande, t_arbre *new_arbre);
void			ft_auto_move_cursor(t_auto **lsauto, t_all *all, \
				int columnlist);
void			ft_auto_print_color(char *str, int select);
void			ft_print_auto(t_auto **lsauto, t_all *all, int i);
void			ft_auto_move_right(t_auto **lsauto);
void			ft_push_auto(t_auto **lsauto, char *name);
int				ft_create_auto(t_auto **lsauto, char *path, char *debut);
int				ft_auto_sizemax(t_auto **lsauto);
void			ft_count_column(t_all *all);
int				ft_auto_get_nbrline(t_auto **lsauto, int columnlist);
t_auto			*ft_init_auto(char *name);
char			*ft_auto_get_string(char *str, int index);
char			*ft_auto_get_path(char *string);
char			*ft_auto_get_debut(char *string);
int				ft_auto_cmp(char *cmp, char *name);
int				ft_exec(t_all *all, char **cmd, char **env);
int				ft_check_droit(char *str);
void			ft_exec2(t_all *all, char **cmd, char **env, char *str);
void			ft_exec_arbre(t_arbre **arbre);
int				ft_get_arbre(t_commande *commande);
int				ft_exec_pipe(t_arbre **arbre);
int				ft_get_fd(char *str);
int				ft_get_fd2(char *str);
void			ft_init_tabfd(t_all *all);
void			ft_move_char_left(char *str, int i);
char			**ft_strsplit_quote(char **str);
int				ft_exec_bultin(t_all *all, char **cmd);
t_all			*ft_singleton(void);
void			sigfunc(int sig);
void			ft_putprompt(t_all *all);
int				ft_putc(int c);
void			ft_caps(char *cmd, int fd);
int				ft_check_bn(char *line, int pos_x);
int				ft_checks_first_line_left(t_all *all, char *line);
int				ft_count_move_left(t_all *all, char *line);
int				ft_check_move_left(t_all *all, char *line);
int				ft_move_left(t_all *all, char *line);
int				ft_check_move_right(t_all *all, char *line);
int				ft_move_right_quote(t_all *all, char *line);
int				ft_move_right(t_all *all, char *line);
void			ft_delete(t_all *all, char **line);
void			ft_copy_line2(t_all *all, char **line, int init, \
				unsigned long buf);
int				ft_copy_line4(t_all *all, int nbr, char **line);
int				ft_exec_redird(t_arbre **arbre);
void			ft_init_ijk(void);
void			ft_push_commande(t_commande **commande, char *cmd, int token);
int				ft_get_dredirg(t_all *all, t_commande *comande);
int				ft_check_token(char *line, int i);
void			ft_get_token2(t_all *all, t_commande **commande, char *line, \
				int retour);
void			ft_get_token3(t_all *all, t_commande **commande, char *line, \
				int retour);
int				ft_get_token4(t_all *all, t_commande **commande, char *line, \
				int retour);
int				ft_get_token5(t_all *all, t_commande **commande, char *line, \
				int retour);
void			ft_get_token(t_all *all, t_commande **commande, char *line);
int				ft_get_parser2(char **multi_line, t_commande **commande);
void			ft_get_parser3(char **multi_line, t_commande **commande);
int				ft_check_point_virgule(char *line);
int				ft_check_pipe(char *line);
int				ft_check_quote(char *line, int i);
char			*ft_delete_space(char *line);
int				ft_free_line_tab(char *line, char **multi_line);
int				ft_get_multi_commande2(t_all *all, char *line, \
				char **multi_line);
int				ft_get_key(unsigned long buf, t_all *all, char **line, \
				t_history **start);
void			ft_get_key2(t_all *all, char **line, unsigned long buf);
void			ft_get_key3(t_all *all, char **line, unsigned long buf);
void			ft_get_key4(t_all *all, char **line, unsigned long buf);
void			ft_get_key5(t_all *all, char **line, unsigned long buf, \
				t_history **start);
void			ft_get_key6(t_all *all, char **line, unsigned long buf, \
				t_history **start);
void			ft_get_key7(t_all *all, char **line, unsigned long buf, int i);
void			ft_get_key7bis(t_all *all, char c);
int				ft_check_line(char *line);
void			ft_do_up(int nbr);
void			ft_write_middle2(t_all *all, char *str);
void			ft_write_middle(t_all *all, char *str);
int				ft_count_line_histoy(char *line, t_all *all);
void			ft_replace_cursor(char *line, t_all *all);
int				ft_get_heredoc2(t_all *all, unsigned long buf, char **line);
void			ft_init_size_posx(void);

#endif
