/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chdonnat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:53:52 by chdonnat          #+#    #+#             */
/*   Updated: 2024/11/18 13:39:26 by chdonnat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_strndup(const char *s, size_t len)
{
    char *dup = (char *)malloc(len + 1);
    if (!dup)
        return (NULL);
    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';
    return (dup);
}

char	*ft_calloc(size_t nmemb, size_t size)
{
	char	*new;
	size_t	i;
	size_t	total_size;

	total_size = nmemb * size;
	if (total_size != nmemb * size)
		return (NULL);
	new = (char *) malloc(total_size);
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		new[i] = 0;
		i++;
	}
	return (new);
}

char	*ft_memcpy(char *dst, const char *src, size_t n)
{
	size_t			i;
	char			*d;
	const char		*s;

	if (!dst && !src)
		return (NULL);
	d = (char *) dst;
	s = (const char *) src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*ft_memmove(char *dest, const char *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *) dest;
	s = (unsigned char *) src;
	if (d > s)
	{
		while (n > 0)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
		return (dest);
	}
	return (ft_memcpy(dest, src, n));
}

size_t ft_read(int fd, char **buff, char **line, t_raw *remainder)
{
    ssize_t n_read;
    size_t  eol_i;
    char    *temp;

    while (1)
    {
        // Lecture du fichier
        n_read = read(fd, *buff, BUFFER_SIZE);
        if (n_read == -1) // Gestion d'erreur de lecture
            return (0);
        if (n_read == 0)  // Fin de fichier
            return (0);

        // Recherche d'un caractère de fin de ligne ('\n') dans le buffer
        eol_i = ft_eol_search(*buff, n_read);

        // Si un '\n' est trouvé
        if (eol_i < (size_t)n_read)
        {
            // Ajout jusqu'à '\n' à la ligne en cours
            temp = ft_strjoin(*line, *buff, eol_i + 1);
            if (!temp)
                return (0);
            free(*line);
            *line = temp;

            // Sauvegarde le reste dans `remainder`
            remainder->len = n_read - (eol_i + 1);
            free(remainder->str); // Évite une fuite mémoire
            remainder->str = ft_strndup(&(*buff)[eol_i + 1], remainder->len);
            if (!remainder->str)
                return (0);

            return (1); // Ligne complète lue
        }

        // Si pas de '\n', ajout de tout le buffer à la ligne en cours
        temp = ft_strjoin(*line, *buff, n_read);
        if (!temp)
            return (0);
        free(*line);
        *line = temp;
    }
}

char *ft_line(int fd, char **buff, t_raw *remainder)
{
    size_t  eol_i;
    char    *line = NULL;

    // Si remainder contient des données
    if (remainder->str && remainder->len > 0)
    {
        // Recherche de '\n' dans remainder
        eol_i = ft_eol_search(remainder->str, remainder->len);

        // Si un '\n' est trouvé
        if (eol_i < remainder->len)
        {
            // On extrait la ligne jusqu'à '\n' (inclus)
            line = ft_strndup(remainder->str, eol_i + 1);
            if (!line)
                return (NULL);

            // Mise à jour du reste : on conserve après '\n'
            if (eol_i + 1 < remainder->len)
            {
                remainder->len -= (eol_i + 1);
                ft_memmove(remainder->str, &remainder->str[eol_i + 1], remainder->len);
            }
            else
            {
                // Tout le reste a été utilisé, on libère
                free(remainder->str);
                remainder->str = NULL;
                remainder->len = 0;
            }
            return (line);
        }

        // Si aucun '\n', on prend tout remainder comme début de ligne
        line = ft_strndup(remainder->str, remainder->len);
        if (!line)
            return (NULL);

        // Libération du reste après copie
        free(remainder->str);
        remainder->str = NULL;
        remainder->len = 0;
    }

    // Lecture de nouvelles données depuis le fichier
    if (ft_read(fd, buff, &line, remainder) == 0)
    {
        // Si aucune donnée n'a été lue et pas de ligne, retour NULL
        return (free(line), NULL);
    }

    return (line);
}

char *get_next_line(int fd)
{
    char *line;
    char *buff;
    static t_raw remainder;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    buff = ft_calloc(BUFFER_SIZE, 1);
    if (!buff)
        return (NULL);

    if (!remainder.str)
    {
        remainder.str = ft_calloc(BUFFER_SIZE, 1);
        if (!remainder.str)
        {
            free(buff);
            return (NULL);
        }
        remainder.len = 0;
    }

    line = ft_line(fd, &buff, &remainder);

    free(buff);
    if (remainder.len == 0)
    {
        free(remainder.str);
        remainder.str = NULL;
    }

    return (line);
}

#include <stdio.h>  // Pour printf

int main(void)
{
    int     fd;
    char    *line;

    // Ouvrir le fichier
    fd = open("file_to_read", O_RDONLY);
    if (fd == -1)
    {
        perror("Open file error"); // Affiche un message d'erreur
        return (1);
    }

    // Lire et afficher les lignes une par une
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line); // Affiche la ligne
		sleep(1);
        free(line);         // Libère la mémoire allouée pour la ligne
    }

    // Fermer le fichier
    if (close(fd) == -1)
    {
        perror("Close file error");
        return (1);
    }

    return (0);
}

