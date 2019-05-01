/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lists2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrieda <rfrieda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:44:58 by rfrieda           #+#    #+#             */
/*   Updated: 2019/05/01 14:45:08 by rfrieda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>

typedef struct        s_list
{
    void            *content;
    size_t            content_size;
    struct s_list    *next;
}                    t_list;

t_list        *ft_lstnew(void const *content, size_t content_size)
{
    t_list    *new;

    if ((new = (t_list *)malloc(sizeof(*new))) == NULL)
        return (NULL);
    if (content == NULL)
    {
        new->content = NULL;
        new->content_size = 0;
    }
    else
    {
        if ((new->content = malloc(content_size)) == NULL)
        {
            free(new);
            return (NULL);
        }
        memcpy(new->content, content, content_size);
        new->content_size = content_size;
    }
    new->next = NULL;
    return (new);
}
void    ft_print_result(t_list *elem)
{
    int        len;

    len = 0;
    while (((char *)elem->content)[len])
        len++;
    write(1, elem->content, len);
    write(1, "\n", 1);
}
t_list    *ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
    t_list    *new_list;

    if (lst == NULL)
        return (NULL);
        new_list = f(lst);
        new_list->next = ft_lstmap(lst->next, f);
        return (new_list);
}

t_list    *ft_map(t_list *elem)
{
    int        i;
    t_list    *new_elem;

    new_elem = ft_lstnew(elem->content, elem->content_size);
    if (!new_elem)
        return (0);
    i = 0;
    while (((char *)new_elem->content)[i])
    {
        ((char *)new_elem->content)[i] = 'y';
        i++;
    }
    return (new_elem);
}






int main() {
t_list        *elem;
    t_list        *elem2;
    t_list        *elem3;
    t_list        *elem4;
    t_list        *list;
    char        str [] = "lorem";
    char        str2 [] = "ipsum";
    char        str3 [] = "dolor";
    char        str4 [] = "sit";

    elem = ft_lstnew(str, sizeof(str));
    elem2 = ft_lstnew(str2, sizeof(str2));
    elem3 = ft_lstnew(str3, sizeof(str3));
    elem4 = ft_lstnew(str4, sizeof(str4));
    elem->next = elem2;
    elem2->next = elem3;
    elem3->next = elem4;
    if (!(list = ft_lstmap(elem, &ft_map)))
            return (0);
        if (list == elem)
            write(1, "A new list is not returned\n", 27);
       /// while (list)
      //  {
       //     ft_print_result(list);
       //     list = list->next;
       // }
  return 0;
}