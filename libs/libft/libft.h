/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hde-camp <hde-camp@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 18:50:52 by hde-camp          #+#    #+#             */
/*   Updated: 2022/02/05 12:53:40 by hde-camp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_dl_list
{
	void				*content;
	struct s_dl_list	*next;
	struct s_dl_list	*prev;
}	t_dl_list;

/**Parte 1*/
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
/**
 * @brief Compare two strings.
 * 
 * @param s1 string 1.
 * @param s2 string 2.
 * @return an integer less than, equal to, or greater than zero if s1 is found, 
 * respectively, to be less than, to match, or be greater than s2.
 */
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_atoi(const char *nptr);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(char c);
int			ft_toupper(int c);
int			ft_tolower(int c);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(const char *s1);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **lst, void (*del)(void*));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
/**
 * @brief create a new double linked list item.
 * 
 * @param content (void *) Any structure or content
 * @return t_dl_list* returns the item.
 */
t_dl_list	*ft_dl_lstnew(void *content);
void		ft_dl_destroyall(t_dl_list *item, void (*del)(void*));
/**
 * @brief Returns the first item of a list.
 * 
 * @param item Any item in the list
 * @return t_dl_list first item, or NULL if the list is empty
 */
t_dl_list	*ft_dl_getfirst(t_dl_list *item);
/**
 * @brief Destroy a single list item.
 * This already link next to previous itens.
 * @param item item to be destroyed
 * @param del Cleanup function for item.
 */
void		ft_dl_lstdestroy(t_dl_list *item, void (*del)(void*));
/**
 * @brief Add an item to the start of a double linked list.
 * @param item A pointer to any item of the list.
 * @param new Item to be added.
 */
void		ft_dl_addfirst(t_dl_list *item, t_dl_list *new);
/**
 * @brief Add an item to the end of a double linked list.
 * @param item A pointer to any item of the list.
 * @param new Item to be added.
 */
void		ft_dl_addlast(t_dl_list *item, t_dl_list *new);
/**
 * @brief Add an item after the item pointed by lst.
 * after execution, lst will point to new
 * 
 * @param lst Pointer to an item in the list
 * @param new Item to be added
 */
void		ft_dl_addback(t_dl_list **lst, t_dl_list *new);
/**
 * @brief Add an item before the item pointed by lst.
 * after execution, lst will point to new
 * 
 * @param lst Pointer to an item in the list
 * @param new Item to be added
 */
void		ft_dl_addfront(t_dl_list **lst, t_dl_list *new);
/**
 * @brief Remove one item from list, replacing (*lst)
 * with the first available option within next, prev or NULL.
 * @param lst Any pointer to item pointer in the list
 * @param del Cleanup function used on each item.
 */
void		ft_dl_removeone(t_dl_list **lst, void (*del)(void*));
/**
 * @brief Searches str for c.
 * 
 * @param c A character to search for.
 * @param str A string to iterate over.
 * @return Returns the character found (it's value as an integer),
 *  if no character is found, return zero.
 */
int			ft_chrinstr(char c, const char *str);
#endif
