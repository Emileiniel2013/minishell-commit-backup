/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temil-da <temil-da@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:33:56 by temil-da          #+#    #+#             */
/*   Updated: 2024/09/23 18:35:38 by temil-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_list_bonus
{
	void				*content;
	struct s_list_bonus	*next;
}					t_list_bonus;

//Libft functions
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_strlen(const char *s);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
size_t			ft_strlcpy(char *dst, const char *src, size_t dsize);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
char			*ft_strnstr(const char *hay, const char *needle, size_t len);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
// Ft_printf functions
void			free_my(char *str);
int				print_my(char *str);
int				ft_putstr(char *s);
int				ft_putchar(char c);
int				*get_error(void);
void			set_error(int error);
void			ft_toupper_printf(char *str);
int				ft_printf(const char *str, ...);
int				ft_check_it_out(char c, va_list ap);
char			*ft_itoa_u(unsigned int n);
char			*ft_itoa_ptr(void *n);
char			*ft_itoa_printf(int n);
char			*ft_itoa_hex(unsigned long n);
// Libft_bonus functions
t_list_bonus	*ft_lstnew(void *content);
void			ft_lstadd_front(t_list_bonus **lst, t_list_bonus *new);
int				ft_lstsize(t_list_bonus *lst);
t_list_bonus	*ft_lstlast(t_list_bonus *lst);
void			ft_lstadd_back(t_list_bonus **lst, t_list_bonus *new);
// Get_next_line functions
int				ft_fetch_line(t_list **head, int fd);
char			*ft_strchr_gnl(const char *s, int c);
int				ft_create_node(t_list **head, char **buffer);
char			*ft_put_line(t_list *head);
int				ft_strlen_gnl(const char *s);
char			*ft_strcat_gnl(char *dest, const char *src);
char			*get_next_line(int fd);
int				clean_nodes(t_list **head, int x, int z);
void			free_nodes(t_list *head, t_list *last_node);
t_list			*ft_find_last_node_nl(t_list *node);

#endif