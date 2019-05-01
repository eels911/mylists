/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lusts1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfrieda <rfrieda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 14:43:57 by rfrieda           #+#    #+#             */
/*   Updated: 2019/05/01 14:45:10 by rfrieda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <string.h>
#include <stdlib.h>

typedef struct        s_list
{
    void            *content;
    size_t            content_size;
    struct s_list    *next;
}                    t_list;

void    ft_modify_list_with_d(t_list *elem)
{
    int        len;

    len = 0;
    while (((char *)elem->content)[len])
    {
        ((char *)elem->content)[len] = 'd';
        len++;
    }
}

void    ft_print_result(t_list *elem)
{
    int        len;

    len = 0;
    while (((char *)elem->content)[len])
        len++;
    write(1, elem->content, len);
}

void    ft_del(void *content, size_t size)
{
    (void)size;
    free(content);
}

void    ft_lstadd(t_list **alst, t_list *new)
{
    if (*alst != NULL)
        new->next = (*alst);
    *alst = new;
}


t_list    *ft_lstnew(void const *content, size_t content_size)
{
    t_list    *elem;

    elem = (t_list *)malloc(sizeof(t_list));
    if (!elem)
        return (NULL);
    if (!content)
    {
        elem->content = NULL;
        elem->content_size = 0;
    }
    else
    {
        if (!(elem->content = malloc(sizeof(*(elem->content)) * content_size)))
        {
            free(elem);
            return (NULL);
        }
        elem->content = memcpy(elem->content, content, content_size);
        elem->content_size = content_size;
    }
    elem->next = NULL;
    return (elem);
}
void    ft_memdel(void **ap)
{
    if (ap && *ap)
    {
        free(*ap);
        *ap = NULL;
    }
}

void    ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
    if (*alst)
    {
        (del)((*alst)->content, (*alst)->content_size);
        ft_memdel((void**)alst);
    }
}

void    ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
    if (*alst && del)
    {
        ft_lstdel(&(*alst)->next, del);
        ft_lstdelone(alst, del);
    }
}
void    ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
    while (lst != NULL)
    {
        f(lst);
        lst = lst->next;
    }
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

t_list    *ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
    t_list    *new_list;

    if (lst == NULL)
        return (NULL);
        new_list = f(lst);
        new_list->next = ft_lstmap(lst->next, f);
        return (new_list);
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
    //ft_lstiter(elem, &ft_modify_list_with_d);
      //  ft_print_result(elem);
       // while (list)
      //  {
         //   ft_print_result(list);
          //  list = list->next;
       // }
    //ft_lstdel(&elem3, &ft_del);
        /*if (elem)
           ft_print_result(elem);
       else
            write(1, "NULL", 4);
        write(1, "\n", 1);
        if (elem2)
            ft_print_result(elem2);
        else
            write(1, "NULL", 4);
        write(1, "\n", 1);
        if (elem3)
            ft_print_result(elem3);
        else
            write(1, "NULL", 4);
        write(1, "\n", 1);
        if (elem4)
            ft_print_result(elem4);
        else
            write(1, "NULL", 4);*/
            if (!(list = ft_lstmap(elem, &ft_map)))
            return (0);
            if (list == elem)
            write(1, "A new list is not returned\n", 27);
        while (list)
        {
            ft_print_result(list);
            list = list->next;
        }
  return 0;
}